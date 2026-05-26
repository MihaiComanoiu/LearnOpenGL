#pragma once

#include <string>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void compile();
	void use();
private:
	std::string loadShader(const std::string& path);
	unsigned int compileShader(unsigned int type, const std::string& path);
private:
	const std::string m_VertexShaderPath;
	const std::string m_FragmentShaderPath;

	unsigned int m_ShaderProgram;
};

