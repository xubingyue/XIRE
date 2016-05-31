#pragma once
 
#include "XIRE_Afx.h"
#include "EventHandler.h"
#include "Drawable.h"

#include <vector>
#include <map>

NS_Begin(XIRE)

class Graphics; 
class Camera;

class XIREAPI Window
	:public Drawable
{
protected:

    Window();

public:

	explicit Window(HINSTANCE hInstance, String title, int w, int h);
	 
	virtual ~Window();

public:

	bool Create();

	void Show();

	void Hide();

	void Maximize();

	void Minimize();

	void Reset();

	void OnUpdate();

	void OnRender();

	void AddDrawable(Drawable *drawable);
 
	RenderEventHandler WindowRender;

private:

	static LRESULT CALLBACK OnWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); 

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:

	HWND handleWindow; 

	HINSTANCE handleApp;

	WNDCLASSEX wcex; 

	WINDOWPLACEMENT windowPlacement;
	
//Graphics
protected: 

	Graphics *g;

public:

	Graphics *getRender() { return g; }

	Camera* getCamera() { return camera; }

	HWND GetWindowHandle();

	void ToggleFullscreen();

	int Width;
	int Height; 

	int FullscrWidth;
	int FullscrHeight;

	bool Fullscreen;

	String Title;

	Camera *camera;

	std::vector<Drawable*> drawObjectList;
};

NS_End(XIRE)