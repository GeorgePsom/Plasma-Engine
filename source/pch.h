#pragma once

#ifdef _WIN32
#pragma comment(linker, "/subsystem:windows")
#include <windows.h>
#include <ShellScalingAPI.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#endif

#include "vulkan/vulkan.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <algorithm>


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

//#if _WIN32
//	#define VK_USE_PLATFORM_WIN32_KHR
//	#define NOMINMAX
//#endif
//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
//#if _WIN32
//	#define GLFW_EXPOSE_NATIVE_WIN32
//	#include <GLFW/glfw3native.h>
//#endif
//
//#include <glm/glm.hpp>
//
//
//#include <vector>
//#include <array>
//#include <optional>
//#include <set>
//#include <cstdint> // Necessary for uint32_t
//#include <limits> // Necessary for std::numeric_limits
//#include <algorithm> // Necessary for std::clamp
//
//#include <fstream>
//#include <map>

#include "core/VulkanSwapChain.h"
#include "core/UIOverlay.h"
#include "core/CommandLineParser.hpp"
#include "core/Benchmark.hpp"
#include "core/VulkanDevice.h"
#include "core/VulkanDebug.h"
#include "core/VulkanTools.h"
#include "core/Camera.hpp"
#include "core/Sample.h"

// Include core headers
//#include "vulkan_api/Debugger.h"
//#include "vulkan_api/Instance.h"
//#include "platform/Surface.h"
//#include "platform/windows/WindowSurface.h"
//#include "vulkan_api/PhysicalDevice.h"
//#include "vulkan_api/Device.h"
//#include "vulkan_api/Swapchain.h"
//#include "vulkan_api/Shader.h"
//#include "vulkan_api/Vertex.h"
//#include "vulkan_api/RenderPass.h"
//#include "vulkan_api/Pipeline.h"
//#include "vulkan_api/Framebuffer.h"
//
//#include "vulkan_api/VertexBuffer.h"
//
//#include "vulkan_api/CommandPool.h"
//#include "vulkan_api/CommandBuffer.h"
//
//#include "vulkan_api/synchronization/Fence.h"
//#include "vulkan_api/synchronization/Semaphore.h"
//#include "vulkan_api/synchronization/Presenter.h"
//
//#include "Application.h"