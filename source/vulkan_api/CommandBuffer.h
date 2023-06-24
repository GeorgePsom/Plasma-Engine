#pragma once


class CommandBuffer
{
public:
	CommandBuffer(const VkDevice& device, const VkCommandPool& commandPool);
	void RecordCommandBuffer(const VkFramebuffer& frameBuffer, const VkRenderPass& renderPass, const VkExtent2D& extent, const VkPipeline& pipeline);
	
	VkCommandBuffer inline GetCommandBuffer() { return commandBuffer; }


private:

	VkCommandBuffer commandBuffer;
};