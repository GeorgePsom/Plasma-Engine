#include "pch.h"

Swapchain::Swapchain(GLFWwindow& win, const PhysicalDevice& physicalDevice, const VkDevice& device, const VkSurfaceKHR& surface)
{
	SwapChainSupportDetails swapchainDetails = *(physicalDevice.GetSwapChainSupportDetails());
	QueueFamilyIndices indices = (physicalDevice.FindQueueFamilies(physicalDevice.GetDevice()));
	VkSurfaceFormatKHR surfaceFormat = ChooseSurfaceFormat(swapchainDetails.formats);
	VkPresentModeKHR presentMode = ChoosePresentMode(swapchainDetails.presentModes);
	VkExtent2D extent = ChooseExtent(swapchainDetails.capabilities, win);

	uint32_t imageCount = swapchainDetails.capabilities.minImageCount + 1;

	if (swapchainDetails.capabilities.maxImageCount > 0 && imageCount > swapchainDetails.capabilities.maxImageCount)
		imageCount = swapchainDetails.capabilities.maxImageCount;

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1; // Always 1, unless we are developing a 3D stereoscopic application.
	// We will render straight into them. If we are using post-processing then it should be VK_IMAGE_USAGE_TRANSFER_DST_BIT
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if (indices.graphicsFamily != indices.presentFamily)
	{
		
		//  Images can be used across multiple queue families without explicit ownership transfers.
		// We will be using this one for now to avoid the ownership detailed implementation.
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		// An image is owned by one queue family at a time and ownership must be explicitly transferred before using it in another queue family.
		// This option offers the best performance.
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}
	// We do not want a specific transform to be applied
	createInfo.preTransform = swapchainDetails.capabilities.currentTransform;

	// This is for blending between the other windows. Most of the cases we want the alpha channel to be ignored
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	createInfo.presentMode = presentMode;
	// We do not care about the color of the pixel that are obscured, e.g. when another window is in front.
	// Unless we want to read pixels back, clipping should be enabled to achieve best performance.
	createInfo.clipped = VK_TRUE;

	// NULL for now. It is required e.g. in window resizing.
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	images.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, images.data());
	imageFormat = surfaceFormat.format;
	this->extent = extent;

	CreateImageViews(device);

}

void Swapchain::Destroy(const VkDevice& device)
{
	for (size_t i = 0; i < imageViews.size(); i++)
		vkDestroyImageView(device, imageViews[i], nullptr);
	vkDestroySwapchainKHR(device, swapChain, nullptr);
}

VkSurfaceFormatKHR Swapchain::ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB
				&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		}

		// If it fails in most cases it's ok to use the first format
		return availableFormats[0];
	}
}

VkPresentModeKHR Swapchain::ChoosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		// If energy consumption is not an issue. E.g. not in mobile devices.
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return availablePresentMode;
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Swapchain::ChooseExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow& window)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetFramebufferSize(&window, &width, &height);

		VkExtent2D actualExtent =
		{
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		return actualExtent;
	}
}

void Swapchain::CreateImageViews(const VkDevice& device)
{
	imageViews.resize(images.size());

	for (size_t i = 0; i < imageViews.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = images[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = imageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1; // If we had 3D stereoscopic view we would create multiple levels.

		if (vkCreateImageView(device, &createInfo, nullptr, &imageViews[i]) != VK_SUCCESS)
			throw std::runtime_error(" Failed to create swapchain image view!");
	}

}
