// This is the main DLL file.

#include "stdafx.h"

#include "IsilmeProxy.h"
#include "IsilmeControl.h"
#include "Proxy\ModuleProxy.h"
#include "View\LevelEditorWindow.h"

using namespace System;
using namespace System::Threading;


void LevelEditor::Isilme::RaiseLoaded()
{
	Loaded(this, nullptr);
}

LevelEditor::Isilme::Isilme()
{
	mLock = gcnew Object();
}

void LevelEditor::Isilme::StartEngineThread()
{
	if (mEngineThread == nullptr)
	{
		mWorking = true;
		mEngineThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &Isilme::EngineRoutine));
		mUpdateStart = gcnew System::Threading::ThreadStart(this, &Isilme::CallUpdate);
		mEngineThread->Start();
	}
}

void LevelEditor::Isilme::StopEngineThread()
{
	Monitor::Enter(mLock);
	mWorking = false;
	Monitor::Exit(mLock);

	Thread::Sleep(1000);
	mEngineThread->Abort();
	mEngineThread = nullptr;
}

void LevelEditor::Isilme::EngineRoutine()
{
	bool w = true;
	while (w)
	{
		mHostWindow->Dispatcher->Invoke(System::Windows::Threading::DispatcherPriority::Background, mUpdateStart);
		System::Threading::Thread::Sleep(30);

		Monitor::Enter(mLock);
		w = mWorking;
		Monitor::Exit(mLock);
	}
	w = false;
	return;
}

void LevelEditor::Isilme::CallUpdate()
{
	if (View::LevelEditorWindow::Instance->IsActiveDocument)
		HGEGame::GetSingleton()->Start();
}

LevelEditor::Isilme^ LevelEditor::Isilme::Instance::get()
{
	if (mInstance == nullptr)
		mInstance = gcnew Isilme();

	return mInstance;
};

namespace LevelEditor
{
	Proxy::ModuleProxy^ Isilme::Module::get()
	{
		return Proxy::ModuleProxy::Instance;
	}
}