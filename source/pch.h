#pragma once

#include <iostream>
#if _WIN32
	#define VK_USE_PLATFORM_WIN32_KHR
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#if _WIN32
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
#endif
#include <vector>
#include <optional>
#include <set>

// Include core headers
#include "vulkan_api/Debugger.h"
#include  "vulkan_api/Instance.h"
#include "platform/Surface.h"
#include "platform/windows/WindowSurface.h"
#include "vulkan_api/PhysicalDevice.h"
#include "vulkan_api/Device.h"
#include "Application.h"