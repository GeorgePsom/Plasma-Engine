#include "engine.h"
#include "instance.h"



Engine::Engine()
{
	if (debugMode)
		std::cout << "Making a graphics engine\n";

	build_glfw_window();

	make_instance();
}

void Engine::make_instance()
{
	instance = vkInit::make_instance(debugMode, "Plasma Engine");
}

void Engine::build_glfw_window()
{
	// Init glfw
	glfwInit();

	//no default rendering client, hook up vulkan later
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	// resizing breaks the swapchain, disable it for now
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (window = glfwCreateWindow(width, height, "Vulkan Game Engine", nullptr, nullptr))
	{
		if (debugMode)
			std::cout << "Window created successfully\n";
		else
			std::cout << "Window creation failed!\n";

	}

}

Engine::~Engine()
{
	if (debugMode)
		std::cout << "Exiting...\n";

	//terminate glfw
	glfwTerminate();
}