#pragma once

class Shader
{
public:
	Shader(const std::string& filename, const VkDevice& device);
	VkShaderModule inline GetShaderModule() { return shaderModule; }
	VkPipelineShaderStageCreateInfo inline GetPiplineShaderStageCI() { return pipelineShaderStageCI; }
	
	void Destroy(const VkDevice& device);
private:

	// TODO create a new utils file and include IO file reading there.
	static std::vector<char> ReadFile(const std::string& filename);
	void CreateShaderModule(const std::vector<char>& code, const VkDevice& device);
	void CreatePipelineShaderStageCI(VkShaderStageFlagBits type);
	VkShaderStageFlagBits FindShaderType(const std::string& filename);
	VkPipelineShaderStageCreateInfo pipelineShaderStageCI;
	VkShaderModule shaderModule;
	
};