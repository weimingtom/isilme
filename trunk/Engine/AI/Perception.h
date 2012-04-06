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
#ifndef ISILME_AI_PERCEPT_H
#define ISILME_AI_PERCEPT_H

#include "AITypes.h"

/// @class Perception
/// 
class ISILME_API Perception
{
public:
	Perception();
	virtual ~Perception();

	/// Gets ID of the perception
	std::string GetID() const;

	/// Sets ID for the perception
	void SetID(std::string id);

	/// Gets value
	virtual float GetValue(BehaviourPtr behaviour) const = 0;
private:
	/// ID of the perception
	std::string mID;
};

class ISILME_API AttributePerception : public Perception
{
public:
	AttributePerception(std::string attribute);

	/// Gets attribute ID
	std::string GetAttributeID() const;

	/// Sets attribute ID
	void SetAttributeID(std::string attr);

	virtual float GetValue(BehaviourPtr behaviour) const override;
private:
	std::string mAttribute;
};

class ISILME_API ScriptedPerception : public Perception
{
public:
	/// Gets function
	luabind::object GetLuaFunction() const;

	/// Sets function
	void SetLuaFunction(luabind::object f);

	virtual float GetValue(BehaviourPtr behaviour) const override;
private:
	luabind::object mLuaFunction;
};

class ISILME_API LogicPerception : public Perception
{

};

#endif