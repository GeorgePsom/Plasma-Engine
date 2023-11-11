#include "pch.h"

std::vector<const char*> Sample::args;

VkResult Sample::createInstance(bool enableValidation)
{
	this->settings.validation = enableValidation;
#if defined(_VALIDATION)
	this->settings.validation = true;
#endif

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = name.c_str();
	appInfo.pEngineName = name.c_str();
	appInfo.apiVersion = apiVersion;

	std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };

#if defined(_WIN32)
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

	uint32_t extCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
	if (extCount > 0)
	{
		std::vector<VkExtensionProperties> extensions(extCount);
		if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
		{
			for (VkExtensionProperties extension : extensions)
				supportedInstanceExtensions.push_back(extension.extensionName);
		}
	}

	if (enabledInstanceExtensions.size() > 0)
	{
		for (const char* enabledExtension : enabledInstanceExtensions)
		{
			if (std::find(supportedInstanceExtensions.begin(),
				supportedInstanceExtensions.end(),
				enabledExtension) == supportedInstanceExtensions.end())
			{
				std::cerr << "Enabled instance extension \"" << enabledExtension << "\" is not present at instance level\n";
			}
			instanceExtensions.push_back(enabledExtension);
		}
	}

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pNext = NULL;
	instanceCreateInfo.pApplicationInfo = &appInfo;

	// Enable the debug utils extension if available (e.g. when debugging tools are present)
	if (settings.validation || std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME) != supportedInstanceExtensions.end()) {
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	if (instanceExtensions.size() > 0)
	{
		instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	}

	const char* validationLayerName = "VK_LAYER_KHRONOS_validation";
	if (settings.validation)
	{
		// check if this layer is available at instance level
		uint32_t instanceLayerCount;
		vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
		std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
		vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());
		bool validationLayerPresent = false;
		for (VkLayerProperties layer : instanceLayerProperties)
		{
			if (strcmp(layer.layerName, validationLayerName) == 0)
			{
				validationLayerPresent = true;
				break;
			}
		}
		if (validationLayerPresent)
		{
			instanceCreateInfo.ppEnabledLayerNames = &validationLayerName;
			instanceCreateInfo.enabledLayerCount = 1;
		}
		else
		{
			std::cerr << "Validation layer VK_KHRONOS_validation is not present, validation is disabled";
		}
	}
	VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);

	// If the debug utils extension is present we set up debug functions, so samples an label objects for debugging
	if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME) != supportedInstanceExtensions.end()) {
		Debug::Setup(instance);
	}
	return result;
}

void Sample::renderFrame()
{
	prepareFrame();
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &drawCmdBuffers[currentBuffer];
	VK_CHECK_RESULT(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));
	submitFrame();
}

Sample::Sample(bool enableValidation)
{
#if !defined(VK_USE_PLATFORM_ANDROID_KHR)
	struct stat info;
	if (stat(getAssetPath().c_str(), &info) != 0)
	{
#if defined(_WIN32)
		std::string msg = "Could not locate asset path in \"" + getAssetPath() + "\" !";
		MessageBox(NULL, msg.c_str(), "Fatal error", MB_OK | MB_ICONERROR);
#endif
		exit(-1);
	}

#endif	
	settings.validation = enableValidation;

	// Command line arguments
	commandLineParser.add("help", { "--help" }, 0, "Show help");
	commandLineParser.add("validation", { "-v", "--validation" }, 0, "Enable validation layers");
	commandLineParser.add("vsync", { "-vs", "--vsync" }, 0, "Enable V-Sync");
	commandLineParser.add("fullscreen", { "-f", "--fullscreen" }, 0, "Start in fullscreen mode");
	commandLineParser.add("width", { "-w", "--width" }, 1, "Set window width");
	commandLineParser.add("height", { "-h", "--height" }, 1, "Set window height");
	commandLineParser.add("shaders", { "-s", "--shaders" }, 1, "Select shader type to use (glsl or hlsl)");
	commandLineParser.add("gpuselection", { "-g", "--gpu" }, 1, "Select GPU to run on");
	commandLineParser.add("gpulist", { "-gl", "--listgpus" }, 0, "Display a list of available Vulkan devices");
	commandLineParser.add("benchmark", { "-b", "--benchmark" }, 0, "Run example in benchmark mode");
	commandLineParser.add("benchmarkwarmup", { "-bw", "--benchwarmup" }, 1, "Set warmup time for benchmark mode in seconds");
	commandLineParser.add("benchmarkruntime", { "-br", "--benchruntime" }, 1, "Set duration time for benchmark mode in seconds");
	commandLineParser.add("benchmarkresultfile", { "-bf", "--benchfilename" }, 1, "Set file name for benchmark results");
	commandLineParser.add("benchmarkresultframes", { "-bt", "--benchframetimes" }, 0, "Save frame times to benchmark results file");
	commandLineParser.add("benchmarkframes", { "-bfs", "--benchmarkframes" }, 1, "Only render the given number of frames");

	commandLineParser.parse(args);

	if (commandLineParser.isSet("help"))
	{
#if defined (_WIN32)
		setupConsole("Plasma Engine");
#endif
		commandLineParser.printHelp();
		std::cin.get();
		exit(0);
	}
	if (commandLineParser.isSet("validation"))
		settings.validation = true;

	if (commandLineParser.isSet("vsync"))
		settings.vsync = true;

	if (commandLineParser.isSet("height"))
		height = commandLineParser.getValueAsInt("height", height);

	if (commandLineParser.isSet("width"))
		width = commandLineParser.getValueAsInt("width", width);

	if (commandLineParser.isSet("fullscreen"))
		settings.fullscreen = true;

	if (commandLineParser.isSet("shaders"))
	{
		std::string value = commandLineParser.getValueAsString("shaders", "glsl");
		if ((value != "glsl") && (value != "hlsl"))
			std::cerr << "Engine only supports glsl and hlsl shaders";
		else
			shaderDir = value;
	}

	if (commandLineParser.isSet("benchmark"))
	{
		benchmark.active = true;
		Tools::errorModeSilent = true;
	}

	if (commandLineParser.isSet("benchmarkwarmup")) 
		benchmark.warmup = commandLineParser.getValueAsInt("benchmarkwarmup", benchmark.warmup);
	
	if (commandLineParser.isSet("benchmarkruntime"))
		benchmark.duration = commandLineParser.getValueAsInt("benchmarkruntime", benchmark.duration);
	
	if (commandLineParser.isSet("benchmarkresultfile"))
		benchmark.filename = commandLineParser.getValueAsString("benchmarkresultfile", benchmark.filename);
	
	if (commandLineParser.isSet("benchmarkresultframes"))
		benchmark.outputFrameTimes = true;

	if (commandLineParser.isSet("benchmarkframes"))
		benchmark.outputFrames = commandLineParser.getValueAsInt("benchmarkframes", benchmark.outputFrames);
	
#if defined(_WIN32)
	// Enable console if validation is active, debug message callback will output to it
	if (settings.validation)
	{
		setupConsole("Plasma Engine");
	}
	setupDPIAwareness();
#endif
}


