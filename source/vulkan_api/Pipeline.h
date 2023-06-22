#pragma once

class Pipeline
{
public:
	Pipeline(const VkDevice& device, const VkExtent2D& extent,
		const VkPipelineShaderStageCreateInfo& vertex, const VkPipelineShaderStageCreateInfo& fragment,
		const VkRenderPass& renderPass);
	void Destroy(const VkDevice& device);

private:

	void CreateVertexInput();
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