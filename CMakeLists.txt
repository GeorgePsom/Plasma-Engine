cmake_minimum_required(VERSION 3.21)
project(PlasmaEngine)

set(CMAKE_CXX_STANDARD 17)
# Specify the Vulkan SDK path
set(VULKAN_SDK_PATH "D:/VulkanSDK/1.3.250.0" CACHE STRING "Path to the Vulkan SDK")


add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)


include_directories(libraries/glm)
include_directories(${VULKAN_SDK_PATH}/Include)
include_directories(source)

link_directories(${VULKAN_SDK_PATH}/Lib)


add_executable(PlasmaEngine "source/main.cpp" "source/Application.h" "source/Application.cpp" "source/vulkan_api/Instance.h" "source/pch.h" "source/vulkan_api/Instance.cpp" "source/pch.cpp")

set(SOURCE
source/main.cpp
source/Application.cpp
#source/vulkan_api/Instance.cpp

)

set(SOURCE_VULKAN_API
source/vulkan_api/Instance.cpp)
set(PCH_HEADER pch.h)
set(PCH_HEADER_NOT_SOURCE ../pch.h)

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