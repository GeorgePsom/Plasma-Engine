#pragma once
#ifdef NDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif
class Application
{
public:
	Application(uint32_t width = 800, uint32_t height = 600) 
		: m_width(width), m_height(height), m_debugMode(debug) {}
	void Run();
	

private:
	void InitWindow();
	void InitVulkan();
	void MainLoop();
	void DrawFrame();
	void Destroy();
	void RecreateSwapChain();
	void CleanupSwapChain();

	static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);

	uint32_t  m_width, m_height;
	GLFWwindow* m_pWindow;
	Instance* m_pInstance;
	Surface* m_pSurface = nullptr;
	Debugger* m_Debugger = nullptr;
	PhysicalDevice* m_pPhysicalDevice;
	Device* m_pDevice;
	Swapchain* m_pSwapchain;
	Shader* m_pVertexShader;
	Shader* m_pFragmentShader;
	Pipeline* m_pPipeline;
	RenderPass* m_pRenderPass;
	Framebuffer* m_pFramebuffer;
	CommandPool* m_pCommandPool;

	const int FRAMES = 2;
	uint32_t currentFrame = 0;
	CommandBuffer* m_pCommandBuffer;
	Semaphore* m_pPresentSemaphore, *m_pRenderSemaphore;
	Fence* m_pFence;
	bool m_debugMode;

	bool m_bFrameBufferResized;



};
