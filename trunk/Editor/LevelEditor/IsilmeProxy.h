// IsilmeProxy.h

#pragma once

using namespace System;

namespace LevelEditor 
{
	ref class IsilmeHost;
	namespace Proxy
	{
		ref class ModuleProxy;
	}

	/// @class Isilme 
	/// Singleton class to control the engine from .NET code
	public ref class Isilme
	{
	public:
		/// Gets an instance of engine
		static property Isilme^ Instance
		{
			Isilme^ get();
		}

		/// Gets module
		static property Proxy::ModuleProxy^ Module
		{
			Proxy::ModuleProxy^ get();
		}

		/// Event about loading game data
		event System::EventHandler^ Loaded;

		/// Starts or resumes rendering thread
		void StartEngineThread();

		/// Stops rendering thread
		void StopEngineThread();
	internal:
		/// Raises Loaded event
		void RaiseLoaded();

		/// Host window
		IsilmeHost^ mHostWindow;
	private:
		Isilme();
		/// Engine instance
		static Isilme^ mInstance;

		/// Thread with render and update functions
		System::Threading::Thread^ mEngineThread;

		/// Update function with access to UI
		System::Threading::ThreadStart^ mUpdateStart;

		/// Routine for engine draw and update
		void EngineRoutine();

		/// Calls draw and update
		void CallUpdate();

		/// Syncronisation for engine thread
		Object^ mLock;

		/// 
		bool mWorking;
	};
}
