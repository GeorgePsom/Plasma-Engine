#include "pch.h"

PhysicalDevice::PhysicalDevice(const VkInstance& instance)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("Failed to find GPUs with Vulkan Support");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Failed to find a suitable GPU");
}

bool PhysicalDevice::IsDeviceSuitable(const VkPhysicalDevice& device)
{
	QueueFamilyIndices indices = FindQueueFamilies(device);
	return indices.isComplete();
}

PhysicalDevice::QueueFamilyIndices PhysicalDevice::FindQueueFamilies(const VkPhysicalDevice& device)
{
	QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;
	
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;
		if (indices.isComplete())
			break;
		i++;
	}

	return indices;
}
