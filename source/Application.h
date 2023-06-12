#pragma once
#ifdef NDEBUG
	const bool debug = true;
#else
	const bool debug = false;
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
	void Destroy();

	uint32_t  m_width, m_height;
	GLFWwindow* m_pWindow;
	Instance* m_pInstance;
	Debugger* m_Debugger = nullptr;
	bool m_debugMode;



};