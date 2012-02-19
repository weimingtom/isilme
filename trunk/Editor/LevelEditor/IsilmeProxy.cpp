// This is the main DLL file.

#include "stdafx.h"

#include "IsilmeProxy.h"


void LevelEditor::Isilme::RaiseLoaded()
{
	Loaded(this, nullptr);
}

LevelEditor::Isilme::Isilme()
{
}

LevelEditor::Isilme^ LevelEditor::Isilme::Instance::get()
{
	if (mInstance == nullptr)
		mInstance = gcnew Isilme();

	return mInstance;
};