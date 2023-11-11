#pragma once

class Sample
{
private:
	std::string getWindowTitle();
	uint32_t dstWidth;
	uint32_t dstHeight;
	bool resizing = false;
	void handleMouseMove(int32_t x, int32_t y);
	void nextFrame();
	void updateOverlay();
	void createPipelineCache();
	void createCommandPool();
	void createSynchronizationPrimitives();
	void initSwapchain();
	void setupSwapchain();
	void createCommandBuffers();
	void destroyCommandBuffers();
	std::string shaderDir = "glsl";
protected:
	std::string getShadersPath() const;

	uint32_t frameCounter = 0;
	uint32_t lastFps = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTimestamp, tPrevEnd;
	
	
	VkInstance instance;
	std::vector<std::string> supportedInstanceExtensions;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
	VkPhysicalDeviceFeatures enabledFeatures{};
	std::vector<const char*> enabledDeviceExtensions;
	std::vector<const char*> enabledInstanceExtensions;
	void* deviceCreatepNextChain = nullptr;
	VkDevice device;
	VkQueue queue;
	VkFormat depthFormat;
	VkCommandPool cmdPool;
	VkPipelineStageFlags submitPipelineStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	VkSubmitInfo submitInfo;
	std::vector<VkCommandBuffer> drawCmdBuffers;
	VkRenderPass renderPass = VK_NULL_HANDLE;
	std::vector<VkFramebuffer> frameBuffers;
	uint32_t currentBuffer = 0;
	VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
	std::vector<VkShaderModule> shaderModules;
	VkPipelineCache pipelineCache;
	VulkanSwapChain swapChain;
	struct
	{
		VkSemaphore presentComplete;
		VkSemaphore renderComplete;
	} semaphores;

	std::vector<VkFence> waitFences;
	bool requiresStencil{ false };
public:
	bool prepared = false;
	bool resized = false;
	bool viewUpdated = false;
	uint32_t width = 1280;
	uint32_t height = 720;
	
	UIOverlay UIOverlay;
	CommandLineParser commandLineParser;

	float frameTimer = 1.0f;
	Benchmark benchmark;

	VulkanDevice* vulkanDevice;
	struct Settings
	{
		bool validation = false;
		bool fullscreen = false;
		bool vsync = false;
		bool overlay = true;
	}settings;

	VkClearColorValue defaultClearColor = { {0.025f, 0.025f, 0.025f, 1.0f} };

	static std::vector<const char*> args;

	float timer = 0.0f;
	float timerSpeed = 0.25f;
	bool paused = false;

	Camera camera;
	glm::vec2 mousePos;

	std::string title = "Vulkan Example";
	std::string name = "vulkanExample";
	uint32_t apiVersion = VK_API_VERSION_1_0;

	struct
	{
		VkImage image;
		VkDeviceMemory mem;
		VkImageView view;
	} depthStencil;

	struct
	{
		glm::vec2 axisLeft = glm::vec2(0.0f);
		glm::vec2 axisRight = glm::vec2(0.0f);
	} gamePadState;

	struct
	{
		bool left = false;
		bool right = false;
		bool middle = false;
	} mouseButtons;

#if defined(_WIN32)
	HWND window;
	HINSTANCE windowInstance;
#endif

	Sample(bool enableValidation = false);
	virtual ~Sample();
	bool initVulkan();

#if defined(_WIN32)
	void setupConsole(std::string title);
	void setupDPIAwareness();
	HWND setupWindow(HINSTANCE hInstance, WNDPROC wndproc);
	void handleMessages(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

	virtual VkResult createInstance(bool enableValidation);
	virtual void render() = 0;
	virtual void cameraChanged();
	virtual void keyPressed(uint32_t);
	virtual void mouseMoved(double x, double y, bool& handled);
	virtual void windowResized();
	virtual void buildCommandBuffers();
	virtual void setupDepthStencil();
	virtual void setupFrameBuffer();
	virtual void setupRenderPass();
	virtual void getEnabledFeatures();
	virtual void getEnabledExtensions();
	virtual void prepare();

	VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);

	void windowResize();
	void renderLoop();
	void drawUI(const VkCommandBuffer commandBuffer);
	void prepareFrame();
	void submitFrame();
	virtual void renderFrame();
	virtual void onUpdateUIOverlay(/*UIOverlay& overlay*/);

#if defined(_WIN32)
	virtual void onHandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif







};