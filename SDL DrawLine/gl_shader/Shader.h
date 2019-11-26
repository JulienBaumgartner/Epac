#pragma once
#include <string>
#include <GL/glew.h>

enum ShaderType
{
	VertexShader,
	FragmentShader
};

class Shader 
{
public:
	Shader(ShaderType type);
	~Shader();

	bool openShader(std::string path);

	GLuint glShader;
	ShaderType shaderType;
	std::string buffer;
	std::string errorMessage;
};