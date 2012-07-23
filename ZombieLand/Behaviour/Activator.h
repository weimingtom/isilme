#ifndef ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H
#define ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H

#include "../include/Definitions.h"

namespace behaviour
{
	/// @ interface IActivator
	class IActivator
	{
	public:
		virtual ~IActivator() {};

		/// Gets if the activator is available
		virtual bool IsUsable() const = 0;

		/// Sets if the activator can be used
		virtual void SetUsable(bool value) = 0;

		/// Implements the logic of the activator
		virtual void OnUse(CreaturePtr creature) = 0;

		/// Implements the logic of the activator
		virtual void	UseBy(CreaturePtr creature) = 0;
	};

	/// ��������� ����������. ��������� ����� ������������ ����������, � ����-�� ���� ���� �������� ������������
	class Activator : public IActivator
	{
	public:
		/// ���������� ���������, ������� ����� ������������ ������
		static ActivatorPtr	GetActivatorFor(EntityPtr entity);

		Activator();
		virtual ~Activator();

		virtual void	UseBy(CreaturePtr creature);

		virtual bool	IsUsable() const;
		
		virtual void	SetUsable(bool flag);

		/// ���������� ������� ��� ����������
		virtual std::string GetName() const;

		/// Sets ingame name of the activator
		virtual void SetName(std::string name);
	protected:
		virtual void	OnUse(CreaturePtr creature);

	private:
		bool	isUsable;

		/// ��� ����������
		std::string mName;
	};
};
#endif