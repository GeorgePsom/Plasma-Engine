#include "pch.h"

std::array<VkVertexInputAttributeDescription, 2>* Vertex::attributeDescriptions = nullptr;
VkVertexInputBindingDescription* Vertex::bindingDescription = nullptr;

const std::vector<Vertex::Layout> Vertex::vertices =  {
		{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0, 1.0f, 0.0f}},
		{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

void Vertex::CreateBindingDescription()
{
	bindingDescription = new VkVertexInputBindingDescription();
	bindingDescription->binding = 0;
	bindingDescription->stride = sizeof(Layout);
	bindingDescription->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}

void Vertex::CreateAttributeDescriptions()
{
	attributeDescriptions = new std::array<VkVertexInputAttributeDescription, 2>();
	(*attributeDescriptions)[0].binding = 0;
	(*attributeDescriptions)[0].location = 0;
	(*attributeDescriptions)[0].format = VK_FORMAT_R32G32_SFLOAT;
	(*attributeDescriptions)[0].offset = offsetof(Layout, pos);

	(*attributeDescriptions)[1].binding = 0;
	(*attributeDescriptions)[1].location = 1;
	(*attributeDescriptions)[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	(*attributeDescriptions)[1].offset = offsetof(Layout, color);
}
