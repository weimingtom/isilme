#include "Stdafx.h"
#include "ResourceHelper.h"

namespace LevelEditor
{
	System::Windows::Media::ImageSource^ ResourceHelper::GetPngSource( System::String^ filename )
	{
		System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
		System::IO::Stream^ stream = assembly->GetManifestResourceStream(filename);
		System::Windows::Media::Imaging::BitmapDecoder^ decoder = System::Windows::Media::Imaging::PngBitmapDecoder::Create(stream,System::Windows::Media::Imaging::BitmapCreateOptions::None, System::Windows::Media::Imaging::BitmapCacheOption::None);
		System::Windows::Media::Imaging::BitmapSource^ source = decoder->Frames[0];
		return source;
	}

}