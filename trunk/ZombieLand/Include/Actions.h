/// ****************************** Module Header ******************************
/// @file  Actions.h
///	Project:      Teddy Terror 
/// Copyright (c) Ofiel.
///
/// Модуль содержит описание действий, которые могут выполнять различные игровые 
/// объекты.	В	любой	момент	времени может выполняться несколько действий 
/// одновременно, но только если действия не являются взаимоисключающими. Каждое 
/// действие имеет параметры выполнения, которые храняться	в	 соответствующей 
/// структуре. Запоминание параметров происходит при	старте	действия,	 что 
/// позволяет исключить возможность испортить параметры выполняемого действия.
/// ***************************************************************************



#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <Isilme.h>
#include "Definitions.h"
#include "CreatureBehaviour.h"

/// @class Attack
/// Рукопашная атака
/// Персонаж осуществляет рукопашную атаку нанося повреждения стоящим рядом с ним врагам
/// @see AttackParams
/// @todo:
///	Выбор анимации соответствующей комбо-индексу <BR>
/// Восстановление анимации ожидания по заверщении действия <BR>
class Attack : public Action, public b2QueryCallback
{
public:
	Attack(CreatureBehaviour* behaviour);
	virtual ~Attack();
	virtual void OnStart(void* params);
	virtual bool ReportFixture(b2Fixture* fixture);
protected:
	AttackParams params;

	virtual void UpdateOnBeginning(float elapsedTime);
	virtual void UpdateOnDoing(float elapsedTime);
	virtual void UpdateOnEnding(float elapsedTime);
	virtual void UpdateOnReloading(float elapsedTime);
	virtual void OnDone();

};

#endif