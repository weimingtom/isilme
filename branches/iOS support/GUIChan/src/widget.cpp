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
 *    notice, shared_from_this() list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, shared_from_this() list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from shared_from_this() software
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

#include "guichan/widget.hpp"

#include "guichan/actionevent.hpp"
#include "guichan/actionlistener.hpp"
#include "guichan/basiccontainer.hpp"
#include "guichan/deathlistener.hpp"
#include "guichan/defaultfont.hpp"
#include "guichan/event.hpp"
#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/graphics.hpp"
#include "guichan/keyinput.hpp"
#include "guichan/keylistener.hpp"
#include "guichan/mouseinput.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/widgetlistener.hpp"

namespace gcn
{
    FontPtr Widget::mGlobalFont;
    DefaultFontPtr Widget::mDefaultFont;
    std::list<Widget*> Widget::mWidgets;

    Widget::Widget()
            : mForegroundColor(0x000000),
              mBackgroundColor(0xffffff),
              mBaseColor(0x808090),
              mSelectionColor(0xc3d9ff),
              mFocusHandler(FocusHandlerPtr()),
              mInternalFocusHandler(FocusHandlerPtr()),
              mParent(WidgetPtr()),
              mFrameSize(0),
              mFocusable(false),
              mVisible(true),
              mTabIn(true),
              mTabOut(true),
              mEnabled(true),
              mCurrentFont(FontPtr())
    {
        mWidgets.push_back(this);
    }

    Widget::~Widget()
    {
        DeathListenerIterator iter;

        for (iter = mDeathListeners.begin(); iter != mDeathListeners.end(); ++iter)
        {
            Event event(shared_from_this());
            (*iter)->death(event);
        }

        _setFocusHandler(FocusHandlerPtr());

        mWidgets.remove(this);
    }

    void Widget::DrawFrame(GraphicsPtr graphics)
    {
        Color faceColor = getBaseColor();
        Color highlightColor, shadowColor;
        int alpha = getBaseColor().a;
        int width = GetWidth() + GetFrameSize() * 2 - 1;
        int height = GetHeight() + GetFrameSize() * 2 - 1;
        highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        unsigned int i;
        for (i = 0; i < GetFrameSize(); ++i)
        {
            graphics->setColor(shadowColor);
            graphics->drawLine(i,i, width - i, i);
            graphics->drawLine(i,i + 1, i, height - i - 1);
            graphics->setColor(highlightColor);
            graphics->drawLine(width - i,i + 1, width - i, height - i);
            graphics->drawLine(i,height - i, width - i - 1, height - i);
        }
    }

    void Widget::_setParent(WidgetPtr parent)
    {
        mParent = parent;
    }

	gcn::WidgetPtr Widget::GetParent() const
	{
        return mParent.lock();
    }

    void Widget::SetWidth(int width)
    {
        Rectangle newDimension = mDimension;
        newDimension.width = width;

        SetDimension(newDimension);
    }

    int Widget::GetWidth() const
    {
        return mDimension.width;
    }

    void Widget::SetHeight(int height)
    {
        Rectangle newDimension = mDimension;
        newDimension.height = height;

        SetDimension(newDimension);
    }

    int Widget::GetHeight() const
    {
        return mDimension.height;
    }

    void Widget::SetX(int x)
    {
        Rectangle newDimension = mDimension;
        newDimension.x = x;

        SetDimension(newDimension);
    }

    int Widget::GetX() const
    {
        return mDimension.x;
    }

    void Widget::SetY(int y)
    {
        Rectangle newDimension = mDimension;
        newDimension.y = y;

        SetDimension(newDimension);
    }

    int Widget::GetY() const
    {
        return mDimension.y;
    }

    void Widget::SetPosition(int x, int y)
    {
        Rectangle newDimension = mDimension;
        newDimension.x = x;
        newDimension.y = y;
        
        SetDimension(newDimension);
    }

    void Widget::SetDimension(const Rectangle& dimension)
    { 
        Rectangle oldDimension = mDimension;
        mDimension = dimension;

        if (mDimension.width != oldDimension.width
            || mDimension.height != oldDimension.height)
        {
            distributeResizedEvent();
        }

        if (mDimension.x != oldDimension.x
            || mDimension.y != oldDimension.y)
        {
            distributeMovedEvent();
        }
    }

    void Widget::SetFrameSize(unsigned int frameSize)
    {
        mFrameSize = frameSize;
    }

    unsigned int Widget::GetFrameSize() const
    {
        return mFrameSize;
    }

    const Rectangle& Widget::GetDimension() const
    {
        return mDimension;
    }

    const std::string& Widget::getActionEventId() const
    {
        return mActionEventId;
    }

    void Widget::setActionEventId(const std::string& actionEventId)
    {
        mActionEventId = actionEventId;
    }

    bool Widget::IsFocused()
    {
        if (!mFocusHandler)
        {
            return false;
        }
		
        return mFocusHandler->IsFocused(shared_from_this());
    }

