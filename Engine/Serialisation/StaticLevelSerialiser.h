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
#ifndef ISILME_SERIALISATION_STATICLEVELSERIALISER_H
#define ISILME_SERIALISATION_STATICLEVELSERIALISER_H

#include "../Definitions.h"
#include "LevelSerialiser.h"

namespace serialisation
{
	/// Serialiser for static level data.
	class ISILME_API StaticLevelSerialiser : public LevelSerialiser
	{
	public:
		StaticLevelSerialiser();
		virtual ~StaticLevelSerialiser();

		/// Serialise layer.
		///
		/// @param	layer	The layer.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseLayer(LayerPtr layer);

		/// Serialise entity.
		///
		/// @param	entity	The entity.
		///
		/// @return	null if it fails, else.
		TiXmlElement* SerialiseEntity(EntityPtr entity);

		/// Serialise.
		///
		/// @param	level	The level.
		///
		/// @return	null if it fails, else.
		TiXmlElement* Serialise(LevelPtr level);

		/// Serialise and write to file
		///
		/// @param	level   	The level.
		/// @param	fileName	Filename of the file.
		virtual void Serialise(LevelPtr level, std::string fileName);
	};
};

#endif