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
#include "IsilmePCH.h"
#include "Camera.h"

Camera::Camera()
{
	x = 0.0f;
	y = 0.0f;
	width = 800;
	height = 600;
}
Camera::Camera(CameraDefinition* def)
{
	x = 0.0f;
	y = 0.0f;
	width = 800;
	height = 600;
}

Camera::~Camera()
{
}

void	Camera::Update(float elapsedTime)
{
	OnUpdate(elapsedTime);
}

void Camera::Apply()
{
	//mHGE->Gfx_SetTransform(0.0f ,0.0f, -x, -y, 0.0f, 1.0f, 1.0f);
}

void Camera::OnUpdate( float elapsedTime )
{

}

CameraDefinition::CameraDefinition()
{
}

CameraDefinition::~CameraDefinition()
{
}

void	CameraDefinition::Parse(TiXmlElement* def)
{
}

CameraPtr CameraDefinition::Create()
{
	return CameraPtr(new Camera(this));
}