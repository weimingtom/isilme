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

#include "guichan/widgets/scrollarea.hpp"

#include "guichan/exception.hpp"
#include "guichan/graphics.hpp"

namespace gcn
{
    ScrollArea::ScrollArea()
    {
        mVScroll = 0;
        mHScroll = 0;
        mHPolicy = SHOW_AUTO;
        mVPolicy = SHOW_AUTO;
        mScrollbarWidth = 12;
        mUpButtonPressed = false;
        mDownButtonPressed = false;
        mLeftButtonPressed = false;
        mRightButtonPressed = false;
        mUpButtonScrollAmount = 10;
        mDownButtonScrollAmount = 10;
        mLeftButtonScrollAmount = 10;
        mRightButtonScrollAmount = 10;
        mIsVerticalMarkerDragged = false;
        mIsHorizontalMarkerDragged =false;
        mOpaque = true;

        addMouseListener(this);
    }

    ScrollArea::ScrollArea(WidgetPtr content)
    {
        mVScroll = 0;
        mHScroll = 0;
        mHPolicy = SHOW_AUTO;
        mVPolicy = SHOW_AUTO;
        mScrollbarWidth = 12;
        mUpButtonPressed = false;
        mDownButtonPressed = false;
        mLeftButtonPressed = false;
        mRightButtonPressed = false;
        mUpButtonScrollAmount = 10;
        mDownButtonScrollAmount = 10;
        mLeftButtonScrollAmount = 10;
        mRightButtonScrollAmount = 10;
        mIsVerticalMarkerDragged = false;
        mIsHorizontalMarkerDragged =false;
        mOpaque = true;

        SetContent(content);
        addMouseListener(this);
    }

    ScrollArea::ScrollArea(WidgetPtr content,
                           ScrollPolicy hPolicy,
                           ScrollPolicy vPolicy)
    {
        mVScroll = 0;
        mHScroll = 0;
        mHPolicy = hPolicy;
        mVPolicy = vPolicy;
        mScrollbarWidth = 12;
        mUpButtonPressed = false;
        mDownButtonPressed = false;
        mLeftButtonPressed = false;
        mRightButtonPressed = false;
        mUpButtonScrollAmount = 10;
        mDownButtonScrollAmount = 10;
        mLeftButtonScrollAmount = 10;
        mRightButtonScrollAmount = 10;
        mIsVerticalMarkerDragged = false;
        mIsHorizontalMarkerDragged =false;
        mOpaque = true;

        SetContent(content);
        addMouseListener(this);
    }

    ScrollArea::~ScrollArea()
    {
        SetContent(WidgetPtr());
    }

	void ScrollArea::SetContent( WidgetPtr widget )
	{
        if (widget != NULL)
        {
            Clear();
            Add(widget);
            widget->SetPosition(0,0);
        }
        else
        {
            Clear();
        }

        checkPolicies();
    }

	gcn::WidgetPtr ScrollArea::GetContent()
	{
        if (mWidgets.size() > 0)
        {
            return *mWidgets.begin();
        }

        return WidgetPtr();
    }

    void ScrollArea::SetHorizontalScrollPolicy(ScrollPolicy hPolicy)
    {
        mHPolicy = hPolicy;
        checkPolicies();
    }

    ScrollArea::ScrollPolicy ScrollArea::GetHorizontalScrollPolicy() const
    {
        return mHPolicy;
    }

    void ScrollArea::SetVerticalScrollPolicy(ScrollPolicy vPolicy)
    {
        mVPolicy = vPolicy;
        checkPolicies();
    }

    ScrollArea::ScrollPolicy ScrollArea::GetVerticalScrollPolicy() const
    {
        return mVPolicy;
    }

    void ScrollArea::SetScrollPolicy(ScrollPolicy hPolicy, ScrollPolicy vPolicy)
    {
        mHPolicy = hPolicy;
        mVPolicy = vPolicy;
        checkPolicies();
    }

    void ScrollArea::SetVerticalScrollAmount(int vScroll)
    {
        int max = GetVerticalMaxScroll();

        mVScroll = vScroll;

        if (vScroll > max)
        {
            mVScroll = max;
        }

        if (vScroll < 0)
        {
            mVScroll = 0;
        }
    }

