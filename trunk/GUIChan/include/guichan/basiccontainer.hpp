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

#ifndef GCN_BASICCONTAINER_HPP
#define GCN_BASICCONTAINER_HPP

#include <list>

#include "guichan/deathlistener.hpp"
#include "guichan/platform.hpp"
#include "guichan/widget.hpp"

namespace gcn
{
    /**
     * A base class for containers. The class implements the most
     * common things for a container. If you are implementing a 
     * container, consider inheriting from this class.
     *
     * @see Container
     * @since 0.6.0
     */
    class GCN_CORE_DECLSPEC BasicContainer : public Widget, public DeathListener
    {
    public:
        /**
         * Destructor
         */
        virtual ~BasicContainer();

        /**
         * Shows a certain part of a widget in the basic container.
         * Used when widgets want a specific part to be visible in
         * its parent. An example is a TextArea that wants a specific
         * part of its text to be visible when a TextArea is a child
         * of a ScrollArea.
         *
         * @param widget The widget whom wants a specific part of
         *               itself to be visible.
         * @param rectangle The rectangle to be visible.
         */
		virtual void ShowWidgetPart(WidgetPtr widget, Rectangle area);

        
        // Inherited from Widget

		virtual void MoveToTop(WidgetPtr widget);

		virtual void MoveToBottom(WidgetPtr widget);

        virtual Rectangle getChildrenArea();

        virtual void FocusNext();

        virtual void focusPrevious();

        virtual void Logic();

		virtual void _setFocusHandler(FocusHandlerPtr focusHandler);

		void SetInternalFocusHandler(FocusHandlerPtr focusHandler);

		virtual WidgetPtr GetWidgetAt(int x, int y);


        // Inherited from DeathListener

        virtual void death(const Event& event);

    protected:
        /**
         * Adds a widget to the basic container.
         *
         * @param widget The widget to add.
         * @see remove, clear
         */
		void Add(WidgetPtr widget);

        /**
         * Removes a widget from the basic container.
         *
         * @param widget The widget to remove.
         * @see add, clear
         */
		virtual void Remove(WidgetPtr widget);

        /**
         * Clears the basic container from all widgets.
         *
         * @see remove, clear
         */
        virtual void Clear();
        
        /**
         * Draws the children widgets of the basic container.
         *
         * @param graphics A graphics object to draw with.
         */
		virtual void DrawChildren(GraphicsPtr graphics);

        /**
         * Calls logic for the children widgets of the basic
         * container.
         */
        virtual void logicChildren();

        /**
         * Finds a widget given an id. This function can be useful
         * when implementing a GUI generator for Guichan, such as
         * the ability to create a Guichan GUI from an XML file.
         *
         * @param id The id to find a widget by.
         * @return The widget with the corrosponding id, 
                   NULL of no widget is found.
         */
		virtual WidgetPtr FindWidgetById(const std::string& id);

        /**
         * Typedef.
         */
        typedef std::list<WidgetPtr> WidgetList;

         /**
         * Typedef.
         */
        typedef WidgetList::iterator WidgetListIterator;

        /**
         * Typedef.
         */
        typedef WidgetList::reverse_iterator WidgetListReverseIterator;

        /**
         * Holds all widgets of the basic container.
         */
        WidgetList mWidgets;
    };
}

#endif // end GCN_BASICCONTAINER_HPP
