#include "PlayState.h"

PlayState::PlayState() :
	mQuitButton(new gcn::Button())
{
	// Create a top-level container
	gcn::ContainerPtr top(new gcn::Container());
	top->SetFocusable(true);
	top->SetSize(800, 40);
	GetGUI()->SetTop(top);

	// Configure a quit-button
	mQuitButton->SetCaption("Quit");
   // mQuitButton->SetForegroundColor(gcn::Color(255,255,255,255));
	mQuitButton->AdjustSize();

	top->Add(mQuitButton, 103, 103);

	// Listen for mouse events
	top->addMouseListener(this);
}

PlayState::~PlayState()
{

}

void PlayState::mouseClicked( gcn::MouseEvent& mouseEvent )
{
	if (mouseEvent.GetSource() == mQuitButton)
	{
		Close();
	}
}

void PlayState::mouseMoved( gcn::MouseEvent& mouseEvent )
{

}

void PlayState::mousePressed( gcn::MouseEvent& mouseEvent )
{

}

void PlayState::mouseDragged( gcn::MouseEvent& mouseEvent )
{

}

void PlayState::mouseReleased( gcn::MouseEvent& mouseEvent )
{

}

void PlayState::OnUpdate(float elapsedTime)
{
    LOG_D("Update works");
}