    int ScrollArea::GetVerticalScrollAmount() const
    {
        return mVScroll;
    }

    void ScrollArea::SetHorizontalScrollAmount(int hScroll)
    {
        int max = GetHorizontalMaxScroll();

        mHScroll = hScroll;

        if (hScroll > max)
        {
            mHScroll = max;
        }
        else if (hScroll < 0)
        {
            mHScroll = 0;
        }
    }

    int ScrollArea::GetHorizontalScrollAmount() const
    {
        return mHScroll;
    }

    void ScrollArea::SetScrollAmount(int hScroll, int vScroll)
    {
        SetHorizontalScrollAmount(hScroll);
        SetVerticalScrollAmount(vScroll);
    }

    int ScrollArea::GetHorizontalMaxScroll()
    {
        checkPolicies();

        if (GetContent() == NULL)
        {
            return 0;
        }

        int value = GetContent()->GetWidth() - getChildrenArea().width +
            2 * GetContent()->GetFrameSize();

        if (value < 0)
        {
            return 0;
        }

        return value;
    }

    int ScrollArea::GetVerticalMaxScroll()
    {
        checkPolicies();

        if (GetContent() == NULL)
        {
            return 0;
        }

        int value;

        value = GetContent()->GetHeight() - getChildrenArea().height +
            2 * GetContent()->GetFrameSize();

        if (value < 0)
        {
            return 0;
        }

        return value;
    }

    void ScrollArea::SetScrollbarWidth(int width)
    {
        if (width > 0)
        {
            mScrollbarWidth = width;
        }
        else
        {
            throw GCN_EXCEPTION("Width should be greater then 0.");
        }
    }

    int ScrollArea::GetScrollbarWidth() const
    {
        return mScrollbarWidth;
    }

    void ScrollArea::mousePressed(MouseEvent& mouseEvent)
    {
        int x = mouseEvent.getX();
        int y = mouseEvent.getY();

        if (getUpButtonDimension().isPointInRect(x, y))
        {
            SetVerticalScrollAmount(GetVerticalScrollAmount()
                                    - mUpButtonScrollAmount);
            mUpButtonPressed = true;
        }
        else if (getDownButtonDimension().isPointInRect(x, y))
        {
            SetVerticalScrollAmount(GetVerticalScrollAmount()
                                    + mDownButtonScrollAmount);
            mDownButtonPressed = true;
        }
        else if (getLeftButtonDimension().isPointInRect(x, y))
        {
            SetHorizontalScrollAmount(GetHorizontalScrollAmount()
                                      - mLeftButtonScrollAmount);
            mLeftButtonPressed = true;
        }
        else if (getRightButtonDimension().isPointInRect(x, y))
        {
            SetHorizontalScrollAmount(GetHorizontalScrollAmount()
                                      + mRightButtonScrollAmount);
            mRightButtonPressed = true;
        }
        else if (getVerticalMarkerDimension().isPointInRect(x, y))
        {
            mIsHorizontalMarkerDragged = false;
            mIsVerticalMarkerDragged = true;

            mVerticalMarkerDragOffset = y - getVerticalMarkerDimension().y;
        }
        else if (getVerticalBarDimension().isPointInRect(x,y))
        {
            if (y < getVerticalMarkerDimension().y)
            {
                SetVerticalScrollAmount(GetVerticalScrollAmount()
                                        - (int)(getChildrenArea().height * 0.95));
            }
            else
            {
                SetVerticalScrollAmount(GetVerticalScrollAmount()
                                        + (int)(getChildrenArea().height * 0.95));
            }
        }
        else if (getHorizontalMarkerDimension().isPointInRect(x, y))
        {
            mIsHorizontalMarkerDragged = true;
            mIsVerticalMarkerDragged = false;

            mHorizontalMarkerDragOffset = x - getHorizontalMarkerDimension().x;
        }
        else if (getHorizontalBarDimension().isPointInRect(x,y))
        {
            if (x < getHorizontalMarkerDimension().x)
            {
                SetHorizontalScrollAmount(GetHorizontalScrollAmount()
                                          - (int)(getChildrenArea().width * 0.95));
            }
            else
            {
                SetHorizontalScrollAmount(GetHorizontalScrollAmount()
                                          + (int)(getChildrenArea().width * 0.95));
            }
        }
    }

