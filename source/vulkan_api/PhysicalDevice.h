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


// Properties we will check to query when checking if swapchain will be compatible.
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class PhysicalDevice
{
public:

	PhysicalDevice(const VkInstance& instance, VkSurfaceKHR& surface);
	const VkPhysicalDevice GetDevice() const { return physicalDevice; }
	QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;
	SwapChainSupportDetails* GetSwapChainSupportDetails() { return &swapChainSupportDetails; }

private:

	bool IsDeviceSuitable(const VkPhysicalDevice& device);
	bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);
	SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device);

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	// TODO : maybe with shared_ptr
	VkSurfaceKHR* surface;
	SwapChainSupportDetails swapChainSupportDetails;
};