#include "IsilmePCH.h"
#include "TriggerGraphics.h"

namespace graphics
{
	TriggerGraphics::~TriggerGraphics()
	{
		int a = 4;
	}

	void TriggerGraphics::Update(float elapsedTime)
	{
		if (GetBehaviour()->GetTimer() > 0.0f)
			SetState("Inactive");
		else
			SetState("Active");

		GetState()->Update(elapsedTime);
	}

	void TriggerGraphics::Render(float x, float y, float angle)
	{
		GetState()->Render(x, y, angle);
	}
	

	GraphicsPtr	TriggerDef::Create()
	{
		return GraphicsPtr(new TriggerGraphics(this));
	}
};