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
//	���� ���� � ����� Isilme SDK.
//
//		Isilme SDK - ��������� ���������: �� ������ ������������������ �� �/���
//		�������� �� �� �������� ������� ����������� ������������ �������� GNU � ��� ����,
//		� ����� ��� ���� ������������ ������ ���������� ������������ �����������;
//		���� ������ 3 ��������, ���� (�� ������ ������) ����� ����� �������
//		������.
//
//		Isilme SDK ���������������� � �������, ��� ��� ����� ��������,
//		�� ���� ������ ��������; ���� ��� ������� �������� ��������� ����
//		��� ����������� ��� ������������ �����. ��������� ��. � ������� �����������
//		������������ �������� GNU.
//
//		�� ������ ���� �������� ����� ������� ����������� ������������ �������� GNU
//		������ � ���� ����������. ���� ��� �� ���, ��.
//		<http://www.gnu.org/licenses/>.
#ifndef ISILME_GUI_PROGRESSBAR_H
#define ISILME_GUI_PROGRESSBAR_H

#include "Definitions.h"
#include <GUIChan/gui.hpp>

namespace gcn
{
class ProgressBar: public Widget
{
public:
    ProgressBar()
    :mProgress(0)
    {}

    void setProgress(float progress)
    {
         mProgress = progress < 0.0f ? 0.0f : progress;
         mProgress = progress > 100.f ? 100.0f : progress;
    }    
    virtual void Draw(GraphicsPtr g)
    {
         g->setColor(getSelectionColor());
         g->fillRectangle(gcn::Rectangle(0, 0, GetWidth() * mProgress, GetHeight()));
         g->setColor(getForegroundColor());
         g->drawRectangle(gcn::Rectangle(0, 0, GetWidth(), GetHeight()));

    }
    virtual void Logic()
	{
	}
private:
   float mProgress;
};

typedef boost::shared_ptr<ProgressBar> ProgressBarPtr;
};

#endif