bool Sample::initVulkan()
{
	VkResult err;

	err = createInstance(settings.validation);
	if (err)
	{
		Tools::exitFatal("Could not create Vulkan instance : \n" + Tools::errorString(err), err);
		return false;
	}

	// Enable validation
	if (settings.validation)
	{
		Debug::setupDebugging(instance);
	}

	// Physical Device
	uint32_t gpuCount = 0;
	// Get number of available physical devices
	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &gpuCount, nullptr));
	if (gpuCount == 0)
	{
		Tools::exitFatal("No device with Vulkan support found", -1);
		return false;
	}

	// Enumerate devices
	std::vector<VkPhysicalDevice> physicalDevices(gpuCount);
	err = vkEnumeratePhysicalDevices(instance, &gpuCount, physicalDevices.data());
	if (err)
	{
		Tools::exitFatal("Could not enumerate physical devices : \n" + Tools::errorString(err), err);
		return false;
	}

	// GPU selection
	// By default selects the first device unless specified by command line.
	uint32_t selectedDevice = 0;
#if !defined(VK_USE_PLATFORM_ANDROID_KHR)
	// GPU selection via command line argument
	if (commandLineParser.isSet("gpuselection"))
	{
		uint32_t index = commandLineParser.getValueAsInt("gpuselection", 0);
		if (index > gpuCount - 1)
		{
			std::cerr << "Selected device index " << index << " is out of range,  reverting to device 0 (use -listgpus to show available Vulkan devices)" << "\n";
		}
		else
		{
			selectedDevice = index;
		}
	}
	if (commandLineParser.isSet("gpulist")) {
		std::cout << "Available Vulkan devices" << "\n";
		for (uint32_t i = 0; i < gpuCount; i++) {
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
			std::cout << "Device [" << i << "] : " << deviceProperties.deviceName << std::endl;
			std::cout << " Type: " << Tools::physicalDeviceTypeString(deviceProperties.deviceType) << "\n";
			std::cout << " API: " << (deviceProperties.apiVersion >> 22) << "." << ((deviceProperties.apiVersion >> 12) & 0x3ff) << "." << (deviceProperties.apiVersion & 0xfff) << "\n";
		}
	}
#endif

}
#if defined(_WIN32)
// Win32 : Sets up a console window and redirects standard output to it
void Sample::setupConsole(std::string title)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	FILE* stream;
	freopen_s(&stream, "CONIN$", "r", stdin);
	freopen_s(&stream, "CONOUT$", "w+", stdout);
	freopen_s(&stream, "CONOUT$", "w+", stderr);
	SetConsoleTitle(TEXT(title.c_str()));
}

void Sample::setupDPIAwareness()
{
	typedef HRESULT* (__stdcall* SetProcessDpiAwarenessFunc)(PROCESS_DPI_AWARENESS);

	HMODULE shCore = LoadLibraryA("Shcore.dll");
	if (shCore)
	{
		SetProcessDpiAwarenessFunc setProcessDpiAwareness =
			(SetProcessDpiAwarenessFunc)GetProcAddress(shCore, "SetProcessDpiAwareness");

		if (setProcessDpiAwareness != nullptr)
		{
			setProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		}

		FreeLibrary(shCore);
	}
}
#endif

