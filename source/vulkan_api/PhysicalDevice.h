#pragma once

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class PhysicalDevice
{
public:

	PhysicalDevice(const VkInstance& instance, VkSurfaceKHR& surface);
	const VkPhysicalDevice GetDevice() const { return physicalDevice; }
	QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;

private:

	bool IsDeviceSuitable(const VkPhysicalDevice& device);
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	// TODO : maybe with shared_ptr
	VkSurfaceKHR* surface;
};