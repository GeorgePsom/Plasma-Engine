#pragma once


class Fence
{
public:
	Fence(const VkDevice& device, int count);
	void Destroy(const VkDevice& device);
	void Reset(const VkDevice& device, uint32_t index);
	void Wait(const VkDevice& device, uint32_t index);
	VkFence inline GetFence(uint32_t index) { return fences[index]; }

private:
	std::vector<VkFence> fences;
};