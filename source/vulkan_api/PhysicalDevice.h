#pragma once

class PhysicalDevice
{
public:

	PhysicalDevice(const VkInstance& instance);
	VkPhysicalDevice* GetDevice() { return &physicalDevice; }

private:

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value();
		}
	};

	bool IsDeviceSuitable(const VkPhysicalDevice& device);
	QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device);

	

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
};