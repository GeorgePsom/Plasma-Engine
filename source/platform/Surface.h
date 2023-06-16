#pragma once


class Surface
{
public:
	//Surface(GLFWwindow& window, const VkInstance& instance);
	VkSurfaceKHR* GetSurface() { return &surface; }
	void Destroy(const VkInstance& instance);
protected:

	VkSurfaceKHR surface;
};