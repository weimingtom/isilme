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
#ifndef ISILME_CORE_PALETTE_GRAPHICSPALETTE_H
#define ISILME_CORE_PALETTE_GRAPHICSPALETTE_H

#include "Definitions.h"
//#include "Loading/GraphicsDefinition.h"
//#include "include/GraphicsFactory.h"
//#include "Loading/GraphicsDefinition.h"

class ISILME_API GraphicsPalette
{
public:
	GraphicsPalette();
	virtual ~GraphicsPalette();

	/// Registers graphics type
	void RegisterGraphicsType(std::string type, GraphicsFactoryPtr factory);

	/// Registers graphics type
	//template<typename TDefType>
	//void RegisterGraphicsType(std::string type);

	/// Creates graphics instance
	GraphicsPtr CreateGraphics(std::string id);

	/// Clears the palette
	void ClearPalette();

	/// Unregister all types
	void ClearTypes();

	/// Loads palette form file
	void Load(std::string fileName);

	/// Gets definition of type
	GraphicsDefPtr GetDefinition( std::string id );

	/// Gets factory for type
	GraphicsFactoryPtr GetFactory( std::string type );
protected:
	GraphicsDefPtr LoadDefinition(TiXmlElement* element);
private:
	typedef std::map<std::string, GraphicsFactoryPtr> GraphicsFactoryMap;
	typedef std::map<std::string, GraphicsDefPtr> GraphicsDefMap;

	/// Map type - factory
	GraphicsFactoryMap mFactories;

	/// Palette id - definition
	GraphicsDefMap mDefinitions;

};

//template<typename TDefType>
//void GraphicsPalette<TDefType>::RegisterGraphicsType( std::string type )
//{
//	//GraphicsFactoryPtr factory = GraphicsFactory<DefType>::New();
//	//RegisterGraphicsType(type, factory);
//}

#endif