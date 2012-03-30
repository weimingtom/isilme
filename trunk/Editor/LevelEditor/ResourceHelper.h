#pragma once

namespace LevelEditor
{
	public ref class ResourceHelper
	{
	public:
		static System::Windows::Media::ImageSource^ GetPngSource(System::String^ filename);

		static System::String^	CharToString(const char* value);

		static char* StringToChar(System::String^ value);
	};
}