    void ScrollArea::mouseReleased(MouseEvent& mouseEvent)
    {
        mUpButtonPressed = false;
        mDownButtonPressed = false;
        mLeftButtonPressed = false;
        mRightButtonPressed = false;
        mIsHorizontalMarkerDragged = false;
        mIsVerticalMarkerDragged = false;

        mouseEvent.consume();
    }

    void ScrollArea::mouseDragged(MouseEvent& mouseEvent)
    {
        if (mIsVerticalMarkerDragged)
        {
            int pos = mouseEvent.getY() - getVerticalBarDimension().y  - mVerticalMarkerDragOffset;
            int length = getVerticalMarkerDimension().height;

            Rectangle barDim = getVerticalBarDimension();

            if ((barDim.height - length) > 0)
            {
                SetVerticalScrollAmount((GetVerticalMaxScroll() * pos)
                                         / (barDim.height - length));
            }
            else
            {
                SetVerticalScrollAmount(0);
            }
        }

        if (mIsHorizontalMarkerDragged)
        {
            int pos = mouseEvent.getX() - getHorizontalBarDimension().x  - mHorizontalMarkerDragOffset;
            int length = getHorizontalMarkerDimension().width;

            Rectangle barDim = getHorizontalBarDimension();

            if ((barDim.width - length) > 0)
            {
                SetHorizontalScrollAmount((GetHorizontalMaxScroll() * pos)
                                          / (barDim.width - length));
            }
            else
            {
                SetHorizontalScrollAmount(0);
            }
        }

        mouseEvent.consume();
    }

    void ScrollArea::Draw(GraphicsPtr graphics)
    {
        drawBackground(graphics);

        if (mVBarVisible)
        {
            drawUpButton(graphics);
            drawDownButton(graphics);
            drawVBar(graphics);
            drawVMarker(graphics);
        }

        if (mHBarVisible)
        {
            drawLeftButton(graphics);
            drawRightButton(graphics);
            drawHBar(graphics);
            drawHMarker(graphics);
        }

        if (mHBarVisible && mVBarVisible)
        {
            graphics->setColor(getBaseColor());
            graphics->fillRectangle(Rectangle(GetWidth() - mScrollbarWidth,
                                              GetHeight() - mScrollbarWidth,
                                              mScrollbarWidth,
                                              mScrollbarWidth));
        }

        DrawChildren(graphics);
    }

