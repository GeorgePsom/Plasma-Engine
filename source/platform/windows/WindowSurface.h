#pragma once


class WindowSurface : public Surface
{
public:
	WindowSurface(GLFWwindow& window, const VkInstance& instance);
	//const VkSurfaceKHR* GetSurface() const { return &surface; }
private:

	//VkSurfaceKHR surface;
};