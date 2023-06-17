#pragma once

class Device
{
public:
	Device(const PhysicalDevice& physicalDevice, bool debug);
	~Device() { Destroy(); }
	void Destroy() { vkDestroyDevice(device, nullptr); }
	const VkDevice* GetDevice() const{ return &device; }
private:

	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
};
