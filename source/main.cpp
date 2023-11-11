
#include "pch.h"

#define ENABLE_VALIDATION false

class TriangleExample : public Sample
{
public:

	TriangleExample() : Sample(ENABLE_VALIDATION)
	{
		title = "Plasma Engine - Basic indexed triangle";
		settings.overlay = false;
		// TODO initialize camera.
	}

	void render() { //Just to compile for now.}
	}
};



#if defined(_WIN32)
TriangleExample* triangleExample;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (triangleExample != NULL)
		triangleExample->handleMessages(hWnd, uMsg, wParam, lParam);

	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	for (size_t i = 0; i < __argc; i++) { TriangleExample::args.push_back(__argv[i]); };
	triangleExample = new TriangleExample();
	triangleExample->initVulkan();
	//triangleExample->SetupWindow(hInstance, WndProc);
	//triangleExample->Prepare();
	//triangleExample->RenderLoop();
	delete(triangleExample);
	return 0;
}

#else
int maint()
{
	throw std::runtime_error("Currently only Windows platform is supported!");
	return -1;
}
	

#endif
	



