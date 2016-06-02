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

//以下为两种用法

/*//Demo of inheritance

class TestApp
	:public XIRE::Application
{
public: 

};

*/

//Demo of delegate
 
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

protected:

	XIRE::Application app; 

	XIRE::SwMesh *mesh;
};

GameAppDelegate::GameAppDelegate()
{
	app.ApplicationInitialized += MakeCCallback2(&GameAppDelegate::GameApp_OnApplicationInitialized);
	app.ApplicationRender += MakeCCallback2(&GameAppDelegate::GameApp_OnApplicationRender);
  
	//app.GetMainWindow()->WindowRender += MakeCCallback2(&GameAppDelegate::GameApp_OnWindowRender);
 	
	app.Run();
}

GameAppDelegate::~GameAppDelegate()
{
	
} 

void GameAppDelegate::GameApp_OnApplicationInitialized(void *sender, ApplicationEventArgs e)
{ 
	//test for resource loading
	mesh = new XIRE::SwMesh(S("C:/dev/SoftRenderer/bin64/media/ModelViewer/teapot.obj"));
	XIRE::Application *app = (XIRE::Application*)sender;

	app->AddWindow(S("Window2"),1024,768);

	app->GetMainWindow()->AddDrawable(mesh);
	app->GetWindow(S("Window2"))->AddDrawable(mesh);
	
}

void GameAppDelegate::GameApp_OnApplicationRender(void *sender, ApplicationEventArgs e)
{ 
	e.Data->window->getCamera()->Rotate(0.01f, 0.0f, 0.0f); 
}
 
int main(int argc, char** argv)
{  
	//Demo of inheritance usage 
	GameAppDelegate *app = GameAppDelegate::get(); 
	return 0;
} 
