#include "WindowShaderGl.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include "Shader.h"
#include <imgui.h>
#include "../imgui_impl/imgui_impl_sdl.h"
#include "../imgui_impl/imgui_impl_opengl3.h"
#include <vector>


WindowShaderGl::WindowShaderGl(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	init();

	mesh_.ExtractObj("torus.obj");
	mesh_.ComputeFlat();

	algebra::Vec3<float> vLookAt = { 0,0,1 };
	algebra::Vec3<float> vUp = { 0,1,0 };
	algebra::Vec3<float> vPosition = { 0,0,-5 };
	algebra::Vec3<float> vTarget = vPosition + vLookAt;
	camera_.position = vPosition;
	camera_.target = vTarget;
	camera_.up = vUp;
	eventsManager.type = 1;
}


WindowShaderGl::~WindowShaderGl()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

static std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

static std::vector<float> positions = {
	  0.0f,  0.0f,  0.0f,
	  0.0f,  0.5f,  0.0f,
	  0.5f,  0.0f,  0.0f,
	  0.0f, -0.5f,  0.0f,
	 -0.5f,  0.0f,  0.0f
};

static std::vector<float> colors = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f };


static std::vector<float> texture_coordinates = {
	 0.5f,  0.5f,
	 0.5f,  1.0f,
	 1.0f,  0.5f,
	 0.5f,  0.0f,
	 0.0f,  0.5f};

static std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 1 };
static char str_indices[255] = "0,1,2,3,4,1";