    void ScrollArea::drawHBar(GraphicsPtr graphics)
    {
        Rectangle dim = getHorizontalBarDimension();

        graphics->pushClipArea(dim);

        int alpha = getBaseColor().a;
        Color trackColor = getBaseColor() - 0x101010;
        trackColor.a = alpha;
        Color shadowColor = getBaseColor() - 0x303030;
        shadowColor.a = alpha;

        graphics->setColor(trackColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(shadowColor);
        graphics->drawLine(0, 0, dim.width, 0);

        graphics->popClipArea();
    }

    void ScrollArea::drawVBar(GraphicsPtr graphics)
    {
        Rectangle dim = getVerticalBarDimension();

        graphics->pushClipArea(dim);

        int alpha = getBaseColor().a;
        Color trackColor = getBaseColor() - 0x101010;
        trackColor.a = alpha;
        Color shadowColor = getBaseColor() - 0x303030;
        shadowColor.a = alpha;

        graphics->setColor(trackColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(shadowColor);
        graphics->drawLine(0, 0, 0, dim.height);

        graphics->popClipArea();
    }

    void ScrollArea::drawBackground(GraphicsPtr graphics)
    {
        if (isOpaque())
        {
            graphics->setColor(getBackgroundColor());
            graphics->fillRectangle(getChildrenArea());
        }
    }

    void ScrollArea::drawUpButton(GraphicsPtr graphics)
    {
        Rectangle dim = getUpButtonDimension();
        graphics->pushClipArea(dim);

        Color highlightColor;
        Color shadowColor;
        Color faceColor;
        int offset;
        int alpha = getBaseColor().a;

        if (mUpButtonPressed)
        {
            faceColor = getBaseColor() - 0x303030;
            faceColor.a = alpha;
            highlightColor = faceColor - 0x303030;
            highlightColor.a = alpha;
            shadowColor = getBaseColor();
            shadowColor.a = alpha;

            offset = 1;
        }
        else
        {
            faceColor = getBaseColor();
            faceColor.a = alpha;
            highlightColor = faceColor + 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor - 0x303030;
            shadowColor.a = alpha;

            offset = 0;
        }

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);

        graphics->setColor(getForegroundColor());

        int i;
        int w = dim.height / 2;
        int h = w / 2 + 2;
        for (i = 0; i < w / 2; ++i)
        {
            graphics->drawLine(w - i + offset,
                               i + h + offset,
                               w + i + offset,
                               i + h + offset);
        }

        graphics->popClipArea();
    }

    void ScrollArea::drawDownButton(GraphicsPtr graphics)
    {
        Rectangle dim = getDownButtonDimension();
        graphics->pushClipArea(dim);

        Color highlightColor;
        Color shadowColor;
        Color faceColor;
        int offset;
        int alpha = getBaseColor().a;

        if (mDownButtonPressed)
        {
            faceColor = getBaseColor() - 0x303030;
            faceColor.a = alpha;
            highlightColor = faceColor - 0x303030;
            highlightColor.a = alpha;
            shadowColor = getBaseColor();
            shadowColor.a = alpha;

            offset = 1;
        }
        else
        {
            faceColor = getBaseColor();
            faceColor.a = alpha;
            highlightColor = faceColor + 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor - 0x303030;
            shadowColor.a = alpha;

            offset = 0;
        }

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);

        graphics->setColor(getForegroundColor());

        int i;
        int w = dim.height / 2;
        int h = w + 1;
        for (i = 0; i < w / 2; ++i)
        {
            graphics->drawLine(w - i + offset,
                               -i + h + offset,
                               w + i + offset,
                               -i + h + offset);
        }

        graphics->popClipArea();
    }

    void ScrollArea::drawLeftButton(GraphicsPtr graphics)
    {
        Rectangle dim = getLeftButtonDimension();
        graphics->pushClipArea(dim);

        Color highlightColor;
        Color shadowColor;
        Color faceColor;
        int offset;
        int alpha = getBaseColor().a;

        if (mLeftButtonPressed)
        {
            faceColor = getBaseColor() - 0x303030;
            faceColor.a = alpha;
            highlightColor = faceColor - 0x303030;
            highlightColor.a = alpha;
            shadowColor = getBaseColor();
            shadowColor.a = alpha;

            offset = 1;
        }
        else
        {
            faceColor = getBaseColor();
            faceColor.a = alpha;
            highlightColor = faceColor + 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor - 0x303030;
            shadowColor.a = alpha;

            offset = 0;
        }

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);

        graphics->setColor(getForegroundColor());

        int i;
        int w = dim.width / 2;
        int h = w - 2;
        for (i = 0; i < w / 2; ++i)
        {
            graphics->drawLine(i + h + offset,
                               w - i + offset,
                               i + h + offset,
                               w + i + offset);
        }

