#ifndef ISILME_GUI_HGELABEL_H
#define ISILME_GUI_HGELABEL_H

#include "Isilme.h"
#include <GUIChan/gui.hpp>
#include <hgefont.h>

namespace gcn
{
class HGELabel: public Widget
{
public:
    HGELabel(std::string fontfile)
    {
		mFont = new hgeFont(fontfile.c_str());
	}

	~HGELabel()
	{
	}

	void setCaption(std::string caption)
	{
		mCaption = caption;
	}

	void setTextColor(gcn::Color color)
	{
		DWORD c = 256 * 256 * 256 * color.r + 256 * 256 * color.g + 256 * color.b + color.a;
		
		mFont->SetColor(c);
	}

	void setTextScale(float scale)
	{
		mFont->SetScale(scale);
	}

	std::string getCaption()
	{
		return mCaption;
	}

    virtual void draw(Graphics* g)
    {
		mFont->Render(getX(), getY(), HGETEXT_LEFT, mCaption.c_str());
    }
    virtual void logic()
	{
	}
private:
   hgeFont* mFont;
   std::string mCaption;
};
};

#endif