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
#ifndef ISILME_AI_AIBEHAVIOUR_H
#define ISILME_AI_AIBEHAVIOUR_H

#include "AITypes.h"
#include "../Core/Behaviour.h"

/// @class Behaviour
/// Behaviour model for agents (with AI)
class ISILME_API AIBehaviour : public Behaviour
{
public:
	AIBehaviour();
	virtual ~AIBehaviour();

	/// Initiate ai data
	///
	/// @param def		definition for AI
	void Init(AIBehaviourDef* def);

	/// Gets attribute with given id
	/// 
	/// @param id		Identifier of the attribute
	///
	/// @return Attribute instance or nullptr
	AttributePtr GetAttribute(std::string id) const;

	/// Gets value of the attribute with given id
	/// 
	/// @param id		Identifier of the attribute
	///
	/// @return value of the attribute (0 by default)
	float GetAttributeValue(std::string id) const;

	/// Adds attribute
	/// 
	/// @param attr	Attribute to add
	void AddAttribute(AttributePtr attr);

	/// Adds AI-package
	/// 
	/// @param id Identifier of AI-package to add
	void AddAIPackage(std::string id);

	/// Adds AI-package
	///
	/// @param package AI-package to add
	void AddAIPackage(AIPackagePtr package);

	/// Removes AI-package
	void RemoveAIPackage(AIPackagePtr package);

	/// Removes AI-package
	void RemoveAIPackage(std::string packageID);

	/// Sends message to another agent
	/// @return true if agent received the message. If agent is not AIBehaviour it could not get messages
	bool SendMessage(BehaviourPtr dest, MessageDataPtr data);

	/// Starts AI-packages
	/// Call this method if you override it 
	virtual void OnUpdate(float elapsedTime) override;

	/// ���������� ���� �� �������
	int GetRank(FractionPtr fraction) const;

	/// ���������� ���� �� ������� 
	int GetRank(std::string fractionID) const;

	/// ������������� ����
	void	SetRank(FractionPtr fraction, int rank);

	/// ������������� ����
	void	SetRank(std::string fractionID, int rank);	

	/// ���������� ��������� � ������� ���������
	int		GetAttitudeTo(AIBehaviourPtr creature) const;
private:
	typedef std::map<std::string, AttributePtr> AttributeMap;
	typedef std::list<AIPackagePtr>			AIPackageList;

	/// Attributes
	AttributeMap	mAttributes;

	/// Active packages
	AIPackageList	mActivePackages;

	/// Ranks in fractions
	std::map<FractionPtr, int>	mFractions;
};
#endif