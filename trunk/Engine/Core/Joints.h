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
#ifndef JOINTS_H
#define JOINTS_H

#include <tinyxml.h>
#include <string>
#include "Collisions.h"

class ISILME_API JointDefinition
{
public:
	std::string	entityA;
	std::string entityB;
	Vector2	pointA;
	Vector2 pointB;
	b2World* world;

	b2JointDef*	def;

	JointDefinition();

	virtual ~JointDefinition();

	void	Parse(TiXmlElement* jointElement);
};

typedef boost::shared_ptr<JointDefinition> JointDefPtr;
//
//class IsilmeExport Joint : public Object
//{
//public:
//	Joint(JointDefPtr def);
//
//	~Joint();
//
//	EntityPtr GetEntityA();
//
//	EntityPtr GetEntityB();
//
//	Vector2 GetPointA();
//
//	Vector2 GetPointB();
//protected:
//	b2Joint* mJoint;
//	b2World* mWorld;
//};

#endif