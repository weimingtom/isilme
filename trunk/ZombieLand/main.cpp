#include "ZombieLand.h"
#include <guichan.hpp>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//Lua* state = new Lua();
	//double value = 0.0;
	//state->RegisterFunction<double,(Test::fa)>("fa");
	//state->RegisterFunction<double,(Test::fb)>("fb");
	//state->CallFunction("lua_test_func", value);
	//SoundManager::GetSingleton()->SetBackGroundMusic("../Data/Sounds/Background.wav");
	ZombieLand* game = new ZombieLand();
	game->Init();
	game->Start();
	delete game;

	return 0;
}