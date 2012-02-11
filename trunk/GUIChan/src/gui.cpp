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

#include "guichan/gui.hpp"

#include "guichan/basiccontainer.hpp"
#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/graphics.hpp"
#include "guichan/input.hpp"
#include "guichan/keyinput.hpp"
#include "guichan/keylistener.hpp"
#include "guichan/mouseinput.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/widget.hpp"

namespace gcn
{
    Gui::Gui()
            :mInput(NULL),
             mTabbing(true),
             mShiftPressed(false),
             mMetaPressed(false),
             mControlPressed(false),
             mAltPressed(false),
             mLastMousePressButton(0),
             mLastMousePressTimeStamp(0),
             mLastMouseX(0),
             mLastMouseY(0),
             mClickCount(1),
             mLastMouseDragButton(0)
    {
        mFocusHandler = FocusHandlerPtr(new FocusHandler());
    }

    Gui::~Gui()
    {
        if (Widget::widgetExists(mTop))
        {
            SetTop(WidgetPtr());
        }
    }

	void Gui::SetTop( WidgetPtr top )
	{
        if (mTop != NULL)
        {
            mTop->_setFocusHandler(FocusHandlerPtr());
        }
        if (top != NULL)
        {
            top->_setFocusHandler(mFocusHandler);
        }

        mTop = top;
    }

	gcn::WidgetPtr Gui::GetTop() const
	{
        return mTop;
    }

	void Gui::SetGraphics( GraphicsPtr graphics )
	{
        mGraphics = graphics;
    }

	GraphicsPtr Gui::GetGraphics() const
	{
        return mGraphics;
    }

    void Gui::SetInput(Input* input)
    {
        mInput = input;
    }

    Input* Gui::getInput() const
    {
        return mInput;
    }

    void Gui::Logic()
    {
        if (mTop == NULL)
        {
            throw GCN_EXCEPTION("No top widget set");
        }

        handleModalFocus();
        handleModalMouseInputFocus();

        if (mInput != NULL)
        {
            mInput->_pollInput();

            handleKeyInput();
            handleMouseInput();
 
        } // end if

        mTop->Logic();
    }

    void Gui::Draw()
    {
        if (mTop == NULL)
        {
            throw GCN_EXCEPTION("No top widget set");
        }
        if (mGraphics == NULL)
        {
            throw GCN_EXCEPTION("No graphics set");
        }

        if (!mTop->IsVisible())
        {
            return;
        }

        mGraphics->_beginDraw();

        // If top has a frame,
        // draw it before drawing top
        if (mTop->GetFrameSize() > 0)
        {
            Rectangle rec = mTop->GetDimension();
            rec.x -= mTop->GetFrameSize();
            rec.y -= mTop->GetFrameSize();
            rec.width += 2 * mTop->GetFrameSize();
            rec.height += 2 * mTop->GetFrameSize();
            mGraphics->pushClipArea(rec);
            mTop->DrawFrame(mGraphics);
            mGraphics->popClipArea();
        }

        mGraphics->pushClipArea(mTop->GetDimension());
        mTop->Draw(mGraphics);
        mGraphics->popClipArea();

        mGraphics->_endDraw();
    }

    void Gui::FocusNone()
    {
        mFocusHandler->FocusNone();
    }

    void Gui::SetTabbingEnabled(bool tabbing)
    {
        mTabbing = tabbing;
    }

    bool Gui::isTabbingEnabled()
    {
        return mTabbing;
    }

