#include "IsilmePCH.h"
#include "Tool.h"

namespace editor
{
	Tool::Tool()
	{
	}

	Tool::~Tool()
	{
	}

	void Tool::OnMouseDown(LayerPtr layer, float x, float y, int button)
	{
	}

	void Tool::OnMouseMove(LayerPtr layer, float x, float y, int button)
	{
	}

	void Tool::OnMouseUp(LayerPtr layer, float x, float y, int button)
	{
	}

	CommandManagerPtr Tool::GetCommandManager()
	{
		return mCommandManager;
	}

	void Tool::SetCommandManager(CommandManagerPtr value)
	{
		mCommandManager = value;
	}
};