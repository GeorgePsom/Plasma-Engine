#pragma once

namespace Debug
{
	VKAPI_ATTR VkBool32 VKAPI_CALL messageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData);

	void setupDebugging(VkInstance instance);
	void freeDebugCallback(VkInstance instance);

	void setup(VkInstance instance);
	void cmdBegingLabel(VkCommandBuffer cmdBuffer, std::string caption, glm::vec4 color);
	void cmdEndLabel(VkCommandBuffer cmdBuffer);
}
