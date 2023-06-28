#include "pch.h"



void Application::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Destroy();
}

void Application::DrawFrame()
{
	m_pFence->Wait(*m_pDevice->GetDevice(), currentFrame);

	uint32_t imageIndex;
	bool gotIndex = m_pSwapchain->GetNextImageIndex(*m_pDevice->GetDevice(), m_pRenderSemaphore->GetSemaphore(currentFrame), imageIndex);
	
	if (!gotIndex)
	{
		RecreateSwapChain();
		return;
	}
	
	m_pFence->Reset(*m_pDevice->GetDevice(), currentFrame);

	m_pCommandBuffer->Record(m_pFramebuffer->GetFramebuffer(imageIndex), m_pRenderPass->GetRenderPass(),
		m_pSwapchain->GetExtent(), *m_pVertexBuffer,  m_pPipeline->GetPipeline(), currentFrame);
	
	Presenter::Submit(m_pCommandBuffer->GetCommandBuffer(currentFrame),
		m_pRenderSemaphore->GetSemaphore(currentFrame), m_pPresentSemaphore->GetSemaphore(currentFrame), m_pFence->GetFence(currentFrame), m_pDevice->GetGraphicsQueue());

	bool canPresent = Presenter::Present(m_pDevice->GetPresentQueue(), m_pSwapchain->GetSwapChain(), imageIndex, m_pPresentSemaphore->GetSemaphore(currentFrame));

	if (!canPresent)
	{
		m_bFrameBufferResized = true;
		RecreateSwapChain();
	}

	// Go to the next frame to start recording commands.
	currentFrame = (currentFrame + 1) % FRAMES;
}

void Application::InitWindow()
{
	glfwInit();
	// GLFW was initially designed for OpenGL, so no need to tell it not to create OpenGL context.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	// Disable resizable for now. It required extra work.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	
	m_pWindow = glfwCreateWindow(m_width, m_height, "Plasma Engine", nullptr, nullptr);
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferResizeCallback);
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
		DrawFrame();
	}
	vkDeviceWaitIdle(*m_pDevice->GetDevice());
}

void Application::Destroy()
{
	m_pRenderSemaphore->Destroy(*m_pDevice->GetDevice());
	m_pPresentSemaphore->Destroy(*m_pDevice->GetDevice());
	m_pFence->Destroy(*m_pDevice->GetDevice());
	m_pCommandPool->Destroy(*m_pDevice->GetDevice());
	m_pVertexBuffer->Destroy(*m_pDevice->GetDevice());
	m_pFramebuffer->Destroy(*m_pDevice->GetDevice());
	m_pPipeline->Destroy(*m_pDevice->GetDevice());
	m_pRenderPass->Destroy(*m_pDevice->GetDevice());
	m_pVertexShader->Destroy(*m_pDevice->GetDevice());
	m_pFragmentShader->Destroy(*m_pDevice->GetDevice());
	m_pSwapchain->Destroy(*m_pDevice->GetDevice());
	m_pDevice->Destroy();
	/*m_Debugger->DestroyDebugUtilsMessengerEXT(m_pInstance->GetInstance(), m_Debugger->debugMessenger, nullptr);*/
	m_pSurface->Destroy(m_pInstance->GetInstance());
	m_pInstance->Destroy();
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void Application::RecreateSwapChain()
{
	int width = 0, height = 0;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		glfwWaitEvents();
	}
	vkDeviceWaitIdle(*m_pDevice->GetDevice());

	CleanupSwapChain();

	m_pSwapchain = new Swapchain(*m_pWindow, *m_pPhysicalDevice, *m_pDevice->GetDevice(), *m_pSurface->GetSurface());
	m_pFramebuffer = new Framebuffer(*m_pDevice->GetDevice(), m_pSwapchain->GetExtent(), m_pSwapchain->GetImageViews(), m_pRenderPass->GetRenderPass());
}

void Application::CleanupSwapChain()
{
	m_pFramebuffer->Destroy(*m_pDevice->GetDevice());
	m_pSwapchain->Destroy(*m_pDevice->GetDevice());

}

 void Application::FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
	app->m_bFrameBufferResized = true;
}

void Application::InitVulkan()
{
	if (debug)
	{
		m_Debugger = new Debugger(debug);
	}
		
	m_pInstance = new Instance(*m_Debugger);

	// TODO: include more platforms.
#ifdef _WIN32
	m_pSurface = new WindowSurface(*m_pWindow, m_pInstance->GetInstance());
#endif
	/*m_Debugger->SetupDebugMessenger(m_pInstance->GetInstance());*/
	
	m_pPhysicalDevice = new PhysicalDevice(m_pInstance->GetInstance(), *m_pSurface->GetSurface());
	m_pDevice = new Device(*m_pPhysicalDevice, debug);
	m_pSwapchain = new Swapchain(*m_pWindow, *m_pPhysicalDevice, *m_pDevice->GetDevice()/**m_pPhysicalDevice->GetSwapChainSupportDetails()*/, *m_pSurface->GetSurface()/*, *m_pPhysicalDevice->GetFamilyIndices()*/);
	m_pInstance->PrintSupportedExtensions();

	m_pVertexShader = new Shader("../source/shaders/basicVert.spv", *m_pDevice->GetDevice());
	m_pFragmentShader = new Shader("../source/shaders/basicFrag.spv", *m_pDevice->GetDevice());

	m_pRenderPass = new RenderPass(*m_pDevice->GetDevice(), m_pSwapchain->GetFormat());
	m_pPipeline = new Pipeline(*m_pDevice->GetDevice(), m_pSwapchain->GetExtent(), 
		m_pVertexShader->GetPiplineShaderStageCI(), m_pFragmentShader->GetPiplineShaderStageCI(), m_pRenderPass->GetRenderPass());
	m_pFramebuffer = new Framebuffer(*m_pDevice->GetDevice(), m_pSwapchain->GetExtent(), m_pSwapchain->GetImageViews(), m_pRenderPass->GetRenderPass());
	m_pCommandPool = new CommandPool(*m_pDevice->GetDevice(), m_pPhysicalDevice->GetFamilyIndices().graphicsFamily.value());
	m_pVertexBuffer = new VertexBuffer(m_pPhysicalDevice->GetDevice(), *m_pDevice->GetDevice(), m_pDevice->GetGraphicsQueue(), m_pCommandPool->GetCommandPool());
	m_pCommandBuffer = new CommandBuffer(*m_pDevice->GetDevice(), m_pCommandPool->GetCommandPool(), FRAMES);
	m_pRenderSemaphore = new Semaphore(*m_pDevice->GetDevice(), FRAMES);
	m_pPresentSemaphore = new Semaphore(*m_pDevice->GetDevice(), FRAMES);
	m_pFence = new Fence(*m_pDevice->GetDevice(), FRAMES);
}