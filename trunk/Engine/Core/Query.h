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
#ifndef ISILME_QUERY_RESULT_H
#define ISILME_QUERY_RESULT_H

#include "Definitions.h"



/// Query result.
class ISILME_API Query
{
public:

	/// Default constructor.
	Query();
		
	/// Destructor.
	virtual ~Query();
	
	/// Gets an entity.
	///
	/// @param	index	Zero-based index of the entity in result.
	///
	/// @return	The entity or null.
	EntityPtr GetEntity(int index);

	/// Gets the entities count.
	///
	/// @return	The entities count.
	int GetEntitiesCount();

	/// Executes this object.
	virtual bool Execute() = 0;
protected:
	/// Pushes an entity.
	///
	/// @param	entity	The entity.
	void PushEntity(EntityPtr entity);

	/// Clears this object to its blank/initial state.
	void Clear();
private:
	/// The entities
	std::vector<EntityPtr> mEntities;
};

#endif