#pragma once

class Pipeline
{
public:
	Pipeline(const VkDevice& device);
	void Destroy(const VkDevice& device);

private:

	void CreateVertexInput();
	void CreateInputAssembly();
	void CreateViewportScissor(float width, float height, const VkExtent2D& extent);
	void CreateRasterizer();
	void CreateMultisampling();
	void CreateColorBlending();


	VkPipelineVertexInputStateCreateInfo vertexInputState;
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo viewportState;
	VkPipelineRasterizationStateCreateInfo rasterizer;
	VkPipelineMultisampleStateCreateInfo multisampling;
	VkPipelineColorBlendAttachmentState colorBlendAttachment;
	VkPipelineColorBlendStateCreateInfo colorBlending;

	VkPipelineLayout pipelineLayout;




};