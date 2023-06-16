#pragma once

class Device
{
public:
	Device(const PhysicalDevice& physicalDevice, bool debug);
	~Device() { Destroy(); }
	void Destroy() { vkDestroyDevice(device, nullptr); }
private:

	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
};
