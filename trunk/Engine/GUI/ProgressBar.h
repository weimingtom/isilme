#ifndef ISILME_GUI_PROGRESSBAR_H
#define ISILME_GUI_PROGRESSBAR_H

#include "Isilme.h"
#include <GUIChan/gui.hpp>

namespace gcn
{
class ProgressBar: public Widget
{
public:
    ProgressBar()
    :mProgress(0)
    {}

    void setProgress(float progress)
    {
         mProgress = progress < 0.0f ? 0.0f : progress;
         mProgress = progress > 100.f ? 100.0f : progress;
    }    
    virtual void draw(Graphics* g)
    {
         g->setColor(getSelectionColor());
         g->fillRectangle(gcn::Rectangle(0, 0, getWidth() * mProgress, getHeight()));
         g->setColor(getForegroundColor());
         g->drawRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));

    }
    virtual void logic()
	{
	}
private:
   float mProgress;
};
};

#endif