        graphics->popClipArea();
    }

    void ScrollArea::drawRightButton(GraphicsPtr graphics)
    {
        Rectangle dim = getRightButtonDimension();
        graphics->pushClipArea(dim);

        Color highlightColor;
        Color shadowColor;
        Color faceColor;
        int offset;
        int alpha = getBaseColor().a;

        if (mRightButtonPressed)
        {
            faceColor = getBaseColor() - 0x303030;
            faceColor.a = alpha;
            highlightColor = faceColor - 0x303030;
            highlightColor.a = alpha;
            shadowColor = getBaseColor();
            shadowColor.a = alpha;

            offset = 1;
        }
        else
        {
            faceColor = getBaseColor();
            faceColor.a = alpha;
            highlightColor = faceColor + 0x303030;
            highlightColor.a = alpha;
            shadowColor = faceColor - 0x303030;
            shadowColor.a = alpha;

            offset = 0;
        }

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(0, 0, dim.width, dim.height));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);

        graphics->setColor(getForegroundColor());

        int i;
        int w = dim.width / 2;
        int h = w + 1;
        for (i = 0; i < w / 2; ++i)
        {
            graphics->drawLine(-i + h + offset,
                               w - i + offset,
                               -i + h + offset,
                               w + i + offset);
        }

        graphics->popClipArea();
    }

    void ScrollArea::drawVMarker(GraphicsPtr graphics)
    {
        Rectangle dim = getVerticalMarkerDimension();
        graphics->pushClipArea(dim);

        int alpha = getBaseColor().a;
        Color faceColor = getBaseColor();
        faceColor.a = alpha;
        Color highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        Color shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(1, 1, dim.width - 1, dim.height - 1));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);

        graphics->popClipArea();
    }

    void ScrollArea::drawHMarker(GraphicsPtr graphics)
    {
        Rectangle dim = getHorizontalMarkerDimension();
        graphics->pushClipArea(dim);

        int alpha = getBaseColor().a;
        Color faceColor = getBaseColor();
        faceColor.a = alpha;
        Color highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        Color shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        graphics->setColor(faceColor);
        graphics->fillRectangle(Rectangle(1, 1, dim.width - 1, dim.height - 1));

        graphics->setColor(highlightColor);
        graphics->drawLine(0, 0, dim.width - 1, 0);
        graphics->drawLine(0, 1, 0, dim.height - 1);

        graphics->setColor(shadowColor);
        graphics->drawLine(1, dim.height - 1, dim.width - 1, dim.height - 1);
        graphics->drawLine(dim.width - 1, 0, dim.width - 1, dim.height - 1);

        graphics->popClipArea();
    }

    void ScrollArea::Logic()
    {
        checkPolicies();

        SetVerticalScrollAmount(GetVerticalScrollAmount());
        SetHorizontalScrollAmount(GetHorizontalScrollAmount());

        if (GetContent() != NULL)
        {
            GetContent()->SetPosition(-mHScroll + GetContent()->GetFrameSize(),
                                      -mVScroll + GetContent()->GetFrameSize());
            GetContent()->Logic();
        }
    }

    void ScrollArea::checkPolicies()
    {
        int w = GetWidth();
        int h = GetHeight();

        mHBarVisible = false;
        mVBarVisible = false;


        if (!GetContent())
        {
            mHBarVisible = (mHPolicy == SHOW_ALWAYS);
            mVBarVisible = (mVPolicy == SHOW_ALWAYS);
            return;
        }

        if (mHPolicy == SHOW_AUTO &&
            mVPolicy == SHOW_AUTO)
        {
            if (GetContent()->GetWidth() <= w
                && GetContent()->GetHeight() <= h)
            {
                mHBarVisible = false;
                mVBarVisible = false;
            }

            if (GetContent()->GetWidth() > w)
            {
                mHBarVisible = true;
            }

            if ((GetContent()->GetHeight() > h)
                || (mHBarVisible && GetContent()->GetHeight() > h - mScrollbarWidth))
            {
                mVBarVisible = true;
            }

            if (mVBarVisible && GetContent()->GetWidth() > w - mScrollbarWidth)
            {
                mHBarVisible = true;
            }

            return;
        }

        switch (mHPolicy)
        {
          case SHOW_NEVER:
              mHBarVisible = false;
              break;

          case SHOW_ALWAYS:
              mHBarVisible = true;
              break;

          case SHOW_AUTO:
              if (mVPolicy == SHOW_NEVER)
              {
                  mHBarVisible = GetContent()->GetWidth() > w;
              }
              else // (mVPolicy == SHOW_ALWAYS)
              {
                  mHBarVisible = GetContent()->GetWidth() > w - mScrollbarWidth;
              }
              break;

          default:
              throw GCN_EXCEPTION("Horizontal scroll policy invalid.");
        }

        switch (mVPolicy)
        {
          case SHOW_NEVER:
              mVBarVisible = false;
              break;

          case SHOW_ALWAYS:
              mVBarVisible = true;
              break;

          case SHOW_AUTO:
              if (mHPolicy == SHOW_NEVER)
              {
                  mVBarVisible = GetContent()->GetHeight() > h;
              }
              else // (mHPolicy == SHOW_ALWAYS)
              {
                  mVBarVisible = GetContent()->GetHeight() > h - mScrollbarWidth;
              }
              break;
          default:
              throw GCN_EXCEPTION("Vertical scroll policy invalid.");
        }
    }

    Rectangle ScrollArea::getUpButtonDimension()
    {
        if (!mVBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        return Rectangle(GetWidth() - mScrollbarWidth,
                         0,
                         mScrollbarWidth,
                         mScrollbarWidth);
    }

    Rectangle ScrollArea::getDownButtonDimension()
    {
        if (!mVBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        if (mVBarVisible && mHBarVisible)
        {
            return Rectangle(GetWidth() - mScrollbarWidth,
                             GetHeight() - mScrollbarWidth*2,
                             mScrollbarWidth,
                             mScrollbarWidth);
        }

        return Rectangle(GetWidth() - mScrollbarWidth,
                         GetHeight() - mScrollbarWidth,
                         mScrollbarWidth,
                         mScrollbarWidth);
    }

    Rectangle ScrollArea::getLeftButtonDimension()
    {
        if (!mHBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        return Rectangle(0,
                         GetHeight() - mScrollbarWidth,
                         mScrollbarWidth,
                         mScrollbarWidth);
    }

    Rectangle ScrollArea::getRightButtonDimension()
    {
        if (!mHBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        if (mVBarVisible && mHBarVisible)
        {
            return Rectangle(GetWidth() - mScrollbarWidth*2,
                             GetHeight() - mScrollbarWidth,
                             mScrollbarWidth,
                             mScrollbarWidth);
        }

        return Rectangle(GetWidth() - mScrollbarWidth,
                         GetHeight() - mScrollbarWidth,
                         mScrollbarWidth,
                         mScrollbarWidth);
    }

    Rectangle ScrollArea::getChildrenArea()
    {
        Rectangle area = Rectangle(0, 
                                   0,
                                   mVBarVisible ? GetWidth() - mScrollbarWidth : GetWidth(),
                                   mHBarVisible ? GetHeight() - mScrollbarWidth : GetHeight()); 
        
        if (area.width < 0 || area.height < 0)
            return Rectangle();

        return area;
    }

    Rectangle ScrollArea::getVerticalBarDimension()
    {
        if (!mVBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        if (mHBarVisible)
        {
            return Rectangle(GetWidth() - mScrollbarWidth,
                             getUpButtonDimension().height,
                             mScrollbarWidth,
                             GetHeight()
                             - getUpButtonDimension().height
                             - getDownButtonDimension().height
                             - mScrollbarWidth);
        }

        return Rectangle(GetWidth() - mScrollbarWidth,
                         getUpButtonDimension().height,
                         mScrollbarWidth,
                         GetHeight()
                         - getUpButtonDimension().height
                         - getDownButtonDimension().height);
    }

    Rectangle ScrollArea::getHorizontalBarDimension()
    {
        if (!mHBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        if (mVBarVisible)
        {
            return Rectangle(getLeftButtonDimension().width,
                             GetHeight() - mScrollbarWidth,
                             GetWidth()
                             - getLeftButtonDimension().width
                             - getRightButtonDimension().width
                             - mScrollbarWidth,
                             mScrollbarWidth);
        }

        return Rectangle(getLeftButtonDimension().width,
                         GetHeight() - mScrollbarWidth,
                         GetWidth()
                         - getLeftButtonDimension().width
                         - getRightButtonDimension().width,
                         mScrollbarWidth);
    }

    Rectangle ScrollArea::getVerticalMarkerDimension()
    {
        if (!mVBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        int length, pos;
        Rectangle barDim = getVerticalBarDimension();

        if (GetContent() && GetContent()->GetHeight() != 0)
        {
            length = (barDim.height * getChildrenArea().height)
                / GetContent()->GetHeight();
        }
        else
        {
            length = barDim.height;
        }

        if (length < mScrollbarWidth)
        {
            length = mScrollbarWidth;
        }

        if (length > barDim.height)
        {
            length = barDim.height;
        }

        if (GetVerticalMaxScroll() != 0)
        {
            pos = ((barDim.height - length) * GetVerticalScrollAmount())
                / GetVerticalMaxScroll();
        }
        else
        {
            pos = 0;
        }

        return Rectangle(barDim.x, barDim.y + pos, mScrollbarWidth, length);
    }

    Rectangle ScrollArea::getHorizontalMarkerDimension()
    {
        if (!mHBarVisible)
        {
            return Rectangle(0, 0, 0, 0);
        }

        int length, pos;
        Rectangle barDim = getHorizontalBarDimension();

        if (GetContent() && GetContent()->GetWidth() != 0)
        {
            length = (barDim.width * getChildrenArea().width)
                / GetContent()->GetWidth();
        }
        else
        {
            length = barDim.width;
        }

        if (length < mScrollbarWidth)
        {
            length = mScrollbarWidth;
        }

        if (length > barDim.width)
        {
            length = barDim.width;
        }

        if (GetHorizontalMaxScroll() != 0)
        {
            pos = ((barDim.width - length) * GetHorizontalScrollAmount())
                / GetHorizontalMaxScroll();
        }
        else
        {
            pos = 0;
        }

        return Rectangle(barDim.x + pos, barDim.y, length, mScrollbarWidth);
    }

    void ScrollArea::ShowWidgetPart(WidgetPtr widget, Rectangle area)
    {
        if (widget != GetContent())
        {
            throw GCN_EXCEPTION("Widget not content widget");
        }

        BasicContainer::ShowWidgetPart(widget, area);

        SetHorizontalScrollAmount(GetContent()->GetFrameSize() - GetContent()->GetX());
        SetVerticalScrollAmount(GetContent()->GetFrameSize() - GetContent()->GetY());
    }

    WidgetPtr ScrollArea::GetWidgetAt(int x, int y)
    {
        if (getChildrenArea().isPointInRect(x, y))
        {
            return GetContent();
        }

        return WidgetPtr();
    }

    void ScrollArea::mouseWheelMovedUp(MouseEvent& mouseEvent)
    {
        if (mouseEvent.isConsumed())
        {
            return;
        }

        SetVerticalScrollAmount(GetVerticalScrollAmount() - getChildrenArea().height / 8);

        mouseEvent.consume();
    }

    void ScrollArea::mouseWheelMovedDown(MouseEvent& mouseEvent)
    {
        if (mouseEvent.isConsumed())
        {
            return;
        }

        SetVerticalScrollAmount(GetVerticalScrollAmount() + getChildrenArea().height / 8);

        mouseEvent.consume();
    }

    void ScrollArea::SetWidth(int width)
    {
        Widget::SetWidth(width);
        checkPolicies();
    }

    void ScrollArea::SetHeight(int height)
    {
        Widget::SetHeight(height);
        checkPolicies();
    }

    void ScrollArea::SetDimension(const Rectangle& dimension)
    {
        Widget::SetDimension(dimension);
        checkPolicies();
    }

    void ScrollArea::SetLeftButtonScrollAmount(int amount)
    {
        mLeftButtonScrollAmount = amount;
    }

    void ScrollArea::setRightButtonScrollAmount(int amount)
    {
        mRightButtonScrollAmount = amount;
    }

    void ScrollArea::SetUpButtonScrollAmount(int amount)
    {
        mUpButtonScrollAmount = amount;
    }

    void ScrollArea::SetDownButtonScrollAmount(int amount)
    {
        mDownButtonScrollAmount = amount;
    }

    int ScrollArea::GetLeftButtonScrollAmount() const
    {
        return mLeftButtonScrollAmount;
    }

    int ScrollArea::getRightButtonScrollAmount() const
    {
        return mRightButtonScrollAmount;
    }

    int ScrollArea::getUpButtonScrollAmount() const
    {
        return mUpButtonScrollAmount;
    }

    int ScrollArea::getDownButtonScrollAmount() const
    {
        return mDownButtonScrollAmount;
    }

    void ScrollArea::setOpaque(bool opaque)
    {
        mOpaque = opaque;
    }

    
    bool ScrollArea::isOpaque() const
    {
        return mOpaque;
    }
}

/*
 * Wow! This is a looooong source file.
 */
