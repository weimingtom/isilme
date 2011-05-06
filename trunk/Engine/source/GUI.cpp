#include "GUI.h"

HGE *GUI::hge=0;
HGE *GUIObject::hge=0;


GUI::GUI()
{
	hge=hgeCreate(HGE_VERSION);

	ctrls=0;
	ctrlLock=0;
	ctrlFocus=0;
	ctrlOver=0;
	navmode=HGEGUI_NONAVKEYS;
	bLPressed=bLReleased=false;
	bRPressed=bRReleased=false;
	nWheel=0;
	mx=my=0.0f;
	nEnterLeave=0;
	sprCursor=0;
}

GUI::~GUI()
{
	GUIObject *ctrl=ctrls, *nextctrl;

	while(ctrl)
	{
		nextctrl=ctrl->next;
		delete ctrl;
		ctrl=nextctrl;
	}

	hge->Release();
}

void GUI::AddCtrl(GUIObject *ctrl)
{
	GUIObject *last=ctrls;

	ctrl->SetGUI(this);

	if(!ctrls)
	{
		ctrls=ctrl;
		ctrl->prev=0;
		ctrl->next=0;
	}
	else
	{
		while(last->next) last=last->next;
		last->next=ctrl;
		ctrl->prev=last;
		ctrl->next=0;
	}
}

void GUI::DelCtrl(int id)
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		if(ctrl->id == id)
		{
			if(ctrl->prev) ctrl->prev->next = ctrl->next;
			else ctrls = ctrl->next;
			if(ctrl->next) ctrl->next->prev = ctrl->prev;
			delete ctrl;
			return;
		}
		ctrl=ctrl->next;
	}
}

GUIObject* GUI::GetCtrl(int id) const
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		if(ctrl->id == id) return ctrl;
		ctrl=ctrl->next;
	}

	return NULL;
}

void GUI::MoveCtrl(int id, float x, float y)
{
	GUIObject *ctrl=GetCtrl(id);
	ctrl->rect.x2=x + (ctrl->rect.x2 - ctrl->rect.x1);
	ctrl->rect.y2=y + (ctrl->rect.y2 - ctrl->rect.y1);
	ctrl->rect.x1=x;
	ctrl->rect.y1=y;
}

void GUI::ShowCtrl(int id, bool bVisible)
{
	GetCtrl(id)->bVisible=bVisible;
}

void GUI::EnableCtrl(int id, bool bEnabled)
{
	GetCtrl(id)->bEnabled=bEnabled;
}

void GUI::SetNavMode(int mode)
{
	navmode=mode;
}

void GUI::SetCursor(hgeSprite *spr)
{
	sprCursor=spr;
}


void GUI::SetColor(DWORD color)
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		ctrl->SetColor(color);
		ctrl=ctrl->next;
	}
}


void GUI::Reset()
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		ctrl->Reset();
		ctrl=ctrl->next;
	}

	ctrlLock=0;
	ctrlOver=0;
	ctrlFocus=0;
}


void GUI::Move(float dx, float dy)
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		ctrl->rect.x1 += dx;
		ctrl->rect.y1 += dy;
		ctrl->rect.x2 += dx;
		ctrl->rect.y2 += dy;

		ctrl=ctrl->next;
	}
}


void GUI::SetFocus(int id)
{
	GUIObject *ctrlNewFocus=GetCtrl(id);

	if(ctrlNewFocus==ctrlFocus) return;
	if(!ctrlNewFocus)
	{
		if(ctrlFocus) ctrlFocus->Focus(false);
		ctrlFocus=0;
	}
	else if(!ctrlNewFocus->bStatic && ctrlNewFocus->bVisible && ctrlNewFocus->bEnabled)
	{
		if(ctrlFocus) ctrlFocus->Focus(false);
		if(ctrlNewFocus) ctrlNewFocus->Focus(true);
		ctrlFocus=ctrlNewFocus;
	}
}

int GUI::GetFocus() const
{
	if(ctrlFocus) return ctrlFocus->id;
	else return 0;
}

void GUI::Enter()
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		ctrl->Enter();
		ctrl=ctrl->next;
	}

	nEnterLeave=2;
}

void GUI::Leave()
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		ctrl->Leave();
		ctrl=ctrl->next;
	}

	ctrlFocus=0;
	ctrlOver=0;
	ctrlLock=0;
	nEnterLeave=1;
}

void GUI::Render()
{
	GUIObject *ctrl=ctrls;

	while(ctrl)
	{
		if(ctrl->bVisible) ctrl->Render();
		ctrl=ctrl->next;
	}

	if(hge->Input_IsMouseOver() && sprCursor) sprCursor->Render(mx,my);
}

