#include "ShaderProgram.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	: m_ShaderProgram(0), m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
{
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ShaderProgram);
}

void ShaderProgram::compile()
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, m_VertexShaderPath);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_FragmentShaderPath);

    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, vertexShader);
    glAttachShader(m_ShaderProgram, fragmentShader);
    glLinkProgram(m_ShaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::LINKING: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::use()
{
    glUseProgram(m_ShaderProgram);
}

std::string ShaderProgram::loadShader(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Failed to open shader file: " << path << std::endl;
		return "";
	}

	std::stringstream ss;
	ss << file.rdbuf();
    return ss.str();
}

unsigned int ShaderProgram::compileShader(unsigned int type, const std::string& path)
{
    std::string code = loadShader(path);
    const char* src = code.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
    }
    return shader;
}
