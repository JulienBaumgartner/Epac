#pragma once
#include "Shader.h"
#include "../DrawLine/Algebra.h"

class Program
{
public:
	Program(const Shader& vertex, const Shader& frag);
	virtual ~Program();
	void Use();
	void UniformInt(const std::string& name, int value);
	void UniformBool(const std::string& name, bool value);
	void UniformFloat(const std::string& name, float value);
	void UniformVector2(const std::string& name, const algebra::Vec2<float>& value);
	void UniformVector3(const std::string& name, const algebra::Vec3<float>& value);
	void UniformVector4(const std::string& name, const algebra::Vec4<float>& value);
	void UniformMatrix4(const std::string& name, const algebra::Matrix4<float>& value, bool transpose = false);
private:
	int programId_;
};