    void Gui::addGlobalKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.push_back(keyListener);
    }

    void Gui::removeGlobalKeyListener(KeyListener* keyListener)
    {
        mKeyListeners.remove(keyListener);
    }

    void Gui::handleMouseInput()
    {
        while (!mInput->isMouseQueueEmpty())
         {
             MouseInput mouseInput = mInput->dequeueMouseInput();

             // Save the current mouse state. It will be needed if modal focus
             // changes or modal mouse input focus changes.
             mLastMouseX = mouseInput.getX();
             mLastMouseY = mouseInput.getY();

             switch (mouseInput.getType())
             {
               case MouseInput::PRESSED:
                   handleMousePressed(mouseInput);
                   break;
               case MouseInput::RELEASED:
                   handleMouseReleased(mouseInput);
                   break;
               case MouseInput::MOVED:
                   handleMouseMoved(mouseInput);
                   break;
               case MouseInput::WHEEL_MOVED_DOWN:
                   handleMouseWheelMovedDown(mouseInput);
                   break;
               case MouseInput::WHEEL_MOVED_UP:
                   handleMouseWheelMovedUp(mouseInput);
                   break;
               default:
                   throw GCN_EXCEPTION("Unknown mouse input type.");
                   break;
             }
         }
    }

    void Gui::handleKeyInput()
    {
        while (!mInput->isKeyQueueEmpty())
        {
            KeyInput keyInput = mInput->dequeueKeyInput();

            // Save modifiers state
            mShiftPressed = keyInput.isShiftPressed();
            mMetaPressed = keyInput.isMetaPressed();
            mControlPressed = keyInput.isControlPressed();
            mAltPressed = keyInput.isAltPressed();

            KeyEvent keyEventToGlobalKeyListeners(WidgetPtr(),
                                                  mShiftPressed,
                                                  mControlPressed,
                                                  mAltPressed,
                                                  mMetaPressed,
                                                  keyInput.getType(),
                                                  keyInput.isNumericPad(),
                                                  keyInput.getKey());

            distributeKeyEventToGlobalKeyListeners(keyEventToGlobalKeyListeners);

            // If a global key listener consumes the event it will not be
            // sent further to the source of the event.
            if (keyEventToGlobalKeyListeners.isConsumed())
            {
                continue;
            }

            bool keyEventConsumed = false;
            
            // Send key inputs to the focused widgets
            if (mFocusHandler->GetFocused() != NULL)
            {
                KeyEvent keyEvent(GetKeyEventSource(),
                                  mShiftPressed,
                                  mControlPressed,
                                  mAltPressed,
                                  mMetaPressed,
                                  keyInput.getType(),
                                  keyInput.isNumericPad(),
                                  keyInput.getKey());
                

                if (!mFocusHandler->GetFocused()->IsFocusable())
                {
                    mFocusHandler->FocusNone();
                }
                else
                {                    
                    distributeKeyEvent(keyEvent);                    
                }

                keyEventConsumed = keyEvent.isConsumed();
            }

            // If the key event hasn't been consumed and
            // tabbing is enable check for tab press and
            // change focus.
            if (!keyEventConsumed
                && mTabbing
                && keyInput.getKey().getValue() == Key::TAB
                && keyInput.getType() == KeyInput::PRESSED)
            {
                if (keyInput.isShiftPressed())
                {
                    mFocusHandler->TabPrevious();
                }
                else
                {
                    mFocusHandler->TabNext();
                }
            }                           
                
        } // end while
    }

    void Gui::handleMouseMoved(const MouseInput& mouseInput)
    {
        // Check if the mouse leaves the application window.
        if (!mWidgetWithMouseQueue.empty()
            && (mouseInput.getX() < 0
                || mouseInput.getY() < 0
                || !mTop->GetDimension().isPointInRect(mouseInput.getX(), mouseInput.getY()))
            )
        {
            // Distribute an event to all widgets in the "widget with mouse" queue.
            while (!mWidgetWithMouseQueue.empty())
            {
                WidgetPtr widget = mWidgetWithMouseQueue.front();

                if (Widget::widgetExists(widget))
                {
                    distributeMouseEvent(widget,
                                         MouseEvent::EXITED,
                                         mouseInput.getButton(),
                                         mouseInput.getX(),
                                         mouseInput.getY(),
                                         true,
                                         true);
                }

                mWidgetWithMouseQueue.pop_front();
            }

            return;
        }

        // Check if there is a need to send mouse exited events by
        // traversing the "widget with mouse" queue.
        bool widgetWithMouseQueueCheckDone = mWidgetWithMouseQueue.empty();
        while (!widgetWithMouseQueueCheckDone)
        {
            unsigned int iterations = 0;
            std::deque<WidgetPtr>::iterator iter;
            for (iter = mWidgetWithMouseQueue.begin();
                 iter != mWidgetWithMouseQueue.end();
                 iter++)
            {
                WidgetPtr widget = *iter;
                            
                // If a widget in the "widget with mouse queue" doesn't
                // exists anymore it should be removed from the queue.
                if (!Widget::widgetExists(widget))
                {
                    mWidgetWithMouseQueue.erase(iter);
                    break;
                }
                else
                {
                    int x, y;
                    widget->getAbsolutePosition(x, y);

                    if (x > mouseInput.getX()
                        || y > mouseInput.getY()
                        || x + widget->GetWidth() <= mouseInput.getX()
                        || y + widget->GetHeight() <= mouseInput.getY()
                        || !widget->IsVisible())
                    {
                        distributeMouseEvent(widget,
                                             MouseEvent::EXITED,
                                             mouseInput.getButton(),
                                             mouseInput.getX(),
                                             mouseInput.getY(),
                                             true,
                                             true);                                       
                        mClickCount = 1;
                        mLastMousePressTimeStamp = 0;
                        mWidgetWithMouseQueue.erase(iter);
                        break;
                    }
                }

                iterations++;
            }

            widgetWithMouseQueueCheckDone = iterations == mWidgetWithMouseQueue.size();
        }

        // Check all widgets below the mouse to see if they are
        // present in the "widget with mouse" queue. If a widget
        // is not then it should be added and an entered event should
        // be sent to it.
        WidgetPtr parent = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());
        WidgetPtr widget = parent;

        // If a widget has modal mouse input focus then it will
        // always be returned from getMouseEventSource, but we only wan't to send
        // mouse entered events if the mouse has actually entered the widget with
        // modal mouse input focus, hence we need to check if that's the case. If
        // it's not we should simply ignore to send any mouse entered events.
        if (mFocusHandler->GetModalMouseInputFocused()
            && widget == mFocusHandler->GetModalMouseInputFocused()
            && Widget::widgetExists(widget))
        {
            int x, y;
            widget->getAbsolutePosition(x, y);

            if (x > mouseInput.getX()
                || y > mouseInput.getY()
                || x + widget->GetWidth() <= mouseInput.getX() 
                || y + widget->GetHeight() <= mouseInput.getY())
            {
                parent.reset();
            }
        }

        while (parent)
        {
            parent = widget->GetParent();

            // Check if the widget is present in the "widget with mouse" queue.
            bool widgetIsPresentInQueue = false;
            std::deque<WidgetPtr>::iterator iter;
            for (iter = mWidgetWithMouseQueue.begin();
                 iter != mWidgetWithMouseQueue.end();
                 iter++)
            {
                if (*iter == widget)
                {
                    widgetIsPresentInQueue = true;
                    break;
                }
            }

            // Widget is not present, send an entered event and add
            // it to the "widget with mouse" queue.
            if (!widgetIsPresentInQueue
                && Widget::widgetExists(widget))
            {
                distributeMouseEvent(widget,
                                     MouseEvent::ENTERED,
                                     mouseInput.getButton(),
                                     mouseInput.getX(),
                                     mouseInput.getY(),
                                     true,
                                     true);
                mWidgetWithMouseQueue.push_front(widget);
            }

            WidgetPtr swap = widget;
            widget = parent;
            parent = (WidgetPtr)swap->GetParent();
        }

        if (mFocusHandler->GetDraggedWidget())
        {
            distributeMouseEvent(mFocusHandler->GetDraggedWidget(),
                                 MouseEvent::DRAGGED,
                                 mLastMouseDragButton,
                                 mouseInput.getX(),
                                 mouseInput.getY());
        }
        else
        {
            WidgetPtr sourceWidget = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());
            distributeMouseEvent(sourceWidget,
                                 MouseEvent::MOVED,
                                 mouseInput.getButton(),
                                 mouseInput.getX(),
                                 mouseInput.getY());
        }
    }

    void Gui::handleMousePressed(const MouseInput& mouseInput)
    {
        WidgetPtr sourceWidget = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());

        if (mFocusHandler->GetDraggedWidget())
        {
            sourceWidget = mFocusHandler->GetDraggedWidget();
        }

        int sourceWidgetX, sourceWidgetY;
        sourceWidget->getAbsolutePosition(sourceWidgetX, sourceWidgetY);

        if ((mFocusHandler->GetModalFocused() != NULL
            && sourceWidget->isModalFocused())
            || mFocusHandler->GetModalFocused() == NULL)
        {
            sourceWidget->requestFocus();
        }

        if (mouseInput.getTimeStamp() - mLastMousePressTimeStamp < 250
            && mLastMousePressButton == mouseInput.getButton())
        {
            mClickCount++;
        }
        else
        {
            mClickCount = 1;
        }

        distributeMouseEvent(sourceWidget,
                             MouseEvent::PRESSED,
                             mouseInput.getButton(),
                             mouseInput.getX(),
                             mouseInput.getY());

        mFocusHandler->SetLastWidgetPressed(sourceWidget);

        mFocusHandler->SetDraggedWidget(sourceWidget);
        mLastMouseDragButton = mouseInput.getButton();

        mLastMousePressButton = mouseInput.getButton();
        mLastMousePressTimeStamp = mouseInput.getTimeStamp();
    }

    void Gui::handleMouseWheelMovedDown(const MouseInput& mouseInput)
    {
        WidgetPtr sourceWidget = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());

        if (mFocusHandler->GetDraggedWidget() != NULL)
        {
            sourceWidget = mFocusHandler->GetDraggedWidget();
        }

        int sourceWidgetX, sourceWidgetY;
        sourceWidget->getAbsolutePosition(sourceWidgetX, sourceWidgetY);

        distributeMouseEvent(sourceWidget,
                             MouseEvent::WHEEL_MOVED_DOWN,
                             mouseInput.getButton(),
                             mouseInput.getX(),
                             mouseInput.getY());
    }

    void Gui::handleMouseWheelMovedUp(const MouseInput& mouseInput)
    {
        WidgetPtr sourceWidget = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());

        if (mFocusHandler->GetDraggedWidget() != NULL)
        {
            sourceWidget = mFocusHandler->GetDraggedWidget();
        }

        int sourceWidgetX, sourceWidgetY;
        sourceWidget->getAbsolutePosition(sourceWidgetX, sourceWidgetY);

        distributeMouseEvent(sourceWidget,
                             MouseEvent::WHEEL_MOVED_UP,
                             mouseInput.getButton(),
                             mouseInput.getX(),
                             mouseInput.getY());
    }

    void Gui::handleMouseReleased(const MouseInput& mouseInput)
    {
        WidgetPtr sourceWidget = GetMouseEventSource(mouseInput.getX(), mouseInput.getY());

        if (mFocusHandler->GetDraggedWidget())
        {
            if (sourceWidget != mFocusHandler->GetLastWidgetPressed())
            {
                mFocusHandler->SetLastWidgetPressed(WidgetPtr());
            }
            
            sourceWidget = mFocusHandler->GetDraggedWidget();
        }

        int sourceWidgetX, sourceWidgetY;
        sourceWidget->getAbsolutePosition(sourceWidgetX, sourceWidgetY);
        
        distributeMouseEvent(sourceWidget,
                             MouseEvent::RELEASED,
                             mouseInput.getButton(),
                             mouseInput.getX(),
                             mouseInput.getY());

        if (mouseInput.getButton() == mLastMousePressButton            
            && mFocusHandler->GetLastWidgetPressed() == sourceWidget)
        {
            distributeMouseEvent(sourceWidget,
                                 MouseEvent::CLICKED,
                                 mouseInput.getButton(),
                                 mouseInput.getX(),
                                 mouseInput.getY());
            
            mFocusHandler->SetLastWidgetPressed(WidgetPtr());
        }
        else
        {
            mLastMousePressButton = 0;
            mClickCount = 0;
        }

        if (mFocusHandler->GetDraggedWidget())
        {
            mFocusHandler->SetDraggedWidget(WidgetPtr());
        }
    }

    WidgetPtr Gui::GetWidgetAt(int x, int y)
    {
        // If the widget's parent has no child then we have found the widget..
        WidgetPtr parent = mTop;
        WidgetPtr child = mTop;

        while (child != NULL)
        {
            WidgetPtr swap = child;
            int parentX, parentY;
            parent->getAbsolutePosition(parentX, parentY);
            child = parent->GetWidgetAt(x - parentX, y - parentY);
            parent = swap;
        }

        return parent;
    }

    WidgetPtr Gui::GetMouseEventSource(int x, int y)
    {
        WidgetPtr widget = GetWidgetAt(x, y);

        if (mFocusHandler->GetModalMouseInputFocused()
            && !widget->isModalMouseInputFocused())
        {
            return mFocusHandler->GetModalMouseInputFocused();
        }

        return widget;
    }

    WidgetPtr Gui::GetKeyEventSource()
    {
        WidgetPtr widget = mFocusHandler->GetFocused();

        while (widget->_getInternalFocusHandler()
               && widget->_getInternalFocusHandler()->GetFocused())
        {
            widget = widget->_getInternalFocusHandler()->GetFocused();
        }

        return widget;
    }

    void Gui::distributeMouseEvent(WidgetPtr source,
                                   int type,
                                   int button,
                                   int x,
                                   int y,
                                   bool force,
                                   bool toSourceOnly)
    {
        WidgetPtr parent = source;
        WidgetPtr widget = source;

        if (mFocusHandler->GetModalFocused()
            && !widget->isModalFocused()
            && !force)
        {
            return;
        }

        if (mFocusHandler->GetModalMouseInputFocused()
            && !widget->isModalMouseInputFocused()
            && !force)
        {
            return;
        }

        MouseEvent mouseEvent(source,
                              mShiftPressed,
                              mControlPressed,
                              mAltPressed,
                              mMetaPressed,
                              type,
                              button,
                              x,
                              y,
                              mClickCount);

        while (parent != NULL)
        {
            // If the widget has been removed due to input
            // cancel the distribution.
            if (!Widget::widgetExists(widget))
            {
                break;
            }

            parent = (WidgetPtr)widget->GetParent();

            if (widget->IsEnabled() || force)
            {
                int widgetX, widgetY;
                widget->getAbsolutePosition(widgetX, widgetY);

                mouseEvent.mX = x - widgetX;
                mouseEvent.mY = y - widgetY;
                                      
                std::list<MouseListener*> mouseListeners = widget->_getMouseListeners();

                // Send the event to all mouse listeners of the widget.
                for (std::list<MouseListener*>::iterator it = mouseListeners.begin();
                     it != mouseListeners.end();
                     ++it)
                {
                    switch (mouseEvent.getType())
                    {
                      case MouseEvent::ENTERED:
                          (*it)->MouseEntered(mouseEvent);
                          break;
                      case MouseEvent::EXITED:
                          (*it)->MouseExited(mouseEvent);
                          break;
                      case MouseEvent::MOVED:
                          (*it)->mouseMoved(mouseEvent);
                          break;
                      case MouseEvent::PRESSED:
                          (*it)->mousePressed(mouseEvent);
                          break;
                      case MouseEvent::RELEASED:
                          (*it)->mouseReleased(mouseEvent);
                          break;
                      case MouseEvent::WHEEL_MOVED_UP:
                          (*it)->mouseWheelMovedUp(mouseEvent);
                          break;
                      case MouseEvent::WHEEL_MOVED_DOWN:
                          (*it)->mouseWheelMovedDown(mouseEvent);
                          break;
                      case MouseEvent::DRAGGED:
                          (*it)->mouseDragged(mouseEvent);
                          break;
                      case MouseEvent::CLICKED:
                          (*it)->mouseClicked(mouseEvent);
                          break;
                      default:
                          throw GCN_EXCEPTION("Unknown mouse event type.");
                    }                    
                }
                
                if (toSourceOnly)
                {
                    break;
                }

            }

            WidgetPtr swap = widget;
            widget = parent;
            parent = (WidgetPtr)swap->GetParent();

            // If a non modal focused widget has been reach
            // and we have modal focus cancel the distribution.
            if (mFocusHandler->GetModalFocused() != NULL
                && !widget->isModalFocused())
            {
                break;
            }

            // If a non modal mouse input focused widget has been reach
            // and we have modal mouse input focus cancel the distribution.
            if (mFocusHandler->GetModalMouseInputFocused() != NULL
                && !widget->isModalMouseInputFocused())
            {
                break;
            }
        }
    }

    void Gui::distributeKeyEvent(KeyEvent& keyEvent)
    {
        WidgetPtr parent = keyEvent.GetSource();
        WidgetPtr widget = keyEvent.GetSource();

        if (mFocusHandler->GetModalFocused() != NULL
            && !widget->isModalFocused())
        {
            return;
        }

        if (mFocusHandler->GetModalMouseInputFocused() != NULL
            && !widget->isModalMouseInputFocused())
        {
            return;
        }

        while (parent != NULL)
        {
            // If the widget has been removed due to input
            // cancel the distribution.
            if (!Widget::widgetExists(widget))
            {
                break;
            }

            parent = widget->GetParent();

            if (widget->IsEnabled())
            {
                std::list<KeyListener*> keyListeners = widget->_getKeyListeners();
            
                // Send the event to all key listeners of the source widget.
                for (std::list<KeyListener*>::iterator it = keyListeners.begin();
                     it != keyListeners.end();
                     ++it)
                {
                    switch (keyEvent.getType())
                    {
                      case KeyEvent::PRESSED:
                          (*it)->keyPressed(keyEvent);
                          break;
                      case KeyEvent::RELEASED:
                          (*it)->keyReleased(keyEvent);
                          break;
                      default:
                          throw GCN_EXCEPTION("Unknown key event type.");
                    }                
                }
            }

            WidgetPtr swap = widget;
            widget = parent;
            parent = (WidgetPtr)swap->GetParent();

            // If a non modal focused widget has been reach
            // and we have modal focus cancel the distribution.
            if (mFocusHandler->GetModalFocused() != NULL
                && !widget->isModalFocused())
            {
                break;
            }
        }
    }

    void Gui::distributeKeyEventToGlobalKeyListeners(KeyEvent& keyEvent)
    {
        KeyListenerListIterator it;

        for (it = mKeyListeners.begin(); it != mKeyListeners.end(); it++)
        {
            switch (keyEvent.getType())
            {
              case KeyEvent::PRESSED:
                  (*it)->keyPressed(keyEvent);
                  break;
              case KeyEvent::RELEASED:
                  (*it)->keyReleased(keyEvent);
                  break;
              default:
                  throw GCN_EXCEPTION("Unknown key event type.");
            }

            if (keyEvent.isConsumed())
            {
                break;
            }
        }
    }

    void Gui::handleModalMouseInputFocus()
    {
        // Check if modal mouse input focus has been gained by a widget.
        if ((mFocusHandler->getLastWidgetWithModalMouseInputFocus() 
                != mFocusHandler->GetModalMouseInputFocused())
             && (!mFocusHandler->getLastWidgetWithModalMouseInputFocus()))
        {
            handleModalFocusGained();
            mFocusHandler->SetLastWidgetWithModalMouseInputFocus(mFocusHandler->GetModalMouseInputFocused());
        }
        // Check if modal mouse input focus has been released.
        else if ((mFocusHandler->getLastWidgetWithModalMouseInputFocus()
                    != mFocusHandler->GetModalMouseInputFocused())
                    && (mFocusHandler->getLastWidgetWithModalMouseInputFocus()))
        {
            handleModalFocusReleased();
            mFocusHandler->SetLastWidgetWithModalMouseInputFocus(WidgetPtr());
        }
    }

     void Gui::handleModalFocus()
    {
        // Check if modal focus has been gained by a widget.
        if ((mFocusHandler->GetLastWidgetWithModalFocus() 
                != mFocusHandler->GetModalFocused())
             && (!mFocusHandler->GetLastWidgetWithModalFocus()))
        {
            handleModalFocusGained();
            mFocusHandler->setLastWidgetWithModalFocus(mFocusHandler->GetModalFocused());
        }
        // Check if modal focus has been released.
        else if ((mFocusHandler->GetLastWidgetWithModalFocus()
                    != mFocusHandler->GetModalFocused())
                    && (mFocusHandler->GetLastWidgetWithModalFocus()))
        {
            handleModalFocusReleased();
            mFocusHandler->setLastWidgetWithModalFocus(WidgetPtr());
        }
    }

    void Gui::handleModalFocusGained()
    {
         // Distribute an event to all widgets in the "widget with mouse" queue.
        while (!mWidgetWithMouseQueue.empty())
        {
            WidgetPtr widget = mWidgetWithMouseQueue.front();

            if (Widget::widgetExists(widget))
            {
                distributeMouseEvent(widget,
                                     MouseEvent::EXITED,
                                     mLastMousePressButton,
                                     mLastMouseX,
                                     mLastMouseY,
                                     true,
                                     true);
            }

            mWidgetWithMouseQueue.pop_front();
        }

        mFocusHandler->SetLastWidgetWithModalMouseInputFocus(mFocusHandler->GetModalMouseInputFocused());
    }

    void Gui::handleModalFocusReleased()
    {
         // Check all widgets below the mouse to see if they are
        // present in the "widget with mouse" queue. If a widget
        // is not then it should be added and an entered event should
        // be sent to it.
        WidgetPtr widget = GetMouseEventSource(mLastMouseX, mLastMouseY);
        WidgetPtr parent = widget;

        while (parent != NULL)
        {
            parent = widget->GetParent();

            // Check if the widget is present in the "widget with mouse" queue.
            bool widgetIsPresentInQueue = false;
            std::deque<WidgetPtr>::iterator iter;
            for (iter = mWidgetWithMouseQueue.begin();
                 iter != mWidgetWithMouseQueue.end();
                 iter++)
            {
                if (*iter == widget)
                {
                    widgetIsPresentInQueue = true;
                    break;
                }
            }

            // Widget is not present, send an entered event and add
            // it to the "widget with mouse" queue.
            if (!widgetIsPresentInQueue
                && Widget::widgetExists(widget))
            {
                distributeMouseEvent(widget,
                                     MouseEvent::ENTERED,
                                     mLastMousePressButton,
                                     mLastMouseX,
                                     mLastMouseY,
                                     false,
                                     true);
                mWidgetWithMouseQueue.push_front(widget);
            }

            WidgetPtr swap = widget;
            widget = parent;
            parent = swap->GetParent();
        }
    }
}
