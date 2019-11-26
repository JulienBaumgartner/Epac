#include "WindowShaderGl.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include "Shader.h"


WindowShaderGl::WindowShaderGl(int width, int height, std::shared_ptr<EventsManagerShaderGl> events_manager)
{
	screenWidth = width;
	screenHeight = height;
	eventsManager = events_manager;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	init();
}


WindowShaderGl::~WindowShaderGl()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void WindowShaderGl::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, nullptr);

	SDL_GL_SwapWindow(window);
}


static std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
void WindowShaderGl::run()
{
	SDL_Event event;
	bool loop = true;
	lastUpdateTitle = startTime;
	SDL_GL_SetSwapInterval(0);

	float points[] = {
	  0.0f,  0.0f,  0.0f,
	  0.0f,  0.5f,  0.0f,
	  0.5f,  0.0f,  0.0f,
	  0.0f, -0.5f,  0.0f,
	 -0.5f,  0.0f,  0.0f
	};

	float colors[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f };

	unsigned int indices[] = {0, 1, 2, 3, 4, 1};

	glEnable(GL_DEBUG_OUTPUT);
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), points, GL_STATIC_DRAW);
	
	GLuint cbo = 0;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER,
		15 * sizeof(float),
		colors,
		GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		6 * sizeof(unsigned int),
		indices,
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

	GLuint shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, fs.glShader);
	glAttachShader(shaderProgram_, vs.glShader);
	glLinkProgram(shaderProgram_);
	glUseProgram(shaderProgram_);

	glDebugMessageCallback(
		WindowShaderGl::debugMessage,
		nullptr);
	

	while (loop)
	{
		

		auto currentTime = std::chrono::system_clock::now();
		framesTime.push_back(currentTime);

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
			loop = eventsManager->manageEvents(event);
		}

		render();
	}

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

}
