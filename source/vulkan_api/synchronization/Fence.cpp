#include "pch.h"

Fence::Fence(const VkDevice& device, int count)
{
	fences.resize(count);
	VkFenceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	for (size_t i = 0; i < fences.size(); i++)
	{
		if (vkCreateFence(device, &createInfo, nullptr, &fences[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create fence");
	}
	
}

void Fence::Destroy(const VkDevice& device)
{
	for(auto& fence : fences)
		vkDestroyFence(device, fence, nullptr);
}

void Fence::Reset(const VkDevice& device, uint32_t index)
{
	
	vkResetFences(device, 1, &fences[index]);
}

void Fence::Wait(const VkDevice& device, uint32_t index)
{
	vkWaitForFences(device, 1, &fences[index], VK_TRUE, UINT64_MAX);
}
