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

#include "guichan/widgets/window.hpp"

#include "guichan/exception.hpp"
#include "guichan/font.hpp"
#include "guichan/graphics.hpp"
#include "guichan/mouseinput.hpp"

namespace gcn
{
    Window::Window()
            :mMoved(false)
    {
        SetFrameSize(1);
        setPadding(2);
        setTitleBarHeight(16);
        setAlignment(Graphics::CENTER);
        addMouseListener(this);
        setMovable(true);
        SetOpaque(true);
    }

    Window::Window(const std::string& caption)
            :mMoved(false)
    {
        setCaption(caption);
        SetFrameSize(1);
        setPadding(2);
        setTitleBarHeight(16);
        setAlignment(Graphics::CENTER);
        addMouseListener(this);
        setMovable(true);
        SetOpaque(true);
    }

    Window::~Window()
    {
    }

    void Window::setPadding(unsigned int padding)
    {
        mPadding = padding;
    }

    unsigned int Window::getPadding() const
    {
        return mPadding;
    }

    void Window::setTitleBarHeight(unsigned int height)
    {
        mTitleBarHeight = height;
    }

    unsigned int Window::getTitleBarHeight()
    {
        return mTitleBarHeight;
    }

    void Window::setCaption(const std::string& caption)
    {
        mCaption = caption;
    }

    const std::string& Window::getCaption() const
    {
        return mCaption;
    }

    void Window::setAlignment(Graphics::Alignment alignment)
    {
        mAlignment = alignment;
    }

    Graphics::Alignment Window::getAlignment() const
    {
        return mAlignment;
    }

    void Window::Draw(GraphicsPtr graphics)
    {
        const Color &faceColor = getBaseColor();
        Color highlightColor, shadowColor;
        const int alpha = getBaseColor().a;
        highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        Rectangle d = getChildrenArea();

        // Fill the background around the content
        graphics->setColor(faceColor);
        // Fill top
        graphics->fillRectangle(Rectangle(0,0,GetWidth(),d.y - 1));
        // Fill left
        graphics->fillRectangle(Rectangle(0,d.y - 1, d.x - 1, GetHeight() - d.y + 1));
        // Fill right
        graphics->fillRectangle(Rectangle(d.x + d.width + 1,
                                          d.y - 1,
                                          GetWidth() - d.x - d.width - 1,
                                          GetHeight() - d.y + 1));
        // Fill bottom
        graphics->fillRectangle(Rectangle(d.x - 1,
                                          d.y + d.height + 1,
                                          d.width + 2,
                                          GetHeight() - d.height - d.y - 1));

        if (IsOpaque())
        {
            graphics->fillRectangle(d);
        }

        // Construct a rectangle one pixel bigger than the content
        d.x -= 1;
        d.y -= 1;
        d.width += 2;
        d.height += 2;

        // Draw a border around the content
        graphics->setColor(shadowColor);
        // Top line
        graphics->drawLine(d.x,
                           d.y,
                           d.x + d.width - 2,
                           d.y);

        // Left line
        graphics->drawLine(d.x,
                           d.y + 1,
                           d.x,
                           d.y + d.height - 1);

        graphics->setColor(highlightColor);
        // Right line
        graphics->drawLine(d.x + d.width - 1,
                           d.y,
                           d.x + d.width - 1,
                           d.y + d.height - 2);
        // Bottom line
        graphics->drawLine(d.x + 1,
                           d.y + d.height - 1,
                           d.x + d.width - 1,
                           d.y + d.height - 1);

        DrawChildren(graphics);

        int textX;
        int textY;

        textY = ((int)getTitleBarHeight() - GetFont()->getHeight()) / 2;

        switch (getAlignment())
        {
          case Graphics::LEFT:
              textX = 4;
              break;
          case Graphics::CENTER:
              textX = GetWidth() / 2;
              break;
          case Graphics::RIGHT:
              textX = GetWidth() - 4;
              break;
          default:
              throw GCN_EXCEPTION("Unknown alignment.");
        }

        graphics->setColor(getForegroundColor());
        graphics->SetFont(GetFont());
        graphics->pushClipArea(Rectangle(0, 0, GetWidth(), getTitleBarHeight() - 1));
        graphics->drawText(getCaption(), textX, textY, getAlignment());
        graphics->popClipArea();
    }

    void Window::mousePressed(MouseEvent& mouseEvent)
    {
        if (mouseEvent.GetSource() != shared_from_this())
        {
            return;
        }

        if (GetParent())
        {
            GetParent()->MoveToTop(shared_from_this());
        }

        mDragOffsetX = mouseEvent.getX();
        mDragOffsetY = mouseEvent.getY();

        mMoved = mouseEvent.getY() <= (int)mTitleBarHeight;
    }

    void Window::mouseReleased(MouseEvent& mouseEvent)
    {
        mMoved = false;
    }

    void Window::mouseDragged(MouseEvent& mouseEvent)
    {
        if (mouseEvent.isConsumed() || mouseEvent.GetSource() != shared_from_this())
        {
            return;
        }

        if (isMovable() && mMoved)
        {
            SetPosition(mouseEvent.getX() - mDragOffsetX + GetX(),
                        mouseEvent.getY() - mDragOffsetY + GetY());
        }

        mouseEvent.consume();
    }

    Rectangle Window::getChildrenArea()
    {
        return Rectangle(getPadding(),
                         getTitleBarHeight(),
                         GetWidth() - getPadding() * 2,
                         GetHeight() - getPadding() - getTitleBarHeight());
    }

    void Window::setMovable(bool movable)
    {
        mMovable = movable;
    }

    bool Window::isMovable() const
    {
        return mMovable;
    }

    void Window::SetOpaque(bool opaque)
    {
        mOpaque = opaque;
    }

    bool Window::IsOpaque()
    {
        return mOpaque;
    }

    void Window::resizeToContent()
    {
        WidgetListIterator it;

        int w = 0, h = 0;
        for (it = mWidgets.begin(); it != mWidgets.end(); it++)
        {
            if ((*it)->GetX() + (*it)->GetWidth() > w)
            {
                w = (*it)->GetX() + (*it)->GetWidth();
            }

            if ((*it)->GetY() + (*it)->GetHeight() > h)
            {
                h = (*it)->GetY() + (*it)->GetHeight();
            }
        }

        SetSize(w + 2* getPadding(), h + getPadding() + getTitleBarHeight());
    }
}
