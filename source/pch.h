#pragma once

#include <iostream>
#if _WIN32
	#define VK_USE_PLATFORM_WIN32_KHR
	#define NOMINMAX
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#if _WIN32
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
#endif

#include <glm/glm.hpp>


#include <vector>
#include <array>
#include <optional>
#include <set>
#include <cstdint> // Necessary for uint32_t
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp

#include <fstream>
#include <map>

// Include core headers
#include "vulkan_api/Debugger.h"
#include "vulkan_api/Instance.h"
#include "platform/Surface.h"
#include "platform/windows/WindowSurface.h"
#include "vulkan_api/PhysicalDevice.h"
#include "vulkan_api/Device.h"
#include "vulkan_api/Swapchain.h"
#include "vulkan_api/Shader.h"
#include "vulkan_api/Vertex.h"
#include "vulkan_api/RenderPass.h"
#include "vulkan_api/Pipeline.h"
#include "vulkan_api/Framebuffer.h"

#include "vulkan_api/VertexBuffer.h"

#include "vulkan_api/CommandPool.h"
#include "vulkan_api/CommandBuffer.h"

#include "vulkan_api/synchronization/Fence.h"
#include "vulkan_api/synchronization/Semaphore.h"
#include "vulkan_api/synchronization/Presenter.h"

#include "Application.h"