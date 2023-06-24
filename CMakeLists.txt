cmake_minimum_required(VERSION 3.21)
project(PlasmaEngine)

set(CMAKE_CXX_STANDARD 17)
# Specify the Vulkan SDK path
set(VULKAN_SDK_PATH "D:/VulkanSDK/1.3.250.0" CACHE STRING "Path to the Vulkan SDK")
#set(VULKAN_SDK_PATH "C:/VulkanSDK/1.3.250.0" CACHE STRING "Path to the Vulkan SDK")


add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)


include_directories(libraries/glm)
include_directories(${VULKAN_SDK_PATH}/Include)
include_directories(source)

link_directories(${VULKAN_SDK_PATH}/Lib)
set (SOURCE
	source/main.cpp
	source/Application.cpp
	source/vulkan_api/Instance.cpp
	source/vulkan_api/Debugger.cpp
	source/vulkan_api/PhysicalDevice.cpp
	source/vulkan_api/Device.cpp
	source/platform/Surface.cpp
	source/platform/windows/WindowSurface.cpp
	source/vulkan_api/Swapchain.cpp
	source/vulkan_api/Shader.cpp
	source/vulkan_api/Pipeline.cpp
	source/vulkan_api/RenderPass.cpp
	source/vulkan_api/Framebuffer.cpp
	source/vulkan_api/CommandPool.cpp
	source/vulkan_api/CommandBuffer.cpp
)

set (HEADER
	source/Application.h
	source/vulkan_api/Instance.h
	source/vulkan_api/Debugger.h
	source/vulkan_api/PhysicalDevice.h
	source/vulkan_api/Device.h
	source/platform/Surface.h
	source/platform/windows/WindowSurface.h
	source/vulkan_api/Swapchain.h
	source/vulkan_api/Shader.h
	source/vulkan_api/Pipeline.h
	source/vulkan_api/RenderPass.h
	source/vulkan_api/Framebuffer.h
	source/vulkan_api/CommandPool.h
	source/vulkan_api/CommandBuffer.h

)

set (SHADER
	source/shaders/basic.vert
	source/shaders/basic.frag
)

# Create a custom target for the shaders
add_custom_target(shaders SOURCES ${SHADER})
set_target_properties(shaders PROPERTIES FOLDER "shaders")


add_executable(PlasmaEngine "source/pch.h"  "source/pch.cpp" ${HEADER} ${SOURCE})
add_dependencies(PlasmaEngine shaders)


set(PCH_HEADER pch.h)
set(PCH_SOURCE source/pch.cpp)

set_source_files_properties(${PCH_SOURCE} PROPERTIES COMPILE_FLAGS "/Yc${PCH_HEADER}")
set_source_files_properties(${SOURCE} PROPERTIES COMPILE_FLAGS "/Yu${PCH_HEADER}")

set_source_files_properties(${SOURCE_VULKAN_API} PROPERTIES COMPILE_FLAGS "/Yu${PCH_HEADER}")

target_link_libraries(PlasmaEngine glfw)
if(WIN32)
	target_link_libraries(PlasmaEngine ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib)
endif()

if(UNIX)
	target_link_libraries(PlasmaEngine vulkan)
endif()