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
#ifndef ISILME_AI_AIPACKAGE_H
#define ISILME_AI_AIPACKAGE_H

#include "Definitions.h"
#include "AITypes.h"

class ISILME_API AIPackage
{
public:
	/// Creates action
	virtual ActionPtr CreateAction() const;

	/// Checks if AIPackage is applicable 
	virtual bool IsApplicable(BehaviourPtr behaviour) const;
    
    /// Calculates priority for the package
    ///
    /// @return a real value in [-1;1]
    virtual float   CalcPriority(BehaviourPtr behviour);

    virtual bool IsApplicable(AIBehaviourPtr actor) const;
    
    /// @return a real value 
    virtual float   CalcUtility(AIBehaviourPtr actor, EntityPtr target);
    
    TargetSelectorPtr   GetTargetSelector() const;
    
    void    SetTargetSelector(TargetSelectorPtr selector);
private:
    TargetSelectorPtr   mTargetSelector;
};


#endif