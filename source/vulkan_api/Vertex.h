#pragma once

class Vertex
{
public:

	struct Layout
	{
		glm::vec2 pos;
		glm::vec3 color;
	};

	static const std::vector<Layout> vertices;

	static VkVertexInputBindingDescription inline GetBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Layout);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;

	}
	static std::array<VkVertexInputAttributeDescription, 2> inline GetAttributeDescritpions() {
		
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Layout, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Layout, color);

		return attributeDescriptions;
	}
	

private:
	
	static void CreateBindingDescription();
	static void CreateAttributeDescriptions();
	static VkVertexInputBindingDescription* bindingDescription;
	static std::array<VkVertexInputAttributeDescription, 2>* attributeDescriptions;
};