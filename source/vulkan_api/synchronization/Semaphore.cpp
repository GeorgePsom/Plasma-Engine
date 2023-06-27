#include "pch.h"


Semaphore::Semaphore(const VkDevice& device, uint32_t count)
{
	semaphores.resize(count);
	VkSemaphoreCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;

	for (size_t i = 0; i < semaphores.size(); i++)
	{
		if (vkCreateSemaphore(device, &createInfo, nullptr, &semaphores[i]) != VK_SUCCESS)
			throw std::runtime_error("Failed to create semaphore");
	}
	
}

void Semaphore::Destroy(const VkDevice& device)
{
	for(auto& semaphore : semaphores)
		vkDestroySemaphore(device, semaphore, nullptr);
}
