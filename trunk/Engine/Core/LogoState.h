#ifndef LOGO_STATE
#define LOGO_STATE

#include "State.h"

class ISILME_API LogoState : public State
{
public:
	LogoState(hgeSprite* sprite)
	{
		mOfielLogo = sprite;
		mTime = 2.0f;
	}
	virtual void OnUpdate(float elapsedTime){mTime -= elapsedTime; if (mTime < 0) Close();}
	virtual void OnDraw(){mOfielLogo->Render4V(0,0,800,0,800,600,0,600);}

	virtual ~LogoState()
	{
	}
protected:
	float mTime;
	hgeSprite* mOfielLogo;
};
#endif