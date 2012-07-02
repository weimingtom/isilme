/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004 - 2008 Olof Naessén and Per Larsson
 *
 *
 * Per Larsson a.k.a finalman
 * Olof Naessén a.k.a jansem/yakslem
 *
 * Visit: http://guichan.sourceforge.net
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/basiccontainer.hpp"

#include <algorithm>

#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/graphics.hpp"
#include "guichan/mouseinput.hpp"

namespace gcn
{
    BasicContainer::~BasicContainer()
    {
        Clear();
    }

	void BasicContainer::MoveToTop( WidgetPtr widget )
	{
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (*iter == widget)
            {
                mWidgets.erase(iter);
                mWidgets.push_back(widget);
                return;
            }
        }

        throw GCN_EXCEPTION("There is no such widget in this container.");
    }

	void BasicContainer::MoveToBottom( WidgetPtr widget )
	{
        WidgetListIterator iter;
        iter = find(mWidgets.begin(), mWidgets.end(), widget);

        if (iter == mWidgets.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this container.");
        }
        mWidgets.erase(iter);
        mWidgets.push_front(widget);
    }

    void BasicContainer::death(const Event& event)
    {
        WidgetListIterator iter;
        iter = find(mWidgets.begin(), mWidgets.end(), event.GetSource());

        if (iter == mWidgets.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this container.");
        }

        mWidgets.erase(iter);
    }

    Rectangle BasicContainer::getChildrenArea()
    {
        return Rectangle(0, 0, GetWidth(), GetHeight());
    }

    void BasicContainer::FocusNext()
    {
        WidgetListIterator it;

        for (it = mWidgets.begin(); it != mWidgets.end(); it++)
        {
            if ((*it)->IsFocused())
            {
                break;
            }
        }

        WidgetListIterator end = it;

        if (it == mWidgets.end())
        {
            it = mWidgets.begin();
        }

        it++;

        for ( ; it != end; it++)
        {
            if (it == mWidgets.end())
            {
                it = mWidgets.begin();
            }

            if ((*it)->IsFocusable())
            {
                (*it)->requestFocus();
                return;
            }
        }
    }

    void BasicContainer::focusPrevious()
    {
        WidgetListReverseIterator it;

        for (it = mWidgets.rbegin(); it != mWidgets.rend(); it++)
        {
            if ((*it)->IsFocused())
            {
                break;
            }
        }

        WidgetListReverseIterator end = it;

        it++;

        if (it == mWidgets.rend())
        {
            it = mWidgets.rbegin();
        }

        for ( ; it != end; it++)
        {
            if (it == mWidgets.rend())
            {
                it = mWidgets.rbegin();
            }

            if ((*it)->IsFocusable())
            {
                (*it)->requestFocus();
                return;
            }
        }
    }

	gcn::WidgetPtr BasicContainer::GetWidgetAt( int x, int y )
	{
        Rectangle r = getChildrenArea();

        if (!r.isPointInRect(x, y))
        {
            return WidgetPtr();
        }

        x -= r.x;
        y -= r.y;

        WidgetListReverseIterator it;
        for (it = mWidgets.rbegin(); it != mWidgets.rend(); it++)
        {
            if ((*it)->IsVisible() && (*it)->GetDimension().isPointInRect(x, y))
            {
                return (*it);
            }
        }

        return WidgetPtr();
    }

    void BasicContainer::Logic()
    {
        logicChildren();
    }

	void BasicContainer::_setFocusHandler( FocusHandlerPtr focusHandler )
	{
        Widget::_setFocusHandler(focusHandler);

        if (mInternalFocusHandler != NULL)
        {
            return;
        }

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->_setFocusHandler(focusHandler);
        }
    }

    void BasicContainer::Add(WidgetPtr widget)
    {
        mWidgets.push_back(widget);

        if (mInternalFocusHandler == NULL)
        {
            widget->_setFocusHandler(_getFocusHandler());
        }
        else
        {
            widget->_setFocusHandler(mInternalFocusHandler);
        }

        widget->_setParent(shared_from_this());
        widget->addDeathListener(this);
    }

    void BasicContainer::Remove(WidgetPtr widget)
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (*iter == widget)
            {
                mWidgets.erase(iter);
                widget->_setFocusHandler(FocusHandlerPtr());
                widget->_setParent(WidgetPtr());
                widget->removeDeathListener(this);
                return;
            }
        }

        throw GCN_EXCEPTION("There is no such widget in this container.");
    }

    void BasicContainer::Clear()
    {
        WidgetListIterator iter;

        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->_setFocusHandler(FocusHandlerPtr());
            (*iter)->_setParent(WidgetPtr());
            (*iter)->removeDeathListener(this);
        }

        mWidgets.clear();
    }

	void BasicContainer::DrawChildren( GraphicsPtr graphics )
	{
        graphics->pushClipArea(getChildrenArea());

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if ((*iter)->IsVisible())
            {
                // If the widget has a frame,
                // draw it before drawing the widget
                if ((*iter)->GetFrameSize() > 0)
                {
                    Rectangle rec = (*iter)->GetDimension();
                    rec.x -= (*iter)->GetFrameSize();
                    rec.y -= (*iter)->GetFrameSize();
                    rec.width += 2 * (*iter)->GetFrameSize();
                    rec.height += 2 * (*iter)->GetFrameSize();
                    graphics->pushClipArea(rec);
                    (*iter)->DrawFrame(graphics);
                    graphics->popClipArea();
                }

                graphics->pushClipArea((*iter)->GetDimension());
                (*iter)->Draw(graphics);
                graphics->popClipArea();
            }
        }

        graphics->popClipArea();
    }

    void BasicContainer::logicChildren()
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->Logic();
        }
    }

	void BasicContainer::ShowWidgetPart( WidgetPtr widget, Rectangle area )
	{
        Rectangle widgetArea = getChildrenArea();

        area.x += widget->GetX();
        area.y += widget->GetY();
        
        if (area.x + area.width > widgetArea.width)
        {
            widget->SetX(widget->GetX() - area.x - area.width + widgetArea.width);
        }

        if (area.y + area.height > widgetArea.height)
        {
            widget->SetY(widget->GetY() - area.y - area.height + widgetArea.height);
        }

        if (area.x < 0)
        {
            widget->SetX(widget->GetX() - area.x);
        }

        if (area.y < 0)
        {
            widget->SetY(widget->GetY() - area.y);
        }
    }


	void BasicContainer::SetInternalFocusHandler( FocusHandlerPtr focusHandler )
	{
        Widget::SetInternalFocusHandler(focusHandler);

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (mInternalFocusHandler == NULL)
            {
                (*iter)->_setFocusHandler(_getFocusHandler());
            }
            else
            {
                (*iter)->_setFocusHandler(mInternalFocusHandler);
            }
        }
    }

	gcn::WidgetPtr BasicContainer::FindWidgetById( const std::string& id )
	{
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if ((*iter)->getId() == id)
            {
                return (*iter);
            }
            
            BasicContainerPtr basicContainer = boost::shared_dynamic_cast<BasicContainer>(*iter);
            
            if (basicContainer)
            {
                WidgetPtr widget = basicContainer->FindWidgetById(id);
                
                if (widget)
                {
                    return widget;
                }
            }
        }

        return WidgetPtr();
    }

	BasicContainer::WidgetIteratorPair BasicContainer::GetChildren()
	{
		return WidgetIteratorPair(mWidgets.begin(), mWidgets.end());
	}

}
