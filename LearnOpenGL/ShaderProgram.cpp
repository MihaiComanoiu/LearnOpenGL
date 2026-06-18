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

void ShaderProgram::setInt(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void ShaderProgram::setFloat(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void ShaderProgram::setVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setMat3(const std::string& name, const glm::mat3& value)
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setBool(const std::string& name, bool value)
{
    glUniform1i(getUniformLocation(name), (int) value);
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

int ShaderProgram::getUniformLocation(const std::string& name)
{
    auto it = m_UniformCache.find(name);
    if (it != m_UniformCache.end())
        return it->second;

    int location = glGetUniformLocation(m_ShaderProgram, name.c_str());
    if (location == -1)
        std::cerr << "WARNING::SHADER: Uniform " << name << " not found\n";

    m_UniformCache[name] = location;
    return location;

    return 0;
}
