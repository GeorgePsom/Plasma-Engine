#pragma once

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value();
	}
};

class PhysicalDevice
{
public:

	PhysicalDevice(const VkInstance& instance);
	const VkPhysicalDevice GetDevice() const { return physicalDevice; }
	QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;

private:

	bool IsDeviceSuitable(const VkPhysicalDevice& device);
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};