    void Widget::SetFocusable(bool focusable)
    {
        if (!focusable && IsFocused())
        {
            mFocusHandler->FocusNone();
        }

        mFocusable = focusable;
    }

    bool Widget::IsFocusable() const
    {
        return mFocusable && IsVisible() && IsEnabled();
    }

    void Widget::requestFocus()
    {
        if (!mFocusHandler)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (IsFocusable())
        {
            mFocusHandler->RequestFocus(shared_from_this());
        }
    }

    void Widget::requestMoveToTop()
    {
        if (mParent.lock())
        {
            mParent.lock()->MoveToTop(shared_from_this());
        }
    }

    void Widget::requestMoveToBottom()
    {
        if (mParent.lock())
        {
            mParent.lock()->MoveToBottom(shared_from_this());
        }
    }

    void Widget::SetVisible(bool visible)
    {
        if (!visible && IsFocused())
        {
            mFocusHandler->FocusNone();
        }
        
        if (visible)
        {
            distributeShownEvent();
        }
        else if(!visible)
        {
            distributeHiddenEvent();
        }

        mVisible = visible;
    }

    bool Widget::IsVisible() const
    {
        if (!GetParent())
        {
            return mVisible;
        }
        else
        {
            return mVisible && GetParent()->IsVisible();
        }
    }

    void Widget::setBaseColor(const Color& color)
    {
        mBaseColor = color;
    }

    const Color& Widget::getBaseColor() const
    {
        return mBaseColor;
    }

    void Widget::setForegroundColor(const Color& color)
    {
        mForegroundColor = color;
    }

    const Color& Widget::getForegroundColor() const
    {
        return mForegroundColor;
    }

    void Widget::setBackgroundColor(const Color& color)
    {
        mBackgroundColor = color;
    }

    const Color& Widget::getBackgroundColor() const
    {
        return mBackgroundColor;
    }

    void Widget::setSelectionColor(const Color& color)
    {
        mSelectionColor = color;
    }

    const Color& Widget::getSelectionColor() const
    {
        return mSelectionColor;
    }    
    
	void Widget::_setFocusHandler( FocusHandlerPtr focusHandler )
	{
        if (mFocusHandler)
        {
            releaseModalFocus();
            mFocusHandler->Remove(shared_from_this());
        }

        if (focusHandler)
        {
            focusHandler->Add(shared_from_this());
        }

        mFocusHandler = focusHandler;
    }

	gcn::FocusHandlerPtr Widget::_getFocusHandler()
	{
        return mFocusHandler;
    }

    void Widget::addActionListener(ActionListener* actionListener)
    {
        mActionListeners.push_back(actionListener);
    }

    void Widget::removeActionListener(ActionListener* actionListener)
    {
        mActionListeners.remove(actionListener);
    }

    void Widget::addDeathListener(DeathListener* deathListener)
    {
        mDeathListeners.push_back(deathListener);
    }

    void Widget::removeDeathListener(DeathListener* deathListener)
    {
        mDeathListeners.remove(deathListener);
    }

