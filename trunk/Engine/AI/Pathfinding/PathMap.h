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
#ifndef ISILME_AI_PATHFINDING_PATHMAP_H
#define ISILME_AI_PATHFINDING_PATHMAP_H

#include "../AITypes.h"
#include "Types.h"

namespace pathfinding
{
	class PathMap
	{
	public:
		PathMap() {};
		virtual ~PathMap() {};

		/// Initializes map by level static geometry
		virtual void Init(LevelPtr level) = 0;
	private:
	};

	class RegularRectGrid : public PathMap
	{
	public:
		RegularRectGrid();
		virtual ~RegularRectGrid();

		virtual void Init(LevelPtr level) override;
	};

	class IrregularRectGrid : public PathMap
	{
	public:
		IrregularRectGrid();
		virtual ~IrregularRectGrid();

		virtual void Init(LevelPtr level) override;
	private:
		Graph mGraph;
	};

	class TriangleGrid : public PathMap
	{
	public:
		TriangleGrid();
		virtual ~TriangleGrid();

		virtual void Init(LevelPtr level) override;
	};
}
#endif