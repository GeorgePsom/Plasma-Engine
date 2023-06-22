#include "pch.h"



void Application::Run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Destroy();
}

void Application::InitWindow()
{
	glfwInit();
	// GLFW was initially designed for OpenGL, so no need to tell it not to create OpenGL context.
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	// Disable resizable for now. It required extra work.
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	m_pWindow = glfwCreateWindow(m_width, m_height, "Plasma Engine", nullptr, nullptr);
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		glfwPollEvents();
	}
}

void Application::Destroy()
{
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
}