#include "Shader.h"
#include <fstream>

Shader::Shader(ShaderType type) : shaderType(type)
{
	if (shaderType == ShaderType::VertexShader)
	{
		glShader = glCreateShader(GL_VERTEX_SHADER);
	}
	else 
	{
		glShader = glCreateShader(GL_FRAGMENT_SHADER);
	}
}

Shader::~Shader()
{

}

bool Shader::openShader(std::string path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		buffer.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		buffer.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		const char* txt = buffer.c_str();
		glShaderSource(glShader, 1, &txt, NULL);
		glCompileShader(glShader);

		int result, length;
		glGetShaderiv(glShader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &length);
			errorMessage.resize(length);
			glGetShaderInfoLog(
				glShader, length, &length, &errorMessage[0]);
			return false;
		}
		return true;
	}
	
	errorMessage = "Can't open file " + path;
	return false;
}
