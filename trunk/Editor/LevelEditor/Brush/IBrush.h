#pragma  once

namespace LevelEditor
{
	namespace Brush
	{
		public interface class IBrush
		{
		public:
			virtual void OnMouseDown(int x, int y);
			virtual void OnMouseMove(int x, int y);
			virtual void OnMouseUp(int x, int y);
		};
	}
}