#include "MyGame.h"
#include "PlayState.h"

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::Init()
{
	// Register font
	gcn::FontPtr font = gcn::FontPtr(new gcn::HGEImageFont("../Data/Fonts/font2.fnt"));
	gcn::Widget::SetGlobalFont(font);

	// Create state
	StatePtr state(new PlayState());
	GetStateManager()->Push(state);
}
