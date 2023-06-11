#include "pch.h"



void Application::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Destroy();
}

void Application::InitWindow()
{
	glfwInit();
	// GLFW was initially designed for OpenGL, so no need to tell it not to create OpenGL context.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	// Disable resizable for now. It required extra work.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	m_pWindow = glfwCreateWindow(m_width, m_height, "Plasma Engine", nullptr, nullptr);
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
	}
}

void Application::Destroy()
{
	m_pInstance->Destroy();
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void Application::InitVulkan()
{
	m_pInstance = new Instance();
	m_pInstance->PrintSupportedExtensions();
}