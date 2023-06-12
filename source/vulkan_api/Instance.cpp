#include "pch.h"



Instance::Instance(Debugger& debug)
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Plasma Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Plasma Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// For MacOS to work around the VK_ERROR_INCOMPATIBLE_DRIVER
	for (uint32_t i = 0; i < glfwExtensionCount; i++)
	{
		requiredExtensions.emplace_back(glfwExtensions[i]);
	}

	requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);


	// Check for validation layers if debug on
	debugger = &debug;
	if (debugger != nullptr && debugger->CheckValidationLayerSupport())
	{
		throw::std::runtime_error("Validation layers requested, but not available!");
	}
	if (debugger != nullptr && debugger->GetValidationFlag())
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(debugger->GetValidationLayers()->size());
		createInfo.ppEnabledLayerNames = debugger->GetValidationLayers()->data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}
	createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
	createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		throw::std::runtime_error("Failed to create Instance!");
	}
}

void Instance::FindSupportedExtensions()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	supportedExtensions.resize(extensionCount);

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, supportedExtensions.data());
}

void Instance::PrintSupportedExtensions()
{
	std::cout << "available extensions:\n";
	// get the supported extensions in case they have not been retrieved
	if (supportedExtensions.size() == 0)
		FindSupportedExtensions();

	for (const auto& extension : supportedExtensions)
	{
		std::cout << "\t" << extension.extensionName << '\n';
	}
}

void Instance::Destroy()
{
	vkDestroyInstance(instance, nullptr);
}
