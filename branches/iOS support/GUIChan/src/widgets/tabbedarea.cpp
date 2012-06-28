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

#include "guichan/widgets/tabbedarea.hpp"

#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/font.hpp"
#include "guichan/graphics.hpp"

#include "guichan/widgets/container.hpp"
#include "guichan/widgets/tab.hpp"

#include <algorithm>

namespace gcn
{
    TabbedArea::TabbedArea()
            :
             mOpaque(false)
    {
        SetFocusable(true);
        addKeyListener(this);
        addMouseListener(this);

        mTabContainer = ContainerPtr(new Container());
        mTabContainer->SetOpaque(false);
        mWidgetContainer = ContainerPtr(new Container());
    }

    TabbedArea::~TabbedArea()
    {
        Remove(mTabContainer);
        Remove(mWidgetContainer);
    }

    void TabbedArea::AddTab(const std::string& caption, WidgetPtr widget)
    {
        TabPtr tab(new Tab());
		tab->Initialise();
        tab->SetCaption(caption);

        AddTab(tab, widget);
    }

    void TabbedArea::AddTab(TabPtr tab, WidgetPtr widget)
    {
        tab->SetTabbedArea(boost::shared_dynamic_cast<TabbedArea>(shared_from_this()));
        tab->addActionListener(this);

        mTabContainer->Add(tab);
        mTabs.push_back(std::pair<TabPtr, WidgetPtr>(tab, widget));

        if (mSelectedTab == NULL)
        {
            SetSelectedTab(tab);
        }

        adjustTabPositions();
        adjustSize();
    }

    void TabbedArea::RemoveTabWithIndex(unsigned int index)
    {
        if (index >= mTabs.size())
        {
            throw GCN_EXCEPTION("No such tab index.");
        }

        RemoveTab(mTabs[index].first);
    }

    void TabbedArea::RemoveTab(TabPtr tab)
    {
        int tabIndexToBeSelected = - 1;

        if (tab == mSelectedTab)
        {
            int index = GetSelectedTabIndex();

            if (index == (int)mTabs.size() - 1
                && mTabs.size() >= 2)
            {
                tabIndexToBeSelected = index--;
            }
            else if (index == (int)mTabs.size() - 1
                     && mTabs.size() == 1)
            {
                tabIndexToBeSelected = -1;
            }
            else
            {
                tabIndexToBeSelected = index;
            }
        }

        std::vector<std::pair<TabPtr, WidgetPtr> >::iterator iter;
        for (iter = mTabs.begin(); iter != mTabs.end(); iter++)
        {
            if (iter->first == tab)
            {
                mTabContainer->Remove(tab);
                mTabs.erase(iter);
                break;
            }
        }

        if (tabIndexToBeSelected == -1)
        {
            mSelectedTab.reset();
            mWidgetContainer->Clear();
        }
        else
        {
            SetSelectedTab(tabIndexToBeSelected);
        }

        adjustSize();
        adjustTabPositions();
    }

    bool TabbedArea::isTabSelected(unsigned int index) const
    {
        if (index >= mTabs.size())
        {
            throw GCN_EXCEPTION("No such tab index.");
        }

        return mSelectedTab == mTabs[index].first;
    }

    bool TabbedArea::IsTabSelected(TabPtr tab)
    {
        return mSelectedTab == tab;
    }

    void TabbedArea::SetSelectedTab(unsigned int index)
    {
        if (index >= mTabs.size())
        {
            throw GCN_EXCEPTION("No such tab index.");
        }

        SetSelectedTab(mTabs[index].first);
    }

    void TabbedArea::SetSelectedTab(TabPtr tab)
    {
        unsigned int i;
        for (i = 0; i < mTabs.size(); i++)
        {
            if (mTabs[i].first == mSelectedTab)
            {
                mWidgetContainer->Remove(mTabs[i].second);
            }
        }

        for (i = 0; i < mTabs.size(); i++)
        {
            if (mTabs[i].first == tab)
            {
                mSelectedTab = tab;
                mWidgetContainer->Add(mTabs[i].second);
            }
        }
    }

    int TabbedArea::GetSelectedTabIndex() const
    {
        unsigned int i;
        for (i = 0; i < mTabs.size(); i++)
        {
            if (mTabs[i].first == mSelectedTab)
            {
                return i;
            }
        }

        return -1;
    }

    TabPtr TabbedArea::GetSelectedTab()
    {
        return mSelectedTab;
    }

    void TabbedArea::SetOpaque(bool opaque)
    {
        mOpaque = opaque;
    }

    bool TabbedArea::IsOpaque() const
    {
        return mOpaque;
    }

