#ifndef GCN_LISTBOXITEM_HPP
#define GCN_LISTBOXITEM_HPP

#include <list>

#include "guichan/keylistener.hpp"
#include "guichan/listmodel.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/platform.hpp"
#include "guichan/widget.hpp"

namespace gcn
{
	class GCN_CORE_DECLSPEC ListBoxItem : 
		public Widget
	{
	public:
		ListBoxItem();
		virtual ~ListBoxItem();

		virtual void	draw(Graphics* graphics);

		virtual void	logic();
	};

	typedef std::list<ListBoxItem*> ItemsList;
};

#endif