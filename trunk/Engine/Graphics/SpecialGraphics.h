#ifndef ISILME_GRAPHICS_SPECIAL_H
#define ISILME_GRAPHICS_SPECIAL_H

namespace graphics
{
	/// Используется для реализации графики, отражающей особенности поведения
	template<class T>
	class SpecialGraphics : public Graphics
	{
	public:
		SpecialGraphics(GraphicsDefinition* def = 0) : Graphics(def) {}

		virtual ~SpecialGraphics() {}

		T* GetBehaviour()
		{
			return dynamic_cast<T*>(GetEntity()->GetBehaviour().get());
		}
	};
};
#endif