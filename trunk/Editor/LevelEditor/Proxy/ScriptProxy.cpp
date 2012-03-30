#include "Stdafx.h"
#include "ScriptProxy.h"
#include "../ResourceHelper.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LevelEditor
{
	namespace Proxy
	{

		ScriptProxy::ScriptProxy( ScriptPtr script )
		{
			mScript = script;
			mSource = ResourceHelper::CharToString(script->GetSource().c_str());
		}

		ScriptProxy::~ScriptProxy()
		{

		}

		String^ ScriptProxy::Source::get()
		{
			return mSource;
		}

		void ScriptProxy::Source::set(String^ value)
		{
			mSource = value;
			mScript->Set(ResourceHelper::StringToChar(value), mScript->GetParamsString());
		}
	}
}