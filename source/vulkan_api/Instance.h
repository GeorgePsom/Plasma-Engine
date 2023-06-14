#pragma once

class Instance
{
public:
	Instance(Debugger& debugger);
	~Instance() { Destroy(); }
	void PrintSupportedExtensions();
	void FindSupportedExtensions();
	void Destroy();
	VkInstance GetInstance() { return instance; }
private:
	VkDebugUtilsMessengerEXT debugMessenger;
	VkInstance instance;
	void SetupDebugMessenger();
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	std::vector<const char*> requiredExtensions;
	std::vector<VkExtensionProperties> supportedExtensions;
	Debugger* debugger;
};