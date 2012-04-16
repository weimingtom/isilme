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
#include "Script.h"
#include "ScriptAPI.h"

Script::Script( std::string source, std::string params /*= ""*/ )
{
	mLuaScript = ScriptAPI::MakeFunction(params, source);
}

Script::Script()
{

}

void Script::Set( std::string source, std::string params /*= ""*/ )
{

}

bool Script::IsValid() const
{
	return mLuaScript.is_valid();
}

std::string Script::GetSource() const
{
	return mSource;
}

luabind::object Script::GetLuaObject() const
{
	return mLuaScript;
}

std::string Script::GetParamsString() const
{
	StringList::const_iterator it = mParams.begin();
	std::string result = *it;
	++it;
	while (it != mParams.end())
	{
		result += ", ";
		result += *it;
		++it;
	}

	return result;
}

