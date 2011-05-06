#ifndef SCRIPT_API_H
#define SCRIPT_API_H

#include <string>

namespace ScriptAPI
{
	/// Регистрирует все функции  
	void RegisterAPI();

	/// Создает сущность типа type и с именем name в текущем уровне. Взвращает имя сущности
	std::string	CreateEntity(std::string type, std::string name);

	/// Уничтожает сущность с заданным именем
	bool	DestroyEntity(std::string entity);

	/// Перемещает сущность на слой состояния
	bool	MoveEntityToLayer(std::string entity, std::string layer);

	/// Перемещает сущность
	bool	MoveEntityToPosition(std::string entity, float x, float y, float angle);

	/// Перемещает сущность
	bool	SetEntityPosition(std::string entity, float x, float y);

	/// Повернуть сущность
	bool	SetEntityAngle(std::string entity, float angle);

	/// Возвращает координату X сущности
	float	GetEntityX(std::string entity);

	/// Возвращает координату Y сущности
	float	GetEntityY(std::string entity);

	/// Возвращает угол поворота объекта
	float	GetEntityAngle(std::string entity);

	/// Добавить игроку здоровья
	bool	GiveHP(std::string entity, float health);

	/// Дать игроку розу
	bool	GiveRose();

	/// Добавить обычных патронов
	bool	GiveGunAmmo(int count);

	/// Добавить зажигательных патронов
	bool	GiveFireAmmo(int count);

	/// Добавить усиленных патронов
	bool	GiveForcedAmmo(int count);

	/// Добавить ракет
	bool	GiveRockets(int count);

	/// Установить здоровье для создания
	float	SetHealth(std::string creature, float health);

	/// Получить здоровье создания
	float	GetHealth(std::string creature);

	/// Нанести повреждение объекту
	float	Damage(std::string createure, float normalDamage, float fireDamage);

	/// Изменить скорость объекта (работает только с Box2DBody)
	bool	SetEntityVelocity(std::string entity, float vx, float vy);

	/// Применить силу к объекту
	bool	SetEntityImpulse(std::string name, float fx, float fy);

	/// Добавляет игроку бонусы
	bool	AddOrbs(int count);
};
#endif