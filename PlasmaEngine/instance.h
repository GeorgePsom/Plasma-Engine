#pragma once
#include "config.h"



namespace vkInit
{
	vk::Instance make_instance(bool debug, const char* appName)
	{

		uint32_t version{ 0 };
		vkEnumerateInstanceVersion(&version);
		std::cout << "System can support vulkan Variant: " << VK_API_VERSION_VARIANT(version)
			<< ", Major: " << VK_API_VERSION_MAJOR(version)
			<< ", Minor: " << VK_API_VERSION_MINOR(version)
			<< ", Patch: " << VK_API_VERSION_PATCH(version) << std::endl;

		// Set patch to zero for best compatibility
		version &= ~(0xFFFU);

		// We can also drop to a lower version
		version = VK_MAKE_API_VERSION(0, 1, 0, 0);

		vk::ApplicationInfo appInfo = vk::ApplicationInfo(
			appName,
			version,
			"Plasma Engine",
			version,
			version
		);

		// Query glfw extensions to inferface with vulkan
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		
		if (debug)
		{
			std::cout << "extensions to be requested:\n";

			for (const char* extensionName : extensions)
			{
				std::cout << "\t\"" << extensionName << "\"\n";
			}
		}

		vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
			vk::InstanceCreateFlags(),
			&appInfo,
			0, nullptr, // enabled layers
			static_cast<uint32_t>(extensions.size()), extensions.data()
		);
		

		try
		{
			return vk::createInstance(createInfo, nullptr);
		}
		catch (vk::SystemError err)
		{
			if (debug)
				std::cout << "Failed to create instance!\n";
		
			return nullptr;
		}

	}

}

