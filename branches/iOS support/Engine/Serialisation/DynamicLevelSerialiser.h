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
#ifndef ISILME_CORE_SERIALISATION_DYNAMICLEVELSERIALISER_H
#define ISILME_CORE_SERIALISATION_DYNAMICLEVELSERIALISER_H

#include "Definitions.h"
#include "LevelSerialiser.h"

namespace serialisation
{
	/// Dynamic level serialiser.
	/// Writes dynamic data into file
	class ISILME_API DynamicLevelSerialiser : public LevelSerialiser
	{
	public:
		DynamicLevelSerialiser();
		virtual ~DynamicLevelSerialiser();

		void Serialise(LevelPtr level, std::string fileName);

		TiXmlElement* SerialiseWorld();

		TiXmlElement* Serialise(LevelPtr level);

		/// Serialise body.
		///
		/// @param	body	The body.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseBody(BodyPtr body);

		/// ��������� ��������
		///
		/// @param	entity	The entity.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseEntity(EntityPtr entity);

		/// ��������� ����
		///
		/// @param	layer	The layer.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseLayer(LayerPtr layer);
	private:
	};
};

#endif