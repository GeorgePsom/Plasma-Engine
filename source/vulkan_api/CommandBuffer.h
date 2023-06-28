#pragma once


class CommandBuffer
{
public:
	CommandBuffer(const VkDevice& device, const VkCommandPool& commandPool, int count);
	void Record(const VkFramebuffer& frameBuffer, const VkRenderPass& renderPass, const VkExtent2D& extent, const VertexBuffer& vb, const VkPipeline& pipeline, int index);
	void Reset(int index);
	VkCommandBuffer inline GetCommandBuffer(int index) { return commandBuffers[index]; }


private:

	std::vector<VkCommandBuffer> commandBuffers;
};