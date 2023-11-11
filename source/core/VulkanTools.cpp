#include "pch.h"

namespace Tools
{
	std::string errorString(VkResult errorCode)
	{
		switch (errorCode)
		{
#define STR(r) case VK_ ##r: return #r
			STR(NOT_READY);
			STR(TIMEOUT);
			STR(EVENT_SET);
			STR(EVENT_RESET);
			STR(INCOMPLETE);
			STR(ERROR_OUT_OF_HOST_MEMORY);
			STR(ERROR_OUT_OF_DEVICE_MEMORY);
			STR(ERROR_INITIALIZATION_FAILED);
			STR(ERROR_DEVICE_LOST);
			STR(ERROR_MEMORY_MAP_FAILED);
			STR(ERROR_LAYER_NOT_PRESENT);
			STR(ERROR_EXTENSION_NOT_PRESENT);
			STR(ERROR_FEATURE_NOT_PRESENT);
			STR(ERROR_INCOMPATIBLE_DRIVER);
			STR(ERROR_TOO_MANY_OBJECTS);
			STR(ERROR_FORMAT_NOT_SUPPORTED);
			STR(ERROR_SURFACE_LOST_KHR);
			STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
			STR(SUBOPTIMAL_KHR);
			STR(ERROR_OUT_OF_DATE_KHR);
			STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
			STR(ERROR_VALIDATION_FAILED_EXT);
			STR(ERROR_INVALID_SHADER_NV);
			STR(ERROR_INCOMPATIBLE_SHADER_BINARY_EXT);
#undef STR
		default:
			return "UKNOWN_ERROR";
		}
	}

	void exitFatal(const std::string& message, int32_t exitCode)
	{
#if defined (_WIN32)
		if (!errorModeSilent)
		{
			MessageBox(NULL, message.c_str(), NULL, MB_OK | MB_ICONERROR);
		}
#endif

#if !defined(__ANDROID__)
		exit(exitCode);
#endif
	}

	void exitFatal(const std::string& message, VkResult resultCode)
	{
		exitFatal(message, (int32_t)resultCode);
	}
}
#if !(defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK))
// iOS & macOS: Sample::getAssetPath() implemented externally to allow access to Objective-C components
const std::string getAssetPath()
{
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
	return "";
#elif defined(VK_EXAMPLE_ASSETS_DIR)
	return VK_EXAMPLE_ASSETS_DIR
#else
	return "./../assets";
#endif	
}
#endif