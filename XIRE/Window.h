#pragma once
 
#include "XIRE_Afx.h"
#include "EventHandler.h"
#include "Drawable.h"

#include <vector>
#include <map>

NS_Begin(XIRE)

class Graphics; 
class D3D9Camera;

class XIREAPI Window : public Drawable 
{ 
public:

	explicit Window(HINSTANCE hInstance, String title, int w=1024, int h=768);
	 
	virtual ~Window(); 

public:

	bool Create();

	void Show();

	void Hide();

	void Close();

	void Maximize();

	void Minimize();

	void Reset();

	void OnUpdate();

	void OnRender();
 
	WindowEventHandler WindowRender;

	WindowEventHandler WindowClosed;

private:

	static LRESULT CALLBACK OnWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); 

	LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND handleWindow; 

	HINSTANCE handleApp;

	WNDCLASSEX wcex; 

	WINDOWPLACEMENT windowPlacement;
 
protected: 

	Graphics *g;

	bool fullscreen;

	D3D9Camera *camera;

public:

	Graphics *getRender() { return g; }

	D3D9Camera* getCamera() { return camera; }

	HWND GetWindowHandle();

	bool IsFullscreen() { return fullscreen; }

	void ToggleFullscreen();

	int Width;
	int Height; 

	int FullscrWidth;
	int FullscrHeight;

	String Title;
};

NS_End(XIRE)