#pragma once


class Presenter
{
public:
	static void Submit(const VkCommandBuffer& commandBuffer,
		const VkSemaphore& waitSemaphore, const VkSemaphore& signalSemaphore,
		const VkFence& fence, const VkQueue& queue);
	static bool Present(const VkQueue& queue, const VkSwapchainKHR& swapChain, uint32_t index,  const VkSemaphore& semaphore);


private:	


	
};