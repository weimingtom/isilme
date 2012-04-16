#ifndef TUTORIALS_PLAYSTATE_H
#define TUTORIALS_PLAYSTATE_H

#include "Definitions.h"

class PlayState : public State, public gcn::MouseListener
{
public:
	PlayState();
	virtual ~PlayState();

	virtual void mouseClicked(gcn::MouseEvent& mouseEvent) override;
	virtual void mouseMoved(gcn::MouseEvent& mouseEvent) override;
	virtual void mousePressed(gcn::MouseEvent& mouseEvent) override;
	virtual void mouseDragged(gcn::MouseEvent& mouseEvent) override;
	virtual void mouseReleased(gcn::MouseEvent& mouseEvent) override;
private:
	gcn::ButtonPtr mQuitButton;
};
#endif