#pragma once

class Framebuffer
{
public:
	Framebuffer(const VkDevice& device, const VkExtent2D& extent, const std::vector<VkImageView>& swapchainImageViews, const VkRenderPass& renderPass);
	void Destroy(const VkDevice& device);
	VkFramebuffer inline GetFramebuffer(uint32_t index) { return swapChainFramebuffers[index]; }
private:

	std::vector<VkFramebuffer> swapChainFramebuffers;

};