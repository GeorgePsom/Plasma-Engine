#include "pch.h"

Shader::Shader(const std::string& filename, const VkDevice& device)
{
	auto shaderCode = ReadFile(filename);
	CreateShaderModule(shaderCode, device);
	CreatePipelineShaderStageCI(FindShaderType(filename));

}

void Shader::Destroy(const VkDevice& device)
{
	vkDestroyShaderModule(device, shaderModule, nullptr);
}

std::vector<char> Shader::ReadFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + filename);

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

void Shader::CreateShaderModule(const std::vector<char>& code, const VkDevice& device)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
		throw std::runtime_error("Failed to create shader module");

}

void Shader::CreatePipelineShaderStageCI(VkShaderStageFlagBits type)
{
	pipelineShaderStageCI.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	pipelineShaderStageCI.stage = type;
	pipelineShaderStageCI.module = shaderModule;
	pipelineShaderStageCI.pName = "main";
}

VkShaderStageFlagBits Shader::FindShaderType(const std::string& filename)
{
	std::map<std::string, VkShaderStageFlagBits> types
	{
		{"Vert", VK_SHADER_STAGE_VERTEX_BIT},
		{ "Frag", VK_SHADER_STAGE_FRAGMENT_BIT }
	};
	for (auto type : types)
	{
		if (filename.find(type.first) != std::string::npos)
		{
			return type.second;
		}
		
	}

	throw std::runtime_error("Invalid shader extension of shader: " + filename);
	
}
