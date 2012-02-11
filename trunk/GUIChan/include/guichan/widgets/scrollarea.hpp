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

#ifndef GCN_SCROLLAREA_HPP
#define GCN_SCROLLAREA_HPP

#include <string>

#include "guichan/basiccontainer.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
    /**
     * Implementation if a scrollable area used to view widgets larger than the scroll area.
     * A scroll area can be customized to always show scroll bars or to show them only when
     * necessary.
     */
    class GCN_CORE_DECLSPEC ScrollArea:
        public BasicContainer,
        public MouseListener
    {
    public:

        /**
         * Scrollpolicies for the horizontal and vertical scrollbar.
         * The policies are:
         *
         * SHOW_ALWAYS - Always show the scrollbars no matter what.
         * SHOW_NEVER  - Never show the scrollbars no matter waht.
         * SHOW_AUTO   - Show the scrollbars only when needed. That is if the
         *               content grows larger then the ScrollArea.
         */
        enum ScrollPolicy
        {
            SHOW_ALWAYS = 0,
            SHOW_NEVER,
            SHOW_AUTO
        };

        /**
         * Constructor.
         */
        ScrollArea();

        /**
         * Constructor.
         *
         * @param content The content of the scroll area.
         */
        ScrollArea(WidgetPtr content);

        /**
         * Constructor.
         *
         * @param content The content of the scroll area.
         * @param hPolicy The policy for the horizontal scrollbar. See enum with
         *                policies.
         * @param vPolicy The policy for the vertical scrollbar. See enum with
         *                policies.
         */
        ScrollArea(WidgetPtr content, 
                   ScrollPolicy hPolicy, 
                   ScrollPolicy vPolicy);

        /**
         * Destructor.
         */
        virtual ~ScrollArea();

        /**
         * Sets the content.
         *
         * @param widget The content of the scroll area.
         */
		void SetContent(WidgetPtr widget);

        /**
         * Gets the content.
         *
         * @return The content of the scroll area.
         */
		WidgetPtr GetContent();

        /**
         * Sets the horizontal scrollbar policy. See enum with policies.
         *
         * @param hPolicy The policy for the horizontal scrollbar.
         * @see getHorizontalScrollPolicy
         */
        void SetHorizontalScrollPolicy(ScrollPolicy hPolicy);

        /**
         * Gets the horizontal scrollbar policy. See enum with policies.
         *
         * @return The policy for the horizontal scrollbar policy.
         * @see setHorizontalScrollPolicy, setScrollPolicy
         */
        ScrollPolicy GetHorizontalScrollPolicy() const;

        /**
         * Sets the vertical scrollbar policy. See enum with policies.
         *
         * @param vPolicy The policy for the vertical scrollbar.
         * @see getVerticalScrollPolicy
         */
        void SetVerticalScrollPolicy(ScrollPolicy vPolicy);

        /**
         * Gets the vertical scrollbar policy. See enum with policies.
         *
         * @return The policy for the vertical scrollbar.
         * @see setVerticalScrollPolicy, setScrollPolicy
         */
        ScrollPolicy GetVerticalScrollPolicy() const;

        /**
         * Sets the horizontal and vertical scrollbar policy.
         *
         * @param hPolicy The policy for the horizontal scrollbar.
         * @param vPolicy The policy for the vertical scrollbar.
         * @see getVerticalScrollPolicy, getHorizontalScrollPolicy
         */
        void SetScrollPolicy(ScrollPolicy hPolicy, ScrollPolicy vPolicy);

        /**
         * Sets the amount to scroll vertically.
         *
         * @param vScroll The amount to scroll.
         * @see getVerticalScrollAmount
         */
        void SetVerticalScrollAmount(int vScroll);

        /**
         * Gets the amount that is scrolled vertically.
         *
         * @return The scroll amount on vertical scroll.
         * @see setVerticalScrollAmount, setScrollAmount
         */
        int GetVerticalScrollAmount() const;

        /**
         * Sets the amount to scroll horizontally.
         *
         * @param hScroll The amount to scroll.
         * @see getHorizontalScrollAmount
         */
        void SetHorizontalScrollAmount(int hScroll);

        /**
         * Gets the amount that is scrolled horizontally.
         *
         * @return The scroll amount on horizontal scroll.
         * @see setHorizontalScrollAmount, setScrollAmount
         */
        int GetHorizontalScrollAmount() const;

        /**
         * Sets the amount to scroll horizontally and vertically.
         *
         * @param hScroll The amount to scroll on horizontal scroll.
         * @param vScroll The amount to scroll on vertical scroll.
         * @see getHorizontalScrollAmount, getVerticalScrollAmount
         */
        void SetScrollAmount(int hScroll, int vScroll);

        /**
         * Gets the maximum amount of horizontal scroll.
         *
         * @return The horizontal max scroll.
         */
        int GetHorizontalMaxScroll();

        /**
         * Gets the maximum amount of vertical scroll.
         *
         * @return The vertical max scroll.
         */
        int GetVerticalMaxScroll();

        /**
         * Sets the width of the scroll bars.
         *
         * @param width The width of the scroll bars.
         * @see getScrollbarWidth
         */
        void SetScrollbarWidth(int width);

        /**
         * Gets the width of the scroll bars.
         *
         * @return the width of the ScrollBar.
         * @see setScrollbarWidth
         */
        int GetScrollbarWidth() const;

        /**
         * Sets the amount to scroll in pixels when the left scroll button is
         * pushed.
         *
         * @param amount The amount to scroll in pixels. 
         * @see getLeftButtonScrollAmount
         */
        void SetLeftButtonScrollAmount(int amount);

        /**
         * Sets the amount to scroll in pixels when the right scroll button is
         * pushed.
         *
         * @param amount The amount to scroll in pixels.
         * @see getRightButtonScrollAmount
         */
        void setRightButtonScrollAmount(int amount);

        /**
         * Sets the amount to scroll in pixels when the up scroll button is
         * pushed.
         *
         * @param amount The amount to scroll in pixels.
         * @see getUpButtonScrollAmount
         */
        void SetUpButtonScrollAmount(int amount);

        /**
         * Sets the amount to scroll in pixels when the down scroll button is
         * pushed.
         *
         * @param amount The amount to scroll in pixels.
         * @see getDownButtonScrollAmount
         */
        void SetDownButtonScrollAmount(int amount);

        /**
         * Gets the amount to scroll in pixels when the left scroll button is
         * pushed.
         *
         * @return The amount to scroll in pixels.
         * @see setLeftButtonScrollAmount
         */
        int GetLeftButtonScrollAmount() const;

        /**
         * Gets the amount to scroll in pixels when the right scroll button is
         * pushed.
         *
         * @return The amount to scroll in pixels.
         * @see setRightButtonScrollAmount
         */
        int getRightButtonScrollAmount() const;

        /**
         * Gets the amount to scroll in pixels when the up scroll button is
         * pushed.
         *
         * @return The amount to scroll in pixels.
         * @see setUpButtonScrollAmount
         */
        int getUpButtonScrollAmount() const;

        /**
         * Gets the amount to scroll in pixels when the down scroll button is
         * pushed.
         *
         * @return The amount to scroll in pixels.
         * @see setDownButtonScrollAmount
         */
        int getDownButtonScrollAmount() const;

        /**
         * Sets the scroll area to be opaque, that is sets the scoll area
         * to display its background.
         *
         * @param opaque True if the scoll area should be opaque, false otherwise.
         */
        void setOpaque(bool opaque);

        /**
         * Checks if the scroll area is opaque, that is if the scroll area
         * displays its background.
         *
         * @return True if the scroll area is opaque, false otherwise.
         */
        bool isOpaque() const;
        
        
        // Inherited from BasicContainer

        virtual void ShowWidgetPart(WidgetPtr widget, Rectangle area);

        virtual Rectangle getChildrenArea();

        virtual WidgetPtr GetWidgetAt(int x, int y);


        // Inherited from Widget

        virtual void Draw(GraphicsPtr graphics);

        virtual void Logic();

        void SetWidth(int width);

        void SetHeight(int height);

        void SetDimension(const Rectangle& dimension);


        // Inherited from MouseListener

        virtual void mousePressed(MouseEvent& mouseEvent);

        virtual void mouseReleased(MouseEvent& mouseEvent);

        virtual void mouseDragged(MouseEvent& mouseEvent);

        virtual void mouseWheelMovedUp(MouseEvent& mouseEvent);

        virtual void mouseWheelMovedDown(MouseEvent& mouseEvent);

    protected:
        /**
         * Draws the background of the scroll area, that is
         * the area behind the content.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawBackground(GraphicsPtr graphics);

        /**
         * Draws the up button.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawUpButton(GraphicsPtr graphics);

        /**
         * Draws the down button.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawDownButton(GraphicsPtr graphics);

        /**
         * Draws the left button.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawLeftButton(GraphicsPtr graphics);

        /**
         * Draws the right button.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawRightButton(GraphicsPtr graphics);

        /**
         * Draws the vertical scroll bar.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawVBar(GraphicsPtr graphics);

        /**
         * Draws the horizontal scroll bar.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawHBar(GraphicsPtr graphics);

        /**
         * Draws the vertical marker.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawVMarker(GraphicsPtr graphics);

        /**
         * Draws the horizontal marker.
         *
         * @param graphics a Graphics object to draw with.
         */
        virtual void drawHMarker(GraphicsPtr graphics);

        /**
         * Checks the policies for the scroll bars.
         */
        virtual void checkPolicies();

        /**
         * Gets the up button dimension.
         *
         * @return the dimension of the up button.
         */
        Rectangle getUpButtonDimension();

        /**
         * Gets the down button dimension.
         *
         * @return the dimension of the down button.
         */
        Rectangle getDownButtonDimension();

        /**
         * Gets the left button dimension.
         *
         * @return the dimension of the left button.
         */
        Rectangle getLeftButtonDimension();

        /**
         * Gets the right button dimension.
         *
         * @return the dimension of the right button.
         */
        Rectangle getRightButtonDimension();

        /**
         * Gets the vertical scrollbar dimension.
         *
         * @return the dimension of the vertical scrollbar.
         */
        Rectangle getVerticalBarDimension();

        /**
         * Gets the horizontal scrollbar dimension.
         *
         * @return the dimension of the horizontal scrollbar.
         */
        Rectangle getHorizontalBarDimension();

        /**
         * Gets the vertical marker dimension.
         *
         * @return the dimension of the vertical marker.
         */
        Rectangle getVerticalMarkerDimension();

        /**
         * Gets the horizontal marker dimension.
         *
         * @return the dimension of the horizontal marker.
         */
        Rectangle getHorizontalMarkerDimension();
        
        /**
         * Holds the vertical scroll amount.
         */
        int mVScroll;

        /**
         * Holds the horizontal scroll amount.
         */
        int mHScroll;

        /**
         * Holds the width of the scroll bars.
         */
        int mScrollbarWidth;

        /**
         * Holds the horizontal scroll bar policy.
         */
        ScrollPolicy mHPolicy;

        /**
         * Holds the vertical scroll bar policy.
         */
        ScrollPolicy mVPolicy;

        /**
         * True if the vertical scroll bar is visible, false otherwise.
         */
        bool mVBarVisible;

        /**
         * True if the horizontal scroll bar is visible, false otherwise.
         */
        bool mHBarVisible;

        /**
         * True if the up button is pressed, false otherwise.
         */
        bool mUpButtonPressed;

        /**
         * True if the down button is pressed, false otherwise.
         */
        bool mDownButtonPressed;

        /**
         * True if the left button is pressed, false otherwise.
         */
        bool mLeftButtonPressed;

        /**
         * True if the right button is pressed, false otherwise.
         */
        bool mRightButtonPressed;

        /**
         * Holds the up button scroll amount.
         */
        int mUpButtonScrollAmount;

        /**
         * Holds the down button scroll amount.
         */
        int mDownButtonScrollAmount;

        /**
         * Holds the left button scroll amount.
         */
        int mLeftButtonScrollAmount;

        /**
         * Holds the right button scroll amount.
         */
        int mRightButtonScrollAmount;

        /**
         * True if the vertical marked is dragged.
         */
        bool mIsVerticalMarkerDragged;

        /**
         * True if the horizontal marked is dragged.
         */
        bool mIsHorizontalMarkerDragged;

        /**
         * Holds the horizontal markers drag offset.
         */
        int mHorizontalMarkerDragOffset;

        /**
         * Holds the vertical markers drag offset.
         */
        int mVerticalMarkerDragOffset;

        /**
         * True if the scroll area should be opaque (that is
         * display its background), false otherwise.
         */
        bool mOpaque;
    };
}

#endif // end GCN_SCROLLAREA_HPP
