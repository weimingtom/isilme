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

#ifndef GCN_TABBEDAREA_HPP
#define GCN_TABBEDAREA_HPP

#include <map>
#include <string>
#include <vector>

#include "guichan/actionlistener.hpp"
#include "guichan/basiccontainer.hpp"
#include "guichan/keylistener.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
    class Container;
    class Tab;

    /**
     * An implementation of a tabbed area where a user can display a widget by
     * selecting a tab.
     *
     * @since 0.8.0
     */
    class GCN_CORE_DECLSPEC TabbedArea:
        public ActionListener,
        public BasicContainer,
        public KeyListener,
        public MouseListener
    {
        friend class Tab;

    public:
        /**
         * Constructor.
         */
        TabbedArea();

        /**
         * Destructor.
         */
        virtual ~TabbedArea();

        /**
         * Sets the tabbed area to be opaque or not. If the tabbed area is
         * opaque its background will be drawn, if it's not opaque its
         * background will not be drawn. By default, a tabbed area is not
         * opaque.
         *
         * The tabbed area's background is normally only visible behind the
         * tabs, since the container holding the tab contents is opaque by
         * default.
         *
         * @param opaque True if the tabbed area should be opaque, false
         *               otherwise.
         * @see isOpaque
         */
        void SetOpaque(bool opaque);

        /**
         * Checks if the tabbed area is opaque or not.
         *
         * @return true if the tabbed area is opaque, false otherwise.
         * @see setOpaque
         */
        bool IsOpaque() const;

        /**
         * Adds a tab to the tabbed area. The newly created tab will be
         * automatically deleted by the tabbed area when it is removed.
         *
         * @param caption The caption of the tab to add.
         * @param widget The widget to view when the tab is selected.
         * @see removeTab, removeTabWithIndex
         */
        virtual void AddTab(const std::string& caption, WidgetPtr widget);

        /**
         * Adds a tab to the tabbed area. The tab will not be deleted by the
         * tabbed area when it is removed.
         *
         * @param tab The tab widget for the tab.
         * @param widget The widget to view when the tab is selected.
         * @see removeTab, removeTabWithIndex
         */
        virtual void AddTab(TabPtr tab, WidgetPtr widget);

        /**
         * Removes a tab from the tabbed area.
         *
         * @param index The index of the tab to remove.
         * @see addTab
         */
        virtual void RemoveTabWithIndex(unsigned int index);

        /**
         * Removes a tab from the tabbed area.
         *
         * @param index The tab to remove.
         * @see addTab
         */
        virtual void RemoveTab(TabPtr tab);

        /**
         * Checks if a tab given an index is selected or not.
         *
         * @param index The index of the tab to check.
         * @return True if the tab is selected, false otherwise.
         * @see setSelectedTab
         */
        virtual bool isTabSelected(unsigned int index) const;

        /**
         * Checks if a tab is selected or not.
         *
         * @param index The tab to check.
         * @return True if the tab is selected, false otherwise.
         * @see setSelectedTab
         */
        virtual bool IsTabSelected(TabPtr tab);

        /**
         * Sets a tab given an index to be selected.
         *
         * @param index The index of the tab to be selected.
         * @see isTabSelected, getSelectedTab
         */
        virtual void SetSelectedTab(unsigned int index);

        /**
         * Sets a tab to be selected or not.
         *
         * @param index The tab to be selected.
         * @see isTabSelected, getSelectedTab
         */
        virtual void SetSelectedTab(TabPtr tab);

        /**
         * Gets the index of the selected tab.
         *
         * @return The undex of the selected tab.
         *         If no tab is selected -1 will be returned.
         * @see isTabSelected, setSelectedTab
         */
        virtual int GetSelectedTabIndex() const;

        /**
         * Gets the selected tab.
         *
         * @return The selected tab.
         * @see isTabSelected, setSelectedTab
         */
        TabPtr GetSelectedTab();


        // Inherited from Widget

        virtual void Draw(GraphicsPtr graphics);

        virtual void Logic();

        void SetWidth(int width);

        void SetHeight(int height);

        void SetSize(int width, int height);

        void SetDimension(const Rectangle& dimension);


        // Inherited from ActionListener

        void action(const ActionEvent& actionEvent);


        // Inherited from DeathListener

        virtual void death(const Event& event);


        // Inherited from KeyListener

        virtual void keyPressed(KeyEvent& keyEvent);


        // Inherited from MouseListener

        virtual void mousePressed(MouseEvent& mouseEvent);

		/// Initialise data TODO: automaitcal call in static New function
		virtual void Initialise();
    protected:
        /**
         * Adjusts the size of the tab container and the widget container.
         */
        void adjustSize();

        /**
         * Adjusts the positions of the tabs.
         */
        void adjustTabPositions();

        /**
         * Holds the selected tab.
         */
        TabPtr mSelectedTab;

        /**
         * Holds the container for the tabs.
         */
        ContainerPtr mTabContainer;

        /**
         * Holds the container for the widgets.
         */
        ContainerPtr mWidgetContainer;

        /**
         * A map between a tab and a widget to display when the
         * tab is selected.
         */
        std::vector<std::pair<TabPtr, WidgetPtr> > mTabs;

        /**
         * True if the tabbed area is opaque, false otherwise.
         */
        bool mOpaque;
    };
}

#endif // end GCN_TABBEDAREA_HPP
