#pragma once

class Instance
{
public:
	Instance();
	~Instance() { Destroy(); }
	void PrintSupportedExtensions();
	void FindSupportedExtensions();
	void Destroy();
private:
	VkInstance instance;
	std::vector<const char*> requiredExtensions;
	std::vector<VkExtensionProperties> supportedExtensions;
};