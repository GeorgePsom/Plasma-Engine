#include "pch.h"

Framebuffer::Framebuffer(const VkDevice& device, const VkExtent2D& extent, const std::vector<VkImageView>& swapchainImageViews, const VkRenderPass& renderPass)
{
	swapChainFramebuffers.resize(swapchainImageViews.size());

	for (size_t i = 0; i < swapchainImageViews.size(); i++)
	{
		VkImageView attachments[] =
		{
			swapchainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.height = extent.height;
		framebufferInfo.width = extent.width;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_FALSE)
			throw std::runtime_error("Failed to create framebuffer");
	}
}

void Framebuffer::Destroy(const VkDevice& device)
{
	for (auto framebuffer : swapChainFramebuffers)
	{
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}
}
