#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& device, const VkQueue& queue, const VkCommandPool& commandPool);
	VertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
		VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void Destroy(const VkDevice& device);
	void Bind(const VkCommandBuffer& cmdBuffer)const;
	
private:
	void Copy(const VkDevice& device, const VkQueue& queue, VkDeviceSize size, const VkCommandPool& commandPool);


	uint32_t FindMemoryType(const VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkBuffer vertexBuffer, stagingBuffer;
	VkDeviceMemory vertexBufferMemory, stagingBufferMemory;

	/*const std::vector<Pipeline::Vertex> vertices = {
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
	};*/


};