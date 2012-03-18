#ifndef EDITOR_TOOL_H
#define EDITOR_TOOL_H

#include "../Definitions.h"
#include "EditorDefinitions.h"

namespace editor
{
/// Базовый класс инструментов
class ISILME_API Tool
{
public:
	Tool();
	virtual ~Tool();

	//// Вызывается при нажатии мыши
	virtual void OnMouseDown(LayerPtr layer, float x, float y, int button);

	/// Вызывается при отпускании мыши
	virtual void OnMouseUp(LayerPtr layer, float x, float y, int button);

	/// Вызывается при перемещении мыши
	virtual void OnMouseMove(LayerPtr layer, float x, float y, int button);

	/// Возвращает менеджер комманд
	CommandManagerPtr GetCommandManager();

	/// Устанавливает менеджер комманд
	void SetCommandManager(CommandManagerPtr value);
private:
	CommandManagerPtr mCommandManager;
};
};

#endif