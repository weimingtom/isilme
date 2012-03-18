#ifndef EDITOR_TOOL_H
#define EDITOR_TOOL_H

#include "../Definitions.h"
#include "EditorDefinitions.h"

namespace editor
{
/// ������� ����� ������������
class ISILME_API Tool
{
public:
	Tool();
	virtual ~Tool();

	//// ���������� ��� ������� ����
	virtual void OnMouseDown(LayerPtr layer, float x, float y, int button);

	/// ���������� ��� ���������� ����
	virtual void OnMouseUp(LayerPtr layer, float x, float y, int button);

	/// ���������� ��� ����������� ����
	virtual void OnMouseMove(LayerPtr layer, float x, float y, int button);

	/// ���������� �������� �������
	CommandManagerPtr GetCommandManager();

	/// ������������� �������� �������
	void SetCommandManager(CommandManagerPtr value);
private:
	CommandManagerPtr mCommandManager;
};
};

#endif