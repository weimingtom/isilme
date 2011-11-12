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

		/// ���������� ��� ������� ���� - ������� ������
		virtual void OnMouseDown(LayerPtr layer, float x, float y, int button);

		/// ���������� ��� ���������� ���� - ��������� ������ �� ������, ��� ������� ���������
		virtual void OnMouseUp(LayerPtr layer, float x, float y, int button);

		/// ������������� ��������� ������
		virtual void OnMouseMove(LayerPtr layer, float x, float y, int button);

		/// ������������� ��� ��������
		void SetEntityTypeID(std::string id);
	private:
		// ��������� ��� ��������
		std::string mEntityTypeID;
	};
};

#endif