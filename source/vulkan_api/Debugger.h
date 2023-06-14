#pragma once

class Debugger
{
public:
	Debugger(bool value) : enableValidationLayers(value) {}
	void SetValidationLayerFlag(bool value);
	bool CheckValidationLayerSupport();
	void AddDebugExtension(std::vector<const char*>& extensions);
	inline bool GetValidationFlag() { return enableValidationLayers; }
	const std::vector<const char*>* GetValidationLayers()
	{
		return &validationLayers;
	}

	

	//VkDebugUtilsMessengerEXT debugMessenger = { nullptr };

	//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
	//	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	//	const VkAllocationCallbacks* pAllocator,
	//	VkDebugUtilsMessengerEXT* pDebugMessenger);

	//void DestroyDebugUtilsMessengerEXT(VkInstance instance,
	//	VkDebugUtilsMessengerEXT debugMessenger,
	//	const VkAllocationCallbacks* pAllocator);
	//
	//void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	//void SetupDebugMessenger(const VkInstance& instance);
private:

	

	bool enableValidationLayers;
	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};
};