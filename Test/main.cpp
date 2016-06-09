//XIRE(XIRE is a Render Engine) 
 
//Include XIRE framework header

#include "..\XIRE\XIRE_Cfg.h"
#include "..\XIRE\XIRE.h" 

//proper version of the lib file
#ifdef _DEBUG 
	#if defined(_WIN64)
		#pragma comment(lib,"..\\bin64\\XIRE_d.lib")  
	#elif defined(_WIN32)
		#pragma comment(lib,"..\\bin32\\XIRE_d.lib") 
	#endif
#else
	#if defined(_WIN64)
		#pragma comment(lib,"..\\bin64\\XIRE.lib")  
	#elif defined(_WIN32)
		#pragma comment(lib,"..\\bin32\\XIRE.lib") 
	#endif
#endif

//以下为两种示例用法

/*//Demo of inheritance(Internal virtual functions)

class TestApp
	:public XIRE::Application
{
public: 
	

};

*/

//Demo of delegate(callback functions)
 
class GameAppDelegate
{
private:

	GameAppDelegate(); 

	~GameAppDelegate();

public:

	static GameAppDelegate* get()
	{
		static GameAppDelegate _inst;
		return &_inst;
	}

protected:

	void GameApp_OnApplicationInitialized(void *sender, ApplicationEventArgs e);

	void GameApp_OnApplicationRender(void *sender, ApplicationEventArgs e);

	void GameApp_OnMeshKeyDown(void *sender, KeyEventArgs e);

	void Mesh_OnMouseMove(void *sender, MouseEventArgs e);

protected:

	XIRE::Application *app;  
};

GameAppDelegate::GameAppDelegate()
{
	app = new XIRE::Application();

	app->ApplicationInitialized += CCallback2(&GameAppDelegate::GameApp_OnApplicationInitialized);
	app->ApplicationRender += CCallback2(&GameAppDelegate::GameApp_OnApplicationRender);
	
	//app.GetMainWindow()->WindowRender += CCallback2(&GameAppDelegate::GameApp_OnWindowRender);
 	
	app->Run();
}

GameAppDelegate::~GameAppDelegate()
{
	SafeDelete(app);
} 

void GameAppDelegate::GameApp_OnApplicationInitialized(void *sender, ApplicationEventArgs e)
{
	//test for resource loading
	XIRE::SwMesh *mesh = new XIRE::SwMesh(S("C:/dev/SoftRenderer/bin64/media/ModelViewer/teapot.obj"));
	XIRE::SwMesh *mesh2 = new XIRE::SwMesh(S("C:/dev/SoftRenderer/bin64/media/ModelViewer/head.obj"));
	
	mesh->KeyDown += CCallback2(&GameAppDelegate::GameApp_OnMeshKeyDown);
	mesh->MouseMove += CCallback2(&GameAppDelegate::Mesh_OnMouseMove);

	XIRE::Application *app = (XIRE::Application*)sender;

	//app->AddWindow(S("Window2"),1024,768);

	app->GetMainWindow()->AddChild(mesh);
	//app->GetWindow(S("Window2"))->AddChild(mesh2);
}

void GameAppDelegate::GameApp_OnApplicationRender(void *sender, ApplicationEventArgs e)
{ 
	 
}

void GameAppDelegate::Mesh_OnMouseMove(void *sender, MouseEventArgs e)
{
	XIRE::SwMesh *mesh = (XIRE::SwMesh *)sender;
	if (mesh == nullptr)
		return;

	XIRE::Window *wnd = (XIRE::Window *)(mesh->Parent);
	wnd->getCamera()->Rotate(0.f, 0.f, 0.3f);
} 

void GameAppDelegate::GameApp_OnMeshKeyDown(void *sender, KeyEventArgs e)
{

}
 
int main(int argc, char** argv)
 {  
	//Demo of inheritance usage  
	GameAppDelegate::get(); 
	return 0;
} 
