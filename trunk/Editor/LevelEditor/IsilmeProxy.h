// IsilmeProxy.h

#pragma once

using namespace System;

namespace LevelEditor 
{
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

		event System::EventHandler^ Loaded;
	internal:
		/// Raises Loaded event
		void RaiseLoaded();
	private:
		Isilme();
		/// Engine instance
		static Isilme^ mInstance;
	};
}
