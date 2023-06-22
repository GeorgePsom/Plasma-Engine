#pragma once

class RenderPass
{
public:

	RenderPass(const VkDevice& device, const VkFormat& swapchainFormat);
	void Destroy(const VkDevice& device);
	VkRenderPass inline GetRenderPass() { return renderPass; }
private:
	VkRenderPass renderPass;
};