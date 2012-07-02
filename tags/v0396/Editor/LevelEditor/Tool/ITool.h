#pragma  once

#include "MouseData.h"

namespace LevelEditor
{
	namespace Tool
	{
		public interface class ITool
		{
		public:
			virtual void OnMouseDown(MouseData^ mouse);
			virtual void OnMouseMove(MouseData^ mouse);
			virtual void OnMouseUp(MouseData^ mouse);
		};
	}
}