#pragma once

class Pipeline
{
public:

	/*struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};*/

	Pipeline(const VkDevice& device, const VkExtent2D& extent,
		const VkPipelineShaderStageCreateInfo& vertex, const VkPipelineShaderStageCreateInfo& fragment,
		const VkRenderPass& renderPass);
	void Destroy(const VkDevice& device);
	VkPipeline inline GetPipeline() { return graphicsPipeline; }

private:

	void CreateVertexInput(const VkVertexInputBindingDescription& bindingDescription, const std::array<VkVertexInputAttributeDescription,2 >& attributeDescription);
	void CreateInputAssembly();
	void CreateDynamicState();
	void CreateViewportScissor(const VkExtent2D& extent);
	void CreateRasterizer();
	void CreateMultisampling();
	void CreateColorBlending();


	VkPipelineVertexInputStateCreateInfo vertexInputState;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineDynamicStateCreateInfo dynamicState;
	VkPipelineViewportStateCreateInfo viewportState;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlending;

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkDynamicState> dynamicStates = {
		   VK_DYNAMIC_STATE_VIEWPORT,
		   VK_DYNAMIC_STATE_SCISSOR
	};

	



};