#include "pch.h"


VertexBuffer::VertexBuffer(const VkPhysicalDevice& physicalDevice, const VkDevice& device)
{

	// Create vertex buffer
	VkBufferCreateInfo creationInfo{};
	creationInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	creationInfo.size = sizeof(Vertex::Layout) * Vertex::vertices.size();
	creationInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	creationInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	
	if (vkCreateBuffer(device, &creationInfo, nullptr, &buffer) != VK_SUCCESS)
		throw std::runtime_error("Failed to create vertex buffer");
	// Allocate memory
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(physicalDevice, memRequirements.memoryTypeBits,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(device, &allocInfo, nullptr, &memory) != VK_SUCCESS)
		throw std::runtime_error("Failed to allocate vertex buffer memory");

	// Bind
	vkBindBufferMemory(device, buffer, memory, 0);

	// Copy data to vertex buffer
	void* data;
	vkMapMemory(device, memory, 0, creationInfo.size, 0, &data);
	memcpy(data, Vertex::vertices.data(), (size_t)creationInfo.size);
	vkUnmapMemory(device, memory);


}

void VertexBuffer::Destroy(const VkDevice& device)
{
	vkDestroyBuffer(device, buffer, nullptr);
	vkFreeMemory(device, memory, nullptr);
}

void VertexBuffer::Bind(const VkCommandBuffer& cmdBuffer) const
{
	VkBuffer vertexBuffers[] = { buffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, vertexBuffers, offsets);
}

uint32_t VertexBuffer::FindMemoryType(const VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{

	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if (typeFilter & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			return i;
	}

	throw std::runtime_error("Failed to find the suitable memory type");
}
