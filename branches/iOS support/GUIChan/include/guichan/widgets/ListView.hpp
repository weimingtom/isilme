#ifndef GCN_LISTVIEW_HPP
#define GCN_LISTVIEW_HPP

#include <string>

#include "guichan/basiccontainer.hpp"
#include "guichan/focuslistener.hpp"
#include "guichan/graphics.hpp"
#include "guichan/keylistener.hpp"
#include "guichan/mouseevent.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/platform.hpp"
#include "guichan/widget.hpp"
#include "guichan/widgets/scrollarea.hpp"

namespace gcn
{
    class GCN_CORE_DECLSPEC ListView : public ScrollArea
    {
    public:
		static ListViewPtr Create();
        /**
         * Constructor.
         */
        ListView();

		/// Destructor.
		virtual ~ListView();

		/// Adds child widget.
		///
		/// @param	child	The WidgetPtr to add.
		void AddItem(WidgetPtr child);

		void RemoveItem(WidgetPtr child);

		virtual void Init();

		WidgetPtr	GetItem(int i) const;

		int GetSize() const;
	private:
		StackPtr mItemsStack;
    };

}

#endif
