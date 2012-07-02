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

#ifndef GCN_FOCUSHANDLER_HPP
#define GCN_FOCUSHANDLER_HPP

#include <vector>

#include "guichan/event.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
    class Widget;

    /**
     * Handles focus for widgets in a Gui. Each Gui has at least one
     * focus handler. 
     
     * You will probably not use the focus handler directly as Widget 
     * has functions that automatically uses the active focus handler.
     *
     * @see Widget::isFocus, Widget::isModalFocused, 
     *      Widget::isModalMouseInputFocused, Widget::requestFocus,
     *      Widget::requestModalFocus, Widget::requestModalMouseInputFocus,
     *      Widget::releaseModalFocus, Widget::relaseModalMouseInputFocus, 
     *      Widget::setFocusable, Widget::isFocusable, FocusListener
     *
     * @since 0.1.0
     */
    class GCN_CORE_DECLSPEC FocusHandler
    {
    public:

        /**
         * Constructor.
         */
        FocusHandler();

        /**
         * Destructor.
         */
        virtual ~FocusHandler() { };

        /**
         * Requests focus for a widget. Focus will only be granted to a widget
         * if it's focusable and if no other widget has modal focus.
         * If a widget receives focus a focus event will be sent to the 
         * focus listeners of the widget.
         *
         * @param widget The widget to request focus for.
         * @see isFocused, Widget::requestFocus
         */
        virtual void RequestFocus(WidgetPtr widget);

        /**
         * Requests modal focus for a widget. Focus will only be granted
         * to a widget if it's focusable and if no other widget has modal 
         * focus.
         *
         * @param widget The widget to request modal focus for.
         * @throws Exception when another widget already has modal focus.
         * @see releaseModalFocus, Widget::requestModalFocus
         */
        virtual void RequestModalFocus(WidgetPtr widget);

        /**
         * Requests modal mouse input focus for a widget. Focus will only 
         * be granted to a widget if it's focusable and if no other widget 
         * has modal mouse input focus.
         *
         * Modal mouse input focus means no other widget then the widget with 
         * modal mouse input focus will receive mouse input. The widget with 
         * modal mouse input focus will also receive mouse input no matter what 
         * the mouse input is or where the mouse input occurs.
         *
         * @param widget The widget to focus for modal mouse input focus.
         * @throws Exception when another widget already has modal mouse input 
         *         focus.
         * @see releaseModalMouseInputFocus, Widget::requestModalMouseInputFocus
         */
        virtual void RequestModalMouseInputFocus(WidgetPtr widget);

        /**
         * Releases modal focus if the widget has modal focus.
         * If the widget doesn't have modal focus no relase will occur.
         *
         * @param widget The widget to release modal focus for.
         * @see reuqestModalFocus, Widget::releaseModalFocus
         */
        virtual void ReleaseModalFocus(WidgetPtr widget);

        /**
         * Releases modal mouse input focus if the widget has modal mouse input
         * focus. If the widget doesn't have modal mouse input focus no relase 
         * will occur.
         *
         * @param widget the widget to release modal mouse input focus for.
         * @see requestModalMouseInputFocus, Widget::releaseModalMouseInputFocus
         */
        virtual void ReleaseModalMouseInputFocus(WidgetPtr widget);

        /**
         * Checks if a widget is focused.
         *
         * @param widget The widget to check.
         * @return True if the widget is focused, false otherwise.
         * @see Widget::isFocused
         */
        virtual bool IsFocused(const WidgetPtr widget) const;

        /**
         * Gets the widget with focus.
         *
         * @return The widget with focus. NULL if no widget has focus.
         */
        virtual WidgetPtr GetFocused() const;

        /**
         * Gets the widget with modal focus.
         *
         * @return The widget with modal focus. NULL if no widget has
         *         modal focus.
         */
        virtual WidgetPtr GetModalFocused() const;

        /**
         * Gets the widget with modal mouse input focus.
         *
         * @return The widget with modal mouse input focus. NULL if
         *         no widget has modal mouse input focus.
         */
        virtual WidgetPtr GetModalMouseInputFocused() const;

        /**
         * Focuses the next widget added to a conainer. 
         * If no widget has focus the first widget gets focus. The order 
         * in which the widgets are focused is determined by the order
         * they were added to a container.
         *
         * @see focusPrevious
         */
        virtual void FocusNext();

        /**
         * Focuses the previous widget added to a contaienr. 
         * If no widget has focus the first widget gets focus. The order 
         * in which the widgets are focused is determined by the order
         * they were added to a container.
         *
         * @see focusNext
         */
        virtual void FocusPrevious();

        /**
         * Adds a widget to by handles by the focus handler.
         *
         * @param widget The widget to add.
         * @see remove
         */
        virtual void Add(WidgetPtr widget);

        /**
         * Removes a widget from the focus handler.
         *
         * @param widget The widget to remove.
         * @see add
         */
        virtual void Remove(WidgetPtr widget);

        /**
         * Focuses nothing. A focus event will also be sent to the 
         * focused widget's focus listeners if a widget has focus.
         */
        virtual void FocusNone();

        /**
         * Focuses the next widget which allows tabbing in unless 
         * the current focused Widget disallows tabbing out.
         * 
         * @see tabPrevious
         */
        virtual void TabNext();

        /**
         * Focuses the previous widget which allows tabbing in unless 
         * current focused widget disallows tabbing out.
         *
         * @see tabNext
         */
        virtual void TabPrevious();

        /**
         * Gets the widget being dragged. Used by the Gui class to 
         * keep track of the dragged widget.
         * 
         * @return the widget being dragged.
         * @see setDraggedWidget
         */
        virtual WidgetPtr GetDraggedWidget();

        /**
         * Sets the widget being dragged. Used by the Gui class to 
         * keep track of the dragged widget.
         * 
         * @param draggedWidget The widget being dragged.
         * @see getDraggedWidget
         */
        virtual void SetDraggedWidget(WidgetPtr draggedWidget);

        /**
         * Gets the last widget with the mouse. Used by the Gui class 
         * to keep track the last widget with the mouse.
         * 
         * @return The last widget with the mouse.
         * @see setLastWidgetWithMouse
         */ 
        virtual WidgetPtr GetLastWidgetWithMouse();

        /**
         * Sets the last widget with the mouse. Used by the Gui class 
         * to keep track the last widget with the mouse.
         *
         * @param lastWidgetWithMouse The last widget with the mouse.
         * @see getLastWidgetWithMouse
         */
        virtual void SetLastWidgetWithMouse(WidgetPtr lastWidgetWithMouse);

        /**
         * Gets the last widget with modal focus.
         * 
         * @return The last widget with modal focus.
         * @see setLastWidgetWithModalFocus
         */
        virtual WidgetPtr GetLastWidgetWithModalFocus();

        /**
         * Sets the last widget with modal focus.
         * 
         * @param lastWidgetWithModalFocus The last widget with modal focus.
         * @see getLastWidgetWithModalFocus
         */
        virtual void setLastWidgetWithModalFocus(WidgetPtr lastWidgetWithModalFocus);

        /**
         * Gets the last widget with modal mouse input focus.
         *
         * @return The last widget with modal mouse input focus.
         * @see setLastWidgetWithModalMouseInputFocus
         */
        virtual WidgetPtr getLastWidgetWithModalMouseInputFocus();

        /**
         * Sets the last widget with modal mouse input focus.
         *
         * @param lastMouseWithModalMouseInputFocus The last widget with 
         *                                          modal mouse input focus.
         * @see getLastWidgetWithModalMouseInputFocus
         */
        virtual void SetLastWidgetWithModalMouseInputFocus(WidgetPtr lastWidgetWithModalMouseInputFocus);

        /**
         * Gets the last widget pressed. Used by the Gui class to keep track
         * of pressed widgets.
         *
         * @return The last widget pressed. 
         * @see setLastWidgetPressed
         */
        virtual WidgetPtr GetLastWidgetPressed();

        /**
         * Sets the last widget pressed. Used by the Gui class to keep track
         * of pressed widgets.
         *
         * @param lastWidgetPressed The last widget pressed.
         * @see getLastWidgetPressed
         */
        virtual void SetLastWidgetPressed(WidgetPtr lastWidgetPressed);

    protected:
        /**
         * Distributes a focus lost event.
         *
         * @param focusEvent the event to distribute.
         * @since 0.7.0
         */
        virtual void distributeFocusLostEvent(const Event& focusEvent);

        /**
         * Distributes a focus gained event.
         *
         * @param focusEvent the event to distribute.
         * @since 0.7.0
         */
        virtual void distributeFocusGainedEvent(const Event& focusEvent);

        /**
         * Typedef.
         */
        typedef std::vector<WidgetPtr> WidgetVector;

        /**
         * Typedef.
         */
        typedef WidgetVector::iterator WidgetIterator;

        /**
         * Holds the widgets currently being handled by the
         * focus handler.
         */
        WidgetVector mWidgets;

        /**
         * Holds the focused widget. NULL if no widget has focus.
         */
        WidgetPtr mFocusedWidget;

        /**
         * Holds the modal focused widget. NULL if no widget has
         * modal focused.
         */
        WidgetPtr mModalFocusedWidget;

        /**
         * Holds the modal mouse input focused widget. NULL if no widget 
         * is being dragged.
         */
        WidgetPtr mModalMouseInputFocusedWidget;

        /** 
         * Holds the dragged widget. NULL if no widget is
         * being dragged.
         */
        WidgetPtr mDraggedWidget;

        /**
         * Holds the last widget with the mouse.
         */
        WidgetPtr mLastWidgetWithMouse;

        /**
         * Holds the last widget with modal focus.
         */
        WidgetPtr mLastWidgetWithModalFocus;

        /**
         * Holds the last widget with modal mouse input focus.
         */
        WidgetPtr mLastWidgetWithModalMouseInputFocus;

        /**
         * Holds the last widget pressed.
         */
        WidgetPtr mLastWidgetPressed;
    };
}

#endif // end GCN_FOCUSHANDLER_HPP
