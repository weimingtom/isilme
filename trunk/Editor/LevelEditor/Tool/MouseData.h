#pragma once

namespace LevelEditor 
{
	namespace Tool
	{
		public enum MouseKey
		{
			NoButton = 0,
			LeftButton = 1,
			MiddleButton = 2,
			RightButton = 4
		};
	public ref class MouseData
	{
	public:
		int x;
		int y;
		MouseKey button;
	};
	}
}