static float t = 0;
void WindowShaderGl::run()
{
	SDL_Event event;
	bool loop = true;
	lastUpdateTitle = startTime;
	SDL_GL_SetSwapInterval(0);

	unsigned int indicesSquare[] = {0, 1, 2, 3, 4, 1};
	unsigned int indicesTriangle[] = {2, 1, 4};


	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(
		WindowShaderGl::debugMessage,
		nullptr);

	// Enable blending to 1 - source alpha.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable Z buffer.
	glEnable(GL_DEPTH_TEST);

	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_.GetFlatPositions().size() * sizeof(float),
		mesh_.GetFlatPositions().data(), 
		GL_STATIC_DRAW);
	
	GLuint cbo = 0;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_.GetFlatNormals().size() * sizeof(float),
		mesh_.GetFlatNormals().data(),
		GL_STATIC_DRAW);



	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	GLuint tco = 0;
	glGenBuffers(1, &tco);
	glBindBuffer(GL_ARRAY_BUFFER, tco);
	glBufferData(
		GL_ARRAY_BUFFER,
		mesh_.GetFlatTextures().size() * sizeof(float),
		mesh_.GetFlatTextures().data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, tco);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		mesh_.GetFlatIndices().size() * sizeof(unsigned int),
		mesh_.GetFlatIndices().data(),
		GL_STATIC_DRAW);

	Shader vs(ShaderType::VertexShader);
	Shader fs(ShaderType::FragmentShader);
	
	if (!vs.openShader("vertexShader.txt")) 
	{
		std::cout << vs.errorMessage << "\n";
		exit(-2);
	}
	if (!fs.openShader("fragmentShader.txt"))
	{
		std::cout << fs.errorMessage << "\n";
		exit(-2);
	}

	program_ = std::make_shared<Program>(vs, fs);
	program_->Use();

	// Bind the texture to the shader.
	const unsigned int slot = 0;
	texture1_ = std::make_shared<Texture>(
		"texture.bmp");
	texture1_->Bind(slot);
	program_->UniformInt("texture1", slot);

	program_->UniformMatrix4("projection", algebra::Matrix4<float>::perspectiveMatrix(screenWidth, screenHeight, 0.1, 100000, 60 * M_PI / 180));


	program_->UniformMatrix4("view", camera_.View());


	while (loop)
	{
		auto currentTime = std::chrono::system_clock::now();
		framesTime.push_back(currentTime);

		std::chrono::duration<float> elapsed_sec = currentTime - startTime;
		t = elapsed_sec.count() * 20;


		program_->UniformMatrix4("model", algebra::Matrix4<float>::rotateMatrixX(t * 0.3f) *
			algebra::Matrix4<float>::rotateMatrixY(t * 0.5f) *
			algebra::Matrix4<float>::rotateMatrixZ(t));

		bool removeFrame = true;
		while (removeFrame) 
		{
			std::chrono::duration<float> elapsed_seconds = currentTime - framesTime[0];
			if (elapsed_seconds.count() > 1) 
			{
				framesTime.erase(framesTime.begin());
			}
			else 
			{
				removeFrame = false;
			}
		}

		std::chrono::duration<float> elapsed_seconds = currentTime - lastUpdateTitle;
		if (elapsed_seconds.count() > 0.01f) 
		{
			lastUpdateTitle = currentTime;
			std::string str = "GL_Shader - " + std::to_string(framesTime.size());
			SDL_SetWindowTitle(window, str.c_str());
		}

		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			loop = eventsManager.manageEvents(event);
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		if (eventsManager.showConsole)
		{
			imguiWindow();
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,
			mesh_.GetFlatPositions().size() * sizeof(float),
			mesh_.GetFlatPositions().data(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, cbo);
		glBufferData(GL_ARRAY_BUFFER,
			mesh_.GetFlatNormals().size() * sizeof(float),
			mesh_.GetFlatNormals().data(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
		glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				mesh_.GetFlatIndices().size() * sizeof(unsigned int),
				mesh_.GetFlatIndices().data(),
				GL_STATIC_DRAW);
		glClearColor(0.2, 0, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture1_->Bind(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		if (eventsManager.type == 0) 
		{
			glDrawElements(GL_TRIANGLE_FAN, mesh_.GetFlatIndices().size(), GL_UNSIGNED_INT, nullptr);
		}
		else if (eventsManager.type == 1)
		{
			glDrawElements(GL_TRIANGLES, mesh_.GetFlatIndices().size(), GL_UNSIGNED_INT, nullptr);
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(
			ImGui::GetDrawData());

		SDL_GL_SwapWindow(window);
	}
}

void WindowShaderGl::imguiWindow()
{
	ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF(
	//	"GreatVibes-Regular.otf", 16.0f, NULL);
	//ImFont* font = io.Fonts->AddFontFromFileTTF(
	//	"c:\\Windows\\Fonts\\wingding.ttf", 18.0f,
	//	NULL);
	//IM_ASSERT(font != NULL);

	const ImU32 flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove;

	float display_width = (float)io.DisplaySize.x;
	float display_height = (float)io.DisplaySize.y;
	ImGui::SetNextWindowPos(
		ImVec2(display_width, display_height),
		ImGuiCond_Always,
		ImVec2(1.f, 1.f));

	ImGui::SetNextWindowSize(
		ImVec2(screenWidth, 150),
		ImGuiCond_Always);

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!", nullptr, flags);
	/*ImGui::Text("This is some useful text.");
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	if (ImGui::Button("Button")) counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/


	/*ImGui::InputFloat("x", &positions[3], 0.01f, 0.1f, 2);
	ImGui::InputFloat("y", &positions[4], 0.01f, 0.1f, 2);

	if (ImGui::Button("Square")) eventsManager.shape = 0;
	ImGui::SameLine();
	if (ImGui::Button("Triangle")) eventsManager.shape = 1;

	if(eventsManager.shape == 0) ImGui::ColorEdit3("Color1", &colors[0]);
	ImGui::ColorEdit3("Color2", &colors[3]);
	ImGui::ColorEdit3("Color3", &colors[6]);
	if (eventsManager.shape == 0) ImGui::ColorEdit3("Color4", &colors[9]);
	ImGui::ColorEdit3("Color5", &colors[12]);*/


	if (ImGui::Button("TRIANGLE_FAN")) eventsManager.type = 0;
	ImGui::SameLine();
	if (ImGui::Button("TRIANGLES")) eventsManager.type = 1;

	ImGui::InputText("Indices", str_indices, IM_ARRAYSIZE(str_indices));
	if (ImGui::Button("Set indices"))
	{
		char str[255];
		strcpy(str, str_indices);
		WindowShaderGl::setIndices(str);
	}
	int n = 1;
	for (int i = 0; i < positions.size(); i += 3, ++n)
	{
		std::string num = std::to_string(n);
		std::string point = "Point " + num;
		ImGui::Text(point.c_str());
		std::string pos = "Position " + num;
		ImGui::InputFloat2(pos.c_str(), &positions[i], 2);
		std::string col = "Color " + num;
		ImGui::ColorEdit3(col.c_str(), &colors[i]);
		std::string remove = "Remove point " + num;
		if (ImGui::Button(remove.c_str())) removePoint(i);
	}

	if (ImGui::Button("Add point")) addPoint();

	ImGui::End();
}

void WindowShaderGl::setIndices(char * str_indices)
{
	char * pch;
	pch = strtok(str_indices, " ,");
	indices.clear();
	while (pch != NULL)
	{
		indices.push_back(std::stoi(std::string(pch)));
		pch = strtok(NULL, " ,");
	}
}

void WindowShaderGl::addPoint()
{
	positions.push_back(0);
	positions.push_back(0);
	positions.push_back(0);
	colors.push_back(1);
	colors.push_back(1);
	colors.push_back(1);
}

void WindowShaderGl::removePoint(int index)
{
	positions.erase(positions.begin() + index, positions.begin() + index + 3);
	colors.erase(colors.begin() + index, colors.begin() + index + 3);
	std::string str = "";
	for (int i = 0; i < indices.size(); i++) 
	{
		if (indices[i] == index/3)
		{
			indices.erase(indices.begin() + i);
			--i;
			continue;
		}
		else if (indices[i] > index/3)
		{
			indices[i]--;
		}
		str += std::to_string(indices[i]);
		str += ",";
	}
	str.pop_back();
	strcpy(str_indices, str.c_str());
}

void WindowShaderGl::init()
{
	auto sdl_gl_context = SDL_GL_CreateContext(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (GLEW_OK != glewInit())
	{
		printf("R.I.P. Glew :(");
		exit(-1);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(
		window,
		sdl_gl_context);
	char* glsl_version = "#version 430";
	ImGui_ImplOpenGL3_Init(glsl_version);

}
