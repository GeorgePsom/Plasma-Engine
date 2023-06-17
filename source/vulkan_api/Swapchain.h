#pragma once


class Swapchain
{
public:
	Swapchain(GLFWwindow& win, const PhysicalDevice& physicalDevice, const VkDevice& device,/*const SwapChainSupportDetails& swapchainDetails, */const VkSurfaceKHR& surface/* const QueueFamilyIndices& indices*/);
	void  Destroy(const VkDevice& device);
private:
	VkSurfaceFormatKHR ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChoosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow& window);

	VkSwapchainKHR swapChain;
	// References of objects from other classes that are required
	/*SwapChainSupportDetails* swapChainSupportDetails;
	QueueFamilyIndices* indices;
	VkSurfaceKHR* surface;*/
};