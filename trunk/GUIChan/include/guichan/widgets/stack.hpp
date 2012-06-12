#ifndef GCN_STACK_HPP
#define GCN_STACK_HPP

#include <string>

#include "guichan/basiccontainer.hpp"
#include "guichan/focuslistener.hpp"
#include "guichan/graphics.hpp"
#include "guichan/keylistener.hpp"
#include "guichan/mouseevent.hpp"
#include "guichan/mouselistener.hpp"
#include "guichan/platform.hpp"
#include "guichan/widget.hpp"

namespace gcn
{
    class GCN_CORE_DECLSPEC Stack : public BasicContainer
    {
    public:
		enum Orientation
		{
			OrientationHorizontal = 0,
			OrientationVertical = 1
		};

		static StackPtr Create();
        /**
         * Constructor.
         */
        Stack();

		virtual ~Stack();

        /**
         * Sets the spacing between the border of the button and its caption.
         *
         * @param spacing The default value for spacing is 4 and can be changed 
         *                using this method.
         * @see GetSpacing
         */
        void SetSpacing(int spacing);

		/// Gets the spacing.
		///
		/// @return	The spacing.
		/// 
		/// @see SetSpacing
		int GetSpacing() const;

		/// Gets the orientation of the stack.
		///
		/// @return	The orientation.
		Orientation	GetOrientation() const;

		/// Sets an orientation.
		///
		/// @param	orientation	 the orientation.
		void SetOrientation(Orientation orientation);

		/// Adds child widget.
		///
		/// @param	child	The WidgetPtr to add.
		void AddChild(WidgetPtr child);

		/// Removes the child described by child.
		///
		/// @param	child	The child.
		void RemoveChild(WidgetPtr child);

		virtual void Draw(GraphicsPtr graphics) override;
	protected:
		/// Rebuilds layout.
		void RebuildLayout();
	private:

        /**
         * Holds the spacing between the border and the caption.
         */
        int mSpacing;

		/// @summary	The orientation.
		Orientation mOrientation;
    };

}

#endif
