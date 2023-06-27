#pragma once

class Semaphore
{
public:
	Semaphore(const VkDevice& device, uint32_t count);
	void Destroy(const VkDevice& device);
	VkSemaphore inline GetSemaphore(uint32_t index) { return semaphores[index]; }
private:
	std::vector<VkSemaphore> semaphores;
};