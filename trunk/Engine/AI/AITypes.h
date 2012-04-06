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
#ifndef ISILME_AI_TYPES_H
#define ISILME_AI_TYPES_H

#include "Definitions.h"

class Actuator;
typedef boost::shared_ptr<Actuator> ActuatorPtr;

class Attribute;
typedef boost::shared_ptr<Attribute> AttributePtr;

class AttributeDef;

class AIBehaviour;
typedef boost::shared_ptr<AIBehaviour> AIBehaviourPtr;

class AIBehaviourDef;

class AIPackage;
typedef boost::shared_ptr<AIPackage> AIPackagePtr;

class AIPackageDef;
typedef boost::shared_ptr<AIPackageDef> AIPackageDefPtr;

class IAIPackageFactory;
typedef boost::shared_ptr<IAIPackageFactory> AIPackageFactoryPtr;
typedef std::map<std::string, AIPackageFactoryPtr> AIFactoryMap;

class Message;
typedef boost::shared_ptr<Message> MessagePtr;

class MessageData;
typedef boost::shared_ptr<MessageData> MessageDataPtr;

class Perception;
typedef boost::shared_ptr<Perception> PerceptionPtr;

class PerceptionList;

class UtilityFunction;
typedef boost::shared_ptr<UtilityFunction> UtilityFunctionPtr;

#endif