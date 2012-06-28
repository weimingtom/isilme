//  Copyright (C) 2010-2012 VSTU
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
#include "Joints.h"

// JointDefinition

JointDefinition::JointDefinition()
{
	def = 0;
}

JointDefinition::~JointDefinition()
{
}

void	JointDefinition::Parse(TiXmlElement* jointElement)
{
	std::string type = jointElement->Attribute("Type");
	entityA = jointElement->Attribute("EntityA");
	entityB = jointElement->Attribute("EntityB");

	Vector2	pointA(0.0f, 0.0f);
	Vector2 pointB(0.0f, 0.0f);

	sscanf(jointElement->Attribute("PointA"), "%f, %f", &pointA.x, &pointA.y);
	sscanf(jointElement->Attribute("PointB"), "%f, %f", &pointB.x, &pointB.y);

	if (type == "Distance")
	{
		b2DistanceJointDef* jDef = new b2DistanceJointDef();
		def = jDef;

		// ������ ����������
		jDef->length = 1.0f;
		jointElement->QueryFloatAttribute("Length", &jDef->length);

		// ���������� ��������
		jDef->localAnchorA = pointA;
		jDef->localAnchorB = pointB;
	}
	else if (type == "Weld")
	{
		b2WeldJointDef* jDef = new b2WeldJointDef();
		def = jDef;

		// ����
		jDef->referenceAngle = 0.0f;
		jointElement->QueryFloatAttribute("Angle", &jDef->referenceAngle);

		// ���������� ��������
		jDef->localAnchorA = pointA;
		jDef->localAnchorB = pointB;
	}
	else if (type == "Revolute")
	{
	}

	// ������������ �� ��������� ����
	int isCollide = 0;
	jointElement->QueryIntAttribute("Collide", &isCollide);
	def->collideConnected = isCollide != 0;

	// ����
	def->bodyA = 0;
	def->bodyB = 0;
}
//
//// Joint
//
//Joint::Joint(JointDefinition* def)
//{
//	Entity* entityA = FactoryManager::GetSingleton()->GetEntity(def->entityA);
//	Entity* entityB = FactoryManager::GetSingleton()->GetEntity(def->entityB);
//
//	def->def->bodyA = ((Box2DBody*)(entityA->GetBody()))->GetBox2DBody();
//	def->def->bodyB = ((Box2DBody*)(entityB->GetBody()))->GetBox2DBody();
//
//	mJoint = def->world->CreateJoint(def->def);
//	mWorld = def->world;
//}
//
//Joint::~Joint()
//{
//	mWorld->DestroyJoint(mJoint);
//	mJoint = 0;
//}
//
//Entity* Joint::GetEntityA()
//{
//	return (Entity*)(mJoint->GetBodyA()->GetUserData());
//}
//
//Vector2 Joint::GetPointA()
//{
//	return mJoint->GetAnchorA();
//}
//
//Vector2 Joint::GetPointB()
//{
//	return mJoint->GetAnchorB();
//}
//
//Entity* Joint::GetEntityB()
//{
//	return (Entity*)(mJoint->GetBodyB()->GetUserData());
//}