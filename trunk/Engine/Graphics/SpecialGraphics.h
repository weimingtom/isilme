#ifndef ISILME_GRAPHICS_SPECIAL_H
#define ISILME_GRAPHICS_SPECIAL_H

namespace graphics
{
	/// ������������ ��� ���������� �������, ���������� ����������� ���������
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