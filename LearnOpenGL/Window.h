#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
	Window(const std::string& title, int width, int height);
	~Window();

	int init();
	void run();
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput();
private:
	GLFWwindow* m_Window;
	std::string m_Title;
	int m_Width, m_Height;
};

