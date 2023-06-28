#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& device);
	void Destroy(const VkDevice& device);
	void Bind(const VkCommandBuffer& cmdBuffer)const;
private:

	uint32_t FindMemoryType(const VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkBuffer buffer;
	VkDeviceMemory memory;

	/*const std::vector<Pipeline::Vertex> vertices = {
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
	};*/


};