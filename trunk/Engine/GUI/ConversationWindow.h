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
#ifndef GCN_CONVERSATION_WINDOW_H
#define GCN_CONVERSATION_WINDOW_H

#include "Definitions.h"
#include "Engine/Story/Quests.h"
#include "ModalDialog.h"

namespace gcn
{
	class ISILME_API ConversationWindow : public ModalDialog
	{
	public:
		ConversationWindow();
		virtual ~ConversationWindow();

		virtual void mouseClicked(gcn::MouseEvent& evt);

		/// Setup conversation
		///
		/// @param conversation
		/// @param player - Human player
		/// @param speaker - NPC
		void SetConversation(story::ConversationPtr conversation, story::SpeakerPtr player, story::SpeakerPtr speaker);

		void SetCurrentPhrase(story::PhrasePtr phrase);
		virtual void Init();
	private:
		story::SpeakerPtr mPlayer;
		story::SpeakerPtr mSpeaker;
		TextBoxPtr mText;
		story::ConversationPtr mConversation;
		story::PhrasePtr mCurrentPhrase;
		std::map<gcn::ButtonPtr, story::PhrasePtr> mAnswers;
	};
	typedef boost::shared_ptr<ConversationWindow> ConversationWindowPtr;
};

#endif