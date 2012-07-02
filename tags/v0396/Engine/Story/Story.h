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
#ifndef ISILME_QUESTS_STORY_H
#define ISILME_QUESTS_STORY_H

#include "Quests.h"

namespace story
{
	class ISILME_API Story/* : public boost::enable_shared_from_this<Story>*/
	{
		friend class Quest;
	public:
		void Load(std::string filename);
		Story();
		virtual ~Story();
		
		/// �������� �������
		void			Update(float elapsedTime);

		/// ���������� ����� �� �����
		QuestPtr		GetQuest(std::string name);

		QuestList*		GetActiveQuests();

		QuestList*		GetFinishedQuests();

		boost::signal<void(QuestPtr, int)>	OnSetStage;

		/// Adds quest to the story
		///
		/// @param	quest Quest to add
		void			AddQuest(QuestPtr quest);

		/// Removes quest from the tory
		///
		/// @param	quest Quest to remove
		void			RemoveQuest(QuestPtr quest);

		int				GetQuestsCount() const;

		QuestPtr		GetQuestAtIndex(const int index) const;
	protected:
		void			OnStartQuest(QuestPtr quest);
	private:
		QuestMap	mQuests;
		QuestList	mActiveQuests;
		QuestList	mFinishedQuests;

		QuestSet	mQuestsToStart;
		QuestSet	mQuestsToFinish;
	};
};

#endif