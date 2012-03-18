#pragma once

#include "../Stdafx.h"
#include "IDataToProxyConverter.h"

using namespace System;

class EditableScriptEntry : public Entry
{
public:
	EditableScriptEntry(std::string filename);
	std::string Source;
};
typedef boost::shared_ptr<ScriptEntry> ScriptEntryPtr;

namespace serialisation
{
	class EditableScirptLoader : public EntryLoader
	{
	public:
		virtual EntryPtr LoadEntry(std::string filename) override;
	};
}

namespace LevelEditor
{
	namespace Proxy
	{
		public ref class ScriptProxy : public Common::ProxyObject
		{
		public:
			ScriptProxy(const char* text);

			property String^ Text
			{
				String^ get();
				void set(String^ value);
			}
		private:
			String^ mText;
		};

		public ref class ScriptDataToProxyConverter : public IDataToProxyConverter
		{
		public:
			virtual Common::IProxyObject^ Convert(SharedCLIPtr<Entry>* entry) override;
		};
	}
}