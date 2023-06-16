#include "pch.h"

void Surface::Destroy(const VkInstance& instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
