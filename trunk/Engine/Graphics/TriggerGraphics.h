#ifndef ISILME_GRAPHICS_TIRGGER_H
#define ISILME_GRAPHICS_TIRGGER_H

#include "Graphics.h"
#include "Engine/Graphics/StateGraphics.h"
#include "Trigger.h"

namespace graphics
{
	class TriggerDef : public StateGraphicsDef<Trigger>
	{
	public:
		virtual GraphicsPtr Create();
	};

	/// @class TriggerGraphics
	class ISILME_API TriggerGraphics : public StateGraphics<Trigger>
	{
	public:
		TriggerGraphics(TriggerDef* def) : 
		  StateGraphics<Trigger>(def)
		{
		}
		virtual ~TriggerGraphics();

		virtual void Update(float elapsedTime);

		virtual void Render(float x, float y, float angle);
	};
};
#endif