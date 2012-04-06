//  Copyright (C) 2010-2012 Alexander Alimov
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#ifndef ISILME_GUI_HGELABEL_H
#define ISILME_GUI_HGELABEL_H

#include "Definitions.h"
#include <GUIChan/gui.hpp>
#include <hgefont.h>

namespace gcn
{
class HGELabel: public Widget
{
public:
    HGELabel(std::string fontfile)
    {
		mFont = new hgeFont(fontfile.c_str());
	}

	~HGELabel()
	{
	}

	void setCaption(std::string caption)
	{
		mCaption = caption;
	}

	void setTextColor(gcn::Color color)
	{
		DWORD c = 256 * 256 * 256 * color.r + 256 * 256 * color.g + 256 * color.b + color.a;
		
		mFont->SetColor(c);
	}

	void setTextScale(float scale)
	{
		mFont->SetScale(scale);
	}

	std::string getCaption()
	{
		return mCaption;
	}

    virtual void Draw(Graphics* g)
    {
		mFont->Render(GetX(), GetY(), HGETEXT_LEFT, mCaption.c_str());
    }
    virtual void Logic()
	{
	}
private:
   hgeFont* mFont;
   std::string mCaption;
};
};

#endif