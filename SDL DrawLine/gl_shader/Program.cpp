#include "Program.h"

Program::Program(const Shader& vertex, const Shader& frag)
{
	programId_ = glCreateProgram();
	glAttachShader(programId_, vertex.glShader);
	glAttachShader(programId_, frag.glShader);
	glLinkProgram(programId_);

}

Program::~Program()
{
	glDeleteProgram(programId_);
}

void Program::Use()
{
	glUseProgram(programId_);
}

void Program::UniformInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(programId_, name.c_str()), value);
}

void Program::UniformBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(programId_, name.c_str()), (int)value);
}

void Program::UniformFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(programId_, name.c_str()), value);
}

void Program::UniformVector2(const std::string& name, const algebra::Vec2<float>& value)
{
	glUniform2f(glGetUniformLocation(programId_, name.c_str()), value.x, value.y);
}

void Program::UniformVector3(const std::string& name, const algebra::Vec3<float>& value)
{
	glUniform3f(glGetUniformLocation(programId_, name.c_str()), value.x, value.y, value.z);
}

void Program::UniformVector4(const std::string& name, const algebra::Vec4<float>& value)
{
	glUniform4f(glGetUniformLocation(programId_, name.c_str()), value.x, value.y, value.z, value.w);
}

void Program::UniformMatrix4(const std::string& name, const algebra::Matrix4<float>& value, bool transpose)
{
	glUniformMatrix4fv(
		glGetUniformLocation(programId_, name.c_str()),
		1,
		transpose ? GL_TRUE : GL_FALSE,
		&value.m11);
}
