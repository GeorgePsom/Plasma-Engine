#pragma once

class Device
{
public:
	Device(const PhysicalDevice& physicalDevice, bool debug);
	~Device() { Destroy(); }
	void Destroy() { vkDestroyDevice(device, nullptr); }
	const VkDevice* GetDevice() const{ return &device; }
	VkQueue inline GetGraphicsQueue() { return graphicsQueue; }
	VkQueue inline GetPresentQueue() { return presentQueue;}
	

private:

	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
};
