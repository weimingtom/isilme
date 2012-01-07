#include "IsilmePCH.h"
#include "Line.h"
#include "Renderer.h"
#include "Game.h"
#include "StateManager.h"

namespace graphics
{
	void LineDef::Parse( TiXmlElement* defElement )
	{

	}

	GraphicsPtr LineDef::Create()
	{
		return GraphicsPtr(new Line(this));
	}


	Line::Line( LineDef* def ) : 
		Graphics(def)
	{
		mColor = def->Color;
		mStart = def->Start;
		mEnd = def->End;
	}

	Line::~Line()
	{

	}

	void Line::Render( float x, float y, float angle )
	{
		float x1 = mStart.x * cos(angle) + x;
		float y1 = mStart.y * sin(angle) + y;
		float x2 = mEnd.x * cos(angle) + x;
		float y2 = mEnd.y * sin(angle) + y;
		Engine::GetSingleton()->mHGE->Gfx_RenderLine(x1, y1, x, y2, mColor);
	}

}