#ifndef GCN_TYPES_H
#define GCN_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace gcn
{
	class ActionListener;
	class BasicContainer;
	typedef boost::shared_ptr<BasicContainer> BasicContainerPtr;
	typedef boost::weak_ptr<BasicContainer> BasicContainerWPtr;

	class DeathListener;
	class DefaultFont;
	typedef boost::shared_ptr<DefaultFont> DefaultFontPtr;

	class FocusHandler;
	typedef boost::shared_ptr<FocusHandler> FocusHandlerPtr;
	typedef boost::weak_ptr<FocusHandler> FocusHandlerWPtr;

	class FocusListener;

	class Font;
	typedef boost::shared_ptr<Font> FontPtr;
	typedef boost::weak_ptr<Font> FontWPtr;

	class Graphics;
	typedef boost::shared_ptr<Graphics> GraphicsPtr;
	typedef boost::weak_ptr<Graphics> GraphicsWPtr;
	
	class Input;
	class KeyInput;
	class KeyListener;
	class MouseInput;
	class MouseListener;

	class Widget;
	typedef boost::shared_ptr<Widget> WidgetPtr;
	typedef boost::weak_ptr<Widget> WidgetWPtr;

	class WidgetListener;


	// Widgets
	class Button;
	typedef boost::shared_ptr<Button> ButtonPtr;

	class Container;
	typedef boost::shared_ptr<Container> ContainerPtr;

	class Icon;
	typedef boost::shared_ptr<Icon> IconPtr;

	class Label;
	typedef boost::shared_ptr<Label> LabelPtr;

	class ListBox;
	typedef boost::shared_ptr<ListBox> ListBoxPtr;

	class ScrollArea;
	typedef boost::shared_ptr<ScrollArea> ScrollAreaPtr;

	class Tab;
	typedef boost::shared_ptr<Tab> TabPtr;

	class TabbedArea;
	typedef boost::shared_ptr<TabbedArea> TabbedAreaPtr;
	typedef boost::weak_ptr<TabbedArea> TabbedAreaWPtr;

	class TextBox;
	typedef boost::shared_ptr<TextBox> TextBoxPtr;

	class Window;
	typedef boost::shared_ptr<Window> WindowPtr;

}
#endif