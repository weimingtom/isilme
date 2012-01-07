#ifndef ISILME_GRAPHICS_LINE_H
#define ISILME_GRAPHICS_LINE_H

#include "Definitions.h"
#include "Graphics.h"

namespace graphics
{
	class ISILME_API LineDef : public GraphicsDefinition
	{
	public:
		DWORD	Color;
		Vector2 Start;
		Vector2 End;

		virtual void Parse(TiXmlElement* defElement);
		virtual GraphicsPtr Create();
	};

	class ISILME_API Line : public Graphics
	{
	public:
		Line(LineDef* def);
		virtual ~Line();

		virtual void Render(float x, float y, float angle);
	private:
		Vector2 mStart;
		Vector2 mEnd;
		DWORD	mColor;
	};
}
#endif