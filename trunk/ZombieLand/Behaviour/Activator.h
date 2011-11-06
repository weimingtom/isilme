#ifndef ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H
#define ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace behaviour
{
	/// ��������� ����������. ��������� ����� ������������ ����������, � ����-�� ���� ���� �������� ������������
	class Activator : public Behaviour
	{
	public:
		/// ���������� ���������, ������� ����� ������������ ������
		static ActivatorPtr	GetActivatorFor(EntityPtr entity);

		Activator(BehaviourDefinition* def);
		virtual ~Activator();

		void	UseBy(CreaturePtr creature);

		bool	IsUsable();
		
		void	SetUsable(bool flag);
	protected:
		virtual void	OnUse(CreaturePtr creature);

	private:
		bool	isUsable;
	};
};
#endif