    void Widget::addKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.push_back(keyListener);
    }

    void Widget::removeKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.remove(keyListener);
    }

    void Widget::addFocusListener(FocusListener* focusListener)
    {
        mFocusListeners.push_back(focusListener);
    }

    void Widget::removeFocusListener(FocusListener* focusListener)
    {
        mFocusListeners.remove(focusListener);
    }

    void Widget::addMouseListener(MouseListener* mouseListener)
    {
        mMouseListeners.push_back(mouseListener);
    }

    void Widget::removeMouseListener(MouseListener* mouseListener)
    {
        mMouseListeners.remove(mouseListener);
    }

    void Widget::addWidgetListener(WidgetListener* widgetListener)
    {
        mWidgetListeners.push_back(widgetListener);
    }

    void Widget::removeWidgetListener(WidgetListener* widgetListener)
    {
        mWidgetListeners.remove(widgetListener);
    }

    void Widget::getAbsolutePosition(int& x, int& y) const
    {
        if (!GetParent())
        {
            x = mDimension.x;
            y = mDimension.y;
            return;
        }

        int parentX;
        int parentY;

        GetParent()->getAbsolutePosition(parentX, parentY);

        x = parentX + mDimension.x + GetParent()->getChildrenArea().x;
        y = parentY + mDimension.y + GetParent()->getChildrenArea().y;
    }

    FontPtr Widget::GetFont() const
    {
        if (!mCurrentFont)
        {
            if (!mGlobalFont)
            {
                return mDefaultFont;
            }

            return mGlobalFont;
        }

        return mCurrentFont;
    }

    void Widget::SetGlobalFont(FontPtr font)
    {
        mGlobalFont = font;

        std::list<Widget*>::iterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); ++iter)
        {
            if (!(*iter)->mCurrentFont)
            {
                (*iter)->fontChanged();
            }
        }
    }

    void Widget::SetFont(FontPtr font)
    {
        mCurrentFont = font;
        fontChanged();
    }

    bool Widget::widgetExists(const WidgetPtr widget)
    {
        bool result = false;

        std::list<Widget*>::iterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); ++iter)
        {
            if ((*iter) == widget.get())
            {
                return true;
            }
        }

        return result;
    }

    bool Widget::isTabInEnabled() const
    {
        return mTabIn;
    }

    void Widget::setTabInEnabled(bool enabled)
    {
        mTabIn = enabled;
    }

    bool Widget::isTabOutEnabled() const
    {
        return mTabOut;
    }

    void Widget::setTabOutEnabled(bool enabled)
    {
        mTabOut = enabled;
    }

    void Widget::SetSize(int width, int height)
    {
        Rectangle newDimension = mDimension;
        newDimension.width = width;
        newDimension.height = height;

        SetDimension(newDimension);
    }

    void Widget::SetEnabled(bool enabled)
    {
        mEnabled = enabled;
    }

    bool Widget::IsEnabled() const
    {
        return mEnabled && IsVisible();
    }

    void Widget::requestModalFocus()
    {
        if (mFocusHandler == NULL)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        mFocusHandler->RequestModalFocus(shared_from_this());
    }

    void Widget::requestModalMouseInputFocus()
    {
        if (mFocusHandler == NULL)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        mFocusHandler->RequestModalMouseInputFocus(shared_from_this());
    }

    void Widget::releaseModalFocus()
    {
        if (mFocusHandler == NULL)
        {
            return;
        }

        mFocusHandler->ReleaseModalFocus(shared_from_this());
    }

    void Widget::releaseModalMouseInputFocus()
    {
        if (mFocusHandler == NULL)
        {
            return;
        }

        mFocusHandler->ReleaseModalMouseInputFocus(shared_from_this());
    }

    bool Widget::isModalFocused() const
    {
        if (mFocusHandler == NULL)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (GetParent() != NULL)
        {
            return (mFocusHandler->GetModalFocused() == shared_from_this()) 
                || GetParent()->isModalFocused();
        }

        return mFocusHandler->GetModalFocused() == shared_from_this();
    }

    bool Widget::isModalMouseInputFocused() const
    {
        if (mFocusHandler == NULL)
        {
            throw GCN_EXCEPTION("No focushandler set (did you add the widget to the gui?).");
        }

        if (GetParent())
        {
            return (mFocusHandler->GetModalMouseInputFocused() == shared_from_this()) 
                || GetParent()->isModalMouseInputFocused();
        }

        return mFocusHandler->GetModalMouseInputFocused() == shared_from_this();
    }

    WidgetPtr Widget::GetWidgetAt(int x, int y)
    {
        return WidgetPtr();
    }

    const std::list<MouseListener*>& Widget::_getMouseListeners()
    {
        return mMouseListeners;
    }

    const std::list<KeyListener*>& Widget::_getKeyListeners()
    {
        return mKeyListeners;
    }

    const std::list<FocusListener*>& Widget::_getFocusListeners()
    {
        return mFocusListeners;
    }

    Rectangle Widget::getChildrenArea()
    {
        return Rectangle(0, 0, 0, 0);
    }

    FocusHandlerPtr Widget::_getInternalFocusHandler()
    {
        return mInternalFocusHandler;
    }

    void Widget::SetInternalFocusHandler(FocusHandlerPtr focusHandler)
    {
        mInternalFocusHandler = focusHandler;
    }

    void Widget::setId(const std::string& id)
    {
        mId = id;
    }

    const std::string& Widget::getId()
    {
        return mId;
    }

    void Widget::distributeResizedEvent()
    {
        WidgetListenerIterator iter;

        for (iter = mWidgetListeners.begin(); iter != mWidgetListeners.end(); ++iter)
        {
            Event event(shared_from_this());
            (*iter)->widgetResized(event);
        }
    }

    void Widget::distributeMovedEvent()
    {
        WidgetListenerIterator iter;

        for (iter = mWidgetListeners.begin(); iter != mWidgetListeners.end(); ++iter)
        {
            Event event(shared_from_this());
            (*iter)->widgetMoved(event);
        }
    }

    void Widget::distributeHiddenEvent()
    {
        WidgetListenerIterator iter;

        for (iter = mWidgetListeners.begin(); iter != mWidgetListeners.end(); ++iter)
        {
            Event event(shared_from_this());
            (*iter)->widgetHidden(event);
        }
    }

    void Widget::distributeActionEvent()
    {
        ActionListenerIterator iter;
        for (iter = mActionListeners.begin(); iter != mActionListeners.end(); ++iter)
        {
            ActionEvent actionEvent(shared_from_this(), mActionEventId);
            (*iter)->action(actionEvent);
        }
    }

    void Widget::distributeShownEvent()
    {
        WidgetListenerIterator iter;

        for (iter = mWidgetListeners.begin(); iter != mWidgetListeners.end(); ++iter)
        {
            Event event(shared_from_this());
            (*iter)->widgetShown(event);
        }
    }

    void Widget::showPart(Rectangle rectangle)
    {
        if (mParent.lock())
        {
            mParent.lock()->ShowWidgetPart(shared_from_this(), rectangle);
        }                
    }
}
