#include "pch.h"

CommandPool::CommandPool(const VkDevice& device, uint32_t graphicsFamilyIndex)
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // we will be reseting and rerecording commands every frame.
	poolInfo.queueFamilyIndex = graphicsFamilyIndex;

	if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		throw std::runtime_error("Failed to create command pool");
}

void CommandPool::Destroy(const VkDevice& device)
{
	vkDestroyCommandPool(device, commandPool, nullptr);
}
