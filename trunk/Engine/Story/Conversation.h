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
#ifndef ISILME_QUESTS_CONVERSATION_H
#define ISILME_QUESTS_CONVERSATION_H

#include "Quests.h"

namespace story
{
	/// ����� ��������� ������
	class ISILME_API Conversation
	{
	public:
		static	ConversationPtr Get(std::string id);
		Conversation(std::string id = "");
		virtual ~Conversation();
		
		/// ���������� ������������� �������
		std::string GetID();

		void SetID(std::string id);

		/// ��������� ����� � ������
		void AddPhrase(PhrasePtr phrase);

		/// ���������� ���������� ����
		int GetPhrasesCount();

		/// ���������� ����� �� �������
		PhrasePtr GetPhrase(int index);

		/// ���������� �����, ������ � �������
		PhrasePtr AutoChoosePhrase(SpeakerPtr speaker);
	private:
		std::string mID;
		std::vector<PhrasePtr> mPhrases;
	};
};

#endif