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

	/// Поведение активатора. Персонажи могут использовать активаторы, и сами-по себе тоже являются активаторами
	class Activator : public IActivator
	{
	public:
		/// Возвращает активатор, который может использовать объект
		static ActivatorPtr	GetActivatorFor(EntityPtr entity);

		Activator();
		virtual ~Activator();

		virtual void	UseBy(CreaturePtr creature);

		virtual bool	IsUsable() const;
		
		virtual void	SetUsable(bool flag);

		/// Возвращает игровое имя активатора
		virtual std::string GetName() const;

		/// Sets ingame name of the activator
		virtual void SetName(std::string name);
	protected:
		virtual void	OnUse(CreaturePtr creature);

	private:
		bool	isUsable;

		/// Имя активатора
		std::string mName;
	};
};
#endif