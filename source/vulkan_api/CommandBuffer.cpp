#include "pch.h"

CommandBuffer::CommandBuffer(const VkDevice& device, const VkCommandPool& commandPool, int count)
{
	commandBuffers.resize(count);
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate command buffers");
}

void CommandBuffer::Record(const VkFramebuffer& frameBuffer, const VkRenderPass& renderPass, const VkExtent2D& extent, const VkPipeline& pipeline, int index)
{
	Reset(index);
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;

	if (vkBeginCommandBuffer(commandBuffers[index], &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("Failed to begin recording command buffer");

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = frameBuffer;
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent;
	VkClearValue clearColor = { {0.0f, 0.0f, 0.0f, 1.0f} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;
	vkCmdBeginRenderPass(commandBuffers[index], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(commandBuffers[index], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(extent.width);
	viewport.height = static_cast<float>(extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffers[index], 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.extent = extent;
	scissor.offset = { 0, 0 };
	vkCmdSetScissor(commandBuffers[index], 0, 1, &scissor);

	vkCmdDraw(commandBuffers[index], 3, 1, 0, 0);

	vkCmdEndRenderPass(commandBuffers[index]);

	if (vkEndCommandBuffer(commandBuffers[index]) != VK_SUCCESS)
		throw std::runtime_error("Failed to record command buffer");

};

void CommandBuffer::Reset(int index)
{
	vkResetCommandBuffer(commandBuffers[index], 0);
}
