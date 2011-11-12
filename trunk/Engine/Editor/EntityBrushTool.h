#ifndef EDITOR_ENTITYBRUSHTOOL_H
#define EDTIOR_ENTITYBRUSHTOOL_H

#include "EditorDefinitions.h"
#include "Tool.h"

namespace editor
{
	class IsilmeExport EntityBrushTool
	{
	public:
		EntityBrushTool();
		virtual ~EntityBrushTool();

		/// Вызывается при нажатии мыши - создаем объект
		virtual void OnMouseDown(LayerPtr layer, float x, float y, int button);

		/// Вызывается при отпускании мыши - размещаем объект на уровне, или удаляем временный
		virtual void OnMouseUp(LayerPtr layer, float x, float y, int button);

		/// Перетаскиваем созданный объект
		virtual void OnMouseMove(LayerPtr layer, float x, float y, int button);

		/// Устанавливает тип сущности
		void SetEntityTypeID(std::string id);
	private:
		// Выбранный тип сущности
		std::string mEntityTypeID;
	};
};

#endif