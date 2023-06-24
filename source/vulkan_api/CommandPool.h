#pragma once


// Manages the memory that is used to store the buffers and command buffers.
class CommandPool
{
public:
	CommandPool(const VkDevice& device, uint32_t graphicsFamilyIndex);
	void Destroy(const VkDevice& device);
	VkCommandPool inline GetCommandPool() { return commandPool; }
private:

	VkCommandPool commandPool;
};