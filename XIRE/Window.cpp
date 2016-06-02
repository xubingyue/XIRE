#include "Window.h"
#include "Graphics.h"
#include "RenderBase.h"
#include "Drawable.h"
#include "Camera.h"

NS_Using(XIRE) 

Window::Window(HINSTANCE hInstance,String title, int w, int h)
	: fullscreen(false), Width(1024), Height(768)
{
	Name = title;

	handleApp = hInstance;

	Title = title;
	Width = w;
	Height = h;

	FullscrWidth = ::GetSystemMetrics(SM_CXSCREEN);
	FullscrHeight = ::GetSystemMetrics(SM_CYSCREEN);

	Create(); 
}

Window::~Window()
{
	SafeDelete(g);
}

HWND Window::GetWindowHandle()
{
	return handleWindow;
}

void Window::OnUpdate()
{
	
}

void Window::OnRender()
{   
	g->BeginFrame();
	 
	for (int i = 0; i < drawObjectList.size(); ++i)
	{
		g->Draw(drawObjectList[i]);
	}
	 
	if (!WindowRender.IsNull())
	{
		WindowRender(this, NULL);
	}
	
	g->EndFrame(); 

	g->Swap();
}

bool Window::Create()
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)OnWindowMessage;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = handleApp;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(handleApp, MAKEINTRESOURCE(IDC_HAND));
	wcex.hIcon = LoadIcon(handleApp, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIconSm = LoadIcon(handleApp, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.lpszClassName = Title.c_str();
	wcex.lpszMenuName = NULL;
	
	if (FAILED(::RegisterClassEx(&wcex)))
	{
		//Log here
		return false;
	}

	handleWindow = ::CreateWindowEx(
		NULL,
		Title.c_str(),
		Title.c_str(),
		fullscreen ? WS_EX_TOPMOST : WS_OVERLAPPEDWINDOW&(~WS_MAXIMIZEBOX),
		(FullscrWidth - Width) / 2,
		(FullscrHeight - Height) / 2,
		Width,
		Height,
		NULL,
		NULL,
		handleApp,
		this);

	RECT rect = { 0, 0, Width, Height };
	AdjustWindowRect(&rect, GetWindowLong(handleWindow, GWL_STYLE), FALSE);
	SetWindowPos(handleWindow, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
		SWP_NOZORDER | SWP_NOMOVE);

	if (fullscreen == true)
	{
		SetWindowLongPtr(handleWindow, GWL_STYLE, WS_EX_TOPMOST);
	}
	else
	{
		::ZeroMemory(&windowPlacement, sizeof(WINDOWPLACEMENT));
		windowPlacement.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(handleWindow, &windowPlacement);
	} 

	if (FAILED(::UpdateWindow(handleWindow)))
	{
		return false;
	}

	g = new Graphics((Window*)this); 

	camera = new Camera(this,core::Vectorf3(0.f,0.f,0.f),core::Quaternion::CreateIdentity());

	return true;
}

void Window::Show()
{
	if (FAILED(::ShowWindow(handleWindow, SW_SHOWNORMAL)))
	{
		MessageBox(NULL,TEXT("H"),TEXT("H"),0); 
		return;
	}
}

void Window::Hide()
{

}

void Window::Maximize()
{
}

void Window::Minimize()
{
}

//Hacks for not breaking capsulation
LRESULT CALLBACK Window::OnWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT*)lParam)->lpCreateParams);
		return 0;
	}
	return ((Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA))->WndProc(hwnd, msg, wParam, lParam); 
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{ 
		/*camera->Rotate(0.0f, 0.0f, -0.19f); */
	}break;
	case WM_KEYUP:
	{
		if (wParam == VK_ESCAPE)
		{
			//::PostQuitMessage(0);
		}
		else if (wParam == VK_F11)
		{
			ToggleFullscreen();
		}
		else if (wParam >= 'A' && wParam <= 'Z')
		{
			printf("KEYUP:%d\n", wParam);
		}
	}
	break;  
	case WM_KEYDOWN:
	{
		if (wParam >= 'A' && wParam <= 'Z')
		{

		}
	} break;
	case WM_CLOSE:
	{ 
		this->Close();
	} break;
	case WM_DESTROY:
	{ 
	} break;
	case WM_QUIT:
	{
		 
	}break;
	default:
		break;
	}

	//U8 keys[256];
	//if (GetKeyboardState(keys))
	//{
	//	 
	//}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Window::Reset()
{
	if (g != nullptr)
	{ 
		g->GetDriver()->Reset(); 
	}
}

void Window::Close()
{
	DestroyWindow(handleWindow);

	if (!WindowClosed.IsNull())
	{
		WindowClosed(this, NULL);
	}
}

void Window::ToggleFullscreen()
{
	fullscreen = !fullscreen;

	if (!fullscreen)
	{
		SetWindowLongPtr(handleWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	}
	else
	{
		ZeroMemory(&windowPlacement, sizeof(WINDOWPLACEMENT));
		windowPlacement.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(handleWindow, &windowPlacement);

		SetWindowLongPtr(handleWindow, GWL_STYLE, WS_EX_TOPMOST);
	}
 
	Reset(); 

	if (!fullscreen)
	{
		SetWindowPlacement(handleWindow, &windowPlacement);
	}
}

void Window::AddDrawable(Drawable *drawable)
{
	drawObjectList.push_back(drawable);
}