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

	void GameApp_OnApplicationInitialized(void *sender, AppStartupEventArgs e);

	void GameApp_OnApplicationRender(void *sender, ApplicationRenderEventArgs e);

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

void GameAppDelegate::GameApp_OnApplicationInitialized(void *sender, AppStartupEventArgs e)
{ 
	//test for resource loading
	mesh = new XIRE::SwMesh(S("C:/dev/SoftRenderer/bin64/media/ModelViewer/teapot.obj"));
	XIRE::Application *app = (XIRE::Application*)sender;
	app->GetMainWindow()->AddDrawable(mesh);
}

void GameAppDelegate::GameApp_OnApplicationRender(void *sender, ApplicationRenderEventArgs e)
{ 
//	//draw all mesh into 3d space
//
	//XIRE::Graphics *g = e.Data->window->getRender();
	//XIRE::Graphics *g = ((XIRE::Window*)sender)->GetRender();
	//g->Draw(mesh);
//
//	//mesh->Draw(g);
//	//mesh->Draw(e.Data->window->GetRender());
}
 
int main(int argc, char** argv)
{
	XIRE::core::Matrixf44 matrix;
	matrix = XIRE::Transform::getMatrixTranslationConst(1.f, 2.f, 3.f); 
	matrix.Print();
	matrix.MakeInverse();
	matrix.Print();

	printf("%d\n", 8 * sizeof(XIRE::SwVertexP3N3T2));
	printf("%d\n", 8 * sizeof(XIRE::core::Vectorf4));
	printf("%d\n", 8 * sizeof(XIRE::core::Vectorf3));
	printf("%d\n", 8 * sizeof(XIRE::core::Vectorf2));

	//Demo of inheritance usage 
	GameAppDelegate *app = GameAppDelegate::get(); 
	return 0;
} 
