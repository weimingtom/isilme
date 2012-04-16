#include "Definitions.h"
#include "MyGame.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	MyGame game;
	game.Init();
	game.Start();
	return 0;
}