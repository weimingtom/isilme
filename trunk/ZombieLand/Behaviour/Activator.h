#ifndef ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H
#define ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace behaviour
{
	/// Поведение активатора. Персонажи могут использовать активаторы, и сами-по себе тоже являются активаторами
	class Activator : public Behaviour
	{
	public:
		/// Возвращает активатор, который может использовать объект
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