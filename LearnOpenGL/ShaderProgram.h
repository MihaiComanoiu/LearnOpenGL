#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void compile();
	void use();

	// Uniform setters
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setMat3(const std::string& name, const glm::mat3& value);
	void setMat4(const std::string& name, const glm::mat4& value);
	void setBool(const std::string& name, bool value);
private:
	std::string loadShader(const std::string& path);
	unsigned int compileShader(unsigned int type, const std::string& path);

	int getUniformLocation(const std::string& name);
private:
	const std::string m_VertexShaderPath;
	const std::string m_FragmentShaderPath;

	unsigned int m_ShaderProgram;

	std::unordered_map<std::string, int> m_UniformCache;
};

