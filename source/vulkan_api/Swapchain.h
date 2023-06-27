#pragma once


class Swapchain
{
public:
	Swapchain(GLFWwindow& win, const PhysicalDevice& physicalDevice, const VkDevice& device,/*const SwapChainSupportDetails& swapchainDetails, */const VkSurfaceKHR& surface/* const QueueFamilyIndices& indices*/);
	void  Destroy(const VkDevice& device);
	VkSwapchainKHR inline GetSwapChain() { return swapChain; }
	VkFormat inline GetFormat() { return imageFormat; }
	VkExtent2D inline GetExtent() { return extent; }
	std::vector<VkImageView> inline GetImageViews() { return imageViews; }
	 bool GetNextImageIndex(const VkDevice& device, const VkSemaphore& semaphore, uint32_t& imageIndex);
	 
private:
	VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow& window);
	void CreateImageViews(const VkDevice& device);

	VkSwapchainKHR swapChain;
	std::vector<VkImage> images;
	VkFormat imageFormat;
	VkExtent2D extent;
	std::vector<VkImageView> imageViews;
	// References of objects from other classes that are required
	/*SwapChainSupportDetails* swapChainSupportDetails;
	
	FamilyIndices* indices;
	VkSurfaceKHR* surface;*/
};