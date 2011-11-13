#ifndef ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H
#define ZOMBIELAND_BEHAVIOUR_ACTIVATOR_H

#include <Isilme.h>
#include "ZombieLand/Include/Definitions.h"

namespace behaviour
{
	
	class ActivatorDef : public BehaviourDefinition
	{
	public:
		ActivatorDef();
		virtual ~ActivatorDef();
		virtual BehaviourPtr Create();
		virtual void Parse(TiXmlElement* element);

		std::string Name;
	};

	/// Поведение активатора. Персонажи могут использовать активаторы, и сами-по себе тоже являются активаторами
	class Activator : public Behaviour
	{
	public:
		/// Возвращает активатор, который может использовать объект
		static ActivatorPtr	GetActivatorFor(EntityPtr entity);

		Activator(ActivatorDef* def);
		virtual ~Activator();

		void	UseBy(CreaturePtr creature);

		virtual bool	IsUsable();
		
		void	SetUsable(bool flag);

		/// Возвращает игровое имя активатора
		std::string GetName();
	protected:
		virtual void	OnUse(CreaturePtr creature);

	private:
		bool	isUsable;

		/// Имя активатора
		std::string mName;
	};
};
#endif