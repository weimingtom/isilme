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
#include "Core/Behaviour.h"

#include "Perception.h"
#include "Attribute.h"
#include "AIBehaviour.h"

Perception::Perception()
{

}

Perception::~Perception()
{

}

void Perception::SetID( std::string id )
{
	mID = id;
}

std::string Perception::GetID() const
{
	return mID;
}

std::string AttributePerception::GetAttributeID() const
{
	return mAttribute;
}

float AttributePerception::GetValue( BehaviourPtr behaviour ) const 
{
	
	AttributePtr attr = boost::shared_dynamic_cast<AIBehaviour>(behaviour)->GetAttribute(mAttribute);
	return attr->GetValue();
}

AttributePerception::AttributePerception( std::string attribute )
{
	mAttribute = attribute;
}

void AttributePerception::SetAttributeID( std::string attr )
{
	mAttribute = attr;
}

luabind::object ScriptedPerception::GetLuaFunction() const
{
	return mLuaFunction;
}

void ScriptedPerception::SetLuaFunction( luabind::object f )
{
	mLuaFunction = f;
}

float ScriptedPerception::GetValue( BehaviourPtr behaviour ) const 
{
	return 0.0f;
}
