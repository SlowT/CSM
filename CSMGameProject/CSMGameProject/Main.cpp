
#include "NNApplication.h"
#include "GameScene.h"

/*
void main()
{
	WinMain(0, 0, 0, 3);
}*/

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );
#endif

	NNApplication* Application = NNApplication::GetInstance();

	Application->Init( L"D2D Test", 800, 600, D2D );

	NNSceneDirector::GetInstance()->ChangeScene( CGameScene::Create() );

	Application->Run();
	Application->Release();

	return 0;
}