    void TabbedArea::Draw(GraphicsPtr graphics)
    {
        const Color &faceColor = getBaseColor();
        const int alpha = getBaseColor().a;
        Color highlightColor = faceColor + 0x303030;
        highlightColor.a = alpha;
        Color shadowColor = faceColor - 0x303030;
        shadowColor.a = alpha;

        // Draw a border.
        graphics->setColor(highlightColor);
        graphics->drawLine(0,
                           mTabContainer->GetHeight(),
                           0,
                           GetHeight() - 2);
        graphics->setColor(shadowColor);
        graphics->drawLine(GetWidth() - 1,
                           mTabContainer->GetHeight() + 1,
                           GetWidth() - 1,
                           GetHeight() - 1);
        graphics->drawLine(1,
                           GetHeight() - 1,
                           GetWidth() - 1,
                           GetHeight() - 1);

        if (IsOpaque())
        {
            graphics->setColor(getBaseColor());
            graphics->fillRectangle(Rectangle(1, 1,
                                              GetWidth() - 2,
                                              GetHeight() - 2));
        }

        // Draw a line underneath the tabs.
        graphics->setColor(highlightColor);
        graphics->drawLine(1,
                           mTabContainer->GetHeight(),
                           GetWidth() - 1,
                           mTabContainer->GetHeight());

        // If a tab is selected, remove the line right underneath
        // the selected tab.
        if (mSelectedTab != NULL)
        {
            graphics->setColor(getBaseColor());
            graphics->drawLine(mSelectedTab->GetX() + 1,
                               mTabContainer->GetHeight(),
                               mSelectedTab->GetX() + mSelectedTab->GetWidth() - 2,
                               mTabContainer->GetHeight());

        }

        DrawChildren(graphics);
    }

    void TabbedArea::Logic()
    {
    }

    void TabbedArea::adjustSize()
    {
        int maxTabHeight = 0;

        for (unsigned int i = 0; i < mTabs.size(); i++)
        {
            if (mTabs[i].first->GetHeight() > maxTabHeight)
            {
                maxTabHeight = mTabs[i].first->GetHeight();
            }
        }

        mTabContainer->SetSize(GetWidth() - 2,
                               maxTabHeight);

        mWidgetContainer->SetPosition(1, maxTabHeight + 1);
        mWidgetContainer->SetSize(GetWidth() - 2,
                                  GetHeight() - maxTabHeight - 2);
    }

    void TabbedArea::adjustTabPositions()
    {
        int maxTabHeight = 0;
        unsigned int i;
        for (i = 0; i < mTabs.size(); i++)
        {
            if (mTabs[i].first->GetHeight() > maxTabHeight)
            {
                maxTabHeight = mTabs[i].first->GetHeight();
            }
        }

        int x = 0;
        for (i = 0; i < mTabs.size(); i++)
        {
            TabPtr tab = mTabs[i].first;
            tab->SetPosition(x, maxTabHeight - tab->GetHeight());
            x += tab->GetWidth();
        }
    }

    void TabbedArea::SetWidth(int width)
    {
        Widget::SetWidth(width);
        adjustSize();
    }

    void TabbedArea::SetHeight(int height)
    {
        Widget::SetHeight(height);
        adjustSize();
    }

    void TabbedArea::SetSize(int width, int height)
    {
        Widget::SetSize(width, height);
        adjustSize();
    }

    void TabbedArea::SetDimension(const Rectangle& dimension)
    {
        Widget::SetDimension(dimension);
        adjustSize();
    }

    void TabbedArea::keyPressed(KeyEvent& keyEvent)
    {
        if (keyEvent.isConsumed() || !IsFocused())
        {
            return;
        }

        if (keyEvent.getKey().getValue() == Key::LEFT)
        {
            int index = GetSelectedTabIndex();
            index--;

            if (index < 0)
            {
                return;
            }
            else
            {
                SetSelectedTab(mTabs[index].first);
            }

            keyEvent.consume();
        }
        else if (keyEvent.getKey().getValue() == Key::RIGHT)
        {
            int index = GetSelectedTabIndex();
            index++;

            if (index >= (int)mTabs.size())
            {
                return;
            }
            else
            {
                SetSelectedTab(mTabs[index].first);
            }

            keyEvent.consume();
        }
    }


    void TabbedArea::mousePressed(MouseEvent& mouseEvent)
    {
        if (mouseEvent.isConsumed())
        {
            return;
        }

        if (mouseEvent.GetButton() == MouseEvent::LEFT)
        {
            WidgetPtr widget = mTabContainer->GetWidgetAt(mouseEvent.getX(), mouseEvent.getY());
            TabPtr tab = boost::shared_dynamic_cast<Tab>(widget);

            if (tab)
            {
                SetSelectedTab(tab);
            }
        }

        // Request focus only if the source of the event
        // is not focusble. If the source of the event
        // is focused we don't want to steal the focus.
        if (!mouseEvent.GetSource()->IsFocusable())
        {
            requestFocus();
        }
    }

    void TabbedArea::death(const Event& event)
    {
        TabPtr tab = boost::shared_dynamic_cast<Tab>(event.GetSource());

        if (tab)
        {
            RemoveTab(tab);
        }
        else
        {
            BasicContainer::death(event);
        }
    }

    void TabbedArea::action(const ActionEvent& actionEvent)
    {
        WidgetPtr source = actionEvent.GetSource();
        TabPtr tab = boost::shared_dynamic_cast<Tab>(source);

        if (!tab)
        {
            throw GCN_EXCEPTION("Received an action from a widget that's not a tab!");
        }

        SetSelectedTab(tab);
    }

	void TabbedArea::Initialise()
	{
		Add(mTabContainer);
		Add(mWidgetContainer);
	}

}
