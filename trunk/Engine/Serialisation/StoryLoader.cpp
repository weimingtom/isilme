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
#include "IsilmePCH.h"
#include "StoryLoader.h"
#include "Core/MasterFile.h"

namespace serialisation
{


	StoryLoader::StoryLoader()
	{

	}

	StoryLoader::~StoryLoader()
	{

	}

	story::StagePtr StoryLoader::LoadStage( TiXmlElement* element )
	{
		story::StagePtr stage(new story::Stage());


		return stage;
	}

	story::QuestPtr StoryLoader::LoadQuest( TiXmlElement* element )
	{
		story::QuestPtr quest(new story::Quest());

		return quest;
	}

	story::StoryPtr StoryLoader::LoadStory( TiXmlElement* element )
	{
		story::StoryPtr story(new story::Story());

		return story;
	}

	story::StoryPtr StoryLoader::LoadStory( std::string fileName )
	{
		story::StoryPtr s(new story::Story());
		s->Load(fileName);
		return s;
	}

	EntryPtr StoryLoader::LoadEntry( std::string filename )
	{
		StoryEntry* entry = new StoryEntry(filename);
		story::StoryPtr story = LoadStory(filename);
		entry->data = story;
		return EntryPtr(entry);
	}

}