int GUI::Update(float dt)
{
	bool bDone;
	int key;
	GUIObject *ctrl;

// Update the mouse variables

	hge->Input_GetMousePos(&mx, &my);
	bLPressed  = hge->Input_KeyDown(HGEK_LBUTTON);
	bLReleased = hge->Input_KeyUp(HGEK_LBUTTON);
	bRPressed  = hge->Input_KeyDown(HGEK_RBUTTON);
	bRReleased = hge->Input_KeyUp(HGEK_RBUTTON);
	nWheel=hge->Input_GetMouseWheel();

// Update all controls

	ctrl=ctrls;
	while(ctrl)
	{
		ctrl->Update(dt);
		ctrl=ctrl->next;
	}

// Handle Enter/Leave

	if(nEnterLeave)
	{
		ctrl=ctrls; bDone=true;
		while(ctrl)
		{
			if(!ctrl->IsDone()) { bDone=false; break; }
			ctrl=ctrl->next;
		}
		if(!bDone) return 0;
		else
		{
			if(nEnterLeave==1) return -1;
			else nEnterLeave=0;
		}
	}

	// Handle hotkeys
	key=hge->Input_GetKey();
	//if (mHotKeyHandlers.find(key) != mHotKeyHandlers.end())
	//	mHotKeyHandlers[key]->HotKeyActivate();
// Handle keys	


	if(((navmode & HGEGUI_LEFTRIGHT) && key==HGEK_LEFT) ||
		((navmode & HGEGUI_UPDOWN) && key==HGEK_UP))
	{
		ctrl=ctrlFocus;
		if(!ctrl)
		{
			ctrl=ctrls;
			if(!ctrl) return 0;
		}
		do {
			ctrl=ctrl->prev;
			if(!ctrl && ((navmode & HGEGUI_CYCLED) || !ctrlFocus))
			{
				ctrl=ctrls;
				while(ctrl->next) ctrl=ctrl->next;
			}
			if(!ctrl || ctrl==ctrlFocus) break;
		} while(ctrl->bStatic==true || ctrl->bVisible==false || ctrl->bEnabled==false);

		if(ctrl && ctrl!=ctrlFocus)
		{
			if(ctrlFocus) ctrlFocus->Focus(false);
			if(ctrl) ctrl->Focus(true);
			ctrlFocus=ctrl;
		}
	}
	else if(((navmode & HGEGUI_LEFTRIGHT) && key==HGEK_RIGHT) ||
		((navmode & HGEGUI_UPDOWN) && key==HGEK_DOWN))
	{
		ctrl=ctrlFocus;
		if(!ctrl)
		{
			ctrl=ctrls;
			if(!ctrl) return 0;
			while(ctrl->next) ctrl=ctrl->next;
		}
		do {
			ctrl=ctrl->next;
			if(!ctrl && ((navmode & HGEGUI_CYCLED) || !ctrlFocus)) ctrl=ctrls;
			if(!ctrl || ctrl==ctrlFocus) break;
		} while(ctrl->bStatic==true || ctrl->bVisible==false || ctrl->bEnabled==false);

		if(ctrl && ctrl!=ctrlFocus)
		{
			if(ctrlFocus) ctrlFocus->Focus(false);
			if(ctrl) ctrl->Focus(true);
			ctrlFocus=ctrl;
		}
	}
	else if(ctrlFocus && key && key!=HGEK_LBUTTON && key!=HGEK_RBUTTON)
	{
		if(ctrlFocus->KeyClick(key, hge->Input_GetChar())) return ctrlFocus->id;
	}

// Handle mouse

	bool bLDown = hge->Input_GetKeyState(HGEK_LBUTTON);
	bool bRDown = hge->Input_GetKeyState(HGEK_RBUTTON);

	if(ctrlLock)
	{
		ctrl=ctrlLock;
		if(!bLDown && !bRDown) ctrlLock=0;
		if(ProcessCtrl(ctrl)) return ctrl->id;
	}
	else
	{
		// Find last (topmost) control

		ctrl=ctrls;
		if(ctrl)
			while(ctrl->next) ctrl=ctrl->next;

		while(ctrl)
		{
			if(ctrl->rect.TestPoint(mx,my) && ctrl->bEnabled)
			{
				if(ctrlOver != ctrl)
				{
					if(ctrlOver) ctrlOver->MouseOver(false);
					ctrl->MouseOver(true);
					ctrlOver=ctrl;
				}

				if(ProcessCtrl(ctrl)) return ctrl->id;
				else return 0;
			}
			ctrl=ctrl->prev;
		}

		if(ctrlOver) {ctrlOver->MouseOver(false); ctrlOver=0;}

	}

	return 0;
}

bool GUI::ProcessCtrl(GUIObject *ctrl)
{
	bool bResult=false;

	if(bLPressed)	{ ctrlLock=ctrl;SetFocus(ctrl->id);bResult=bResult || ctrl->MouseLButton(true); }
	if(bRPressed)	{ ctrlLock=ctrl;SetFocus(ctrl->id);bResult=bResult || ctrl->MouseRButton(true); }
	if(bLReleased)	{ bResult=bResult || ctrl->MouseLButton(false); }
	if(bRReleased)	{ bResult=bResult || ctrl->MouseRButton(false); }
	if(nWheel)		{ bResult=bResult || ctrl->MouseWheel(nWheel); }
	bResult=bResult || ctrl->MouseMove(mx-ctrl->rect.x1,my-ctrl->rect.y1);

	return bResult;
}
