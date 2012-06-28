#ifndef SCRIPT_API_H
#define SCRIPT_API_H

#include <string>

namespace ScriptAPI
{
	/// ������������ ��� �������  
	void RegisterAPI();

	/// ������� �������� ���� type � � ������ name � ������� ������. ��������� ��� ��������
	std::string	CreateEntity(std::string type, std::string name);

	/// ���������� �������� � �������� ������
	bool	DestroyEntity(std::string entity);

	/// ���������� �������� �� ���� ���������
	bool	MoveEntityToLayer(std::string entity, std::string layer);

	/// ���������� ��������
	bool	MoveEntityToPosition(std::string entity, float x, float y, float angle);

	/// ���������� ��������
	bool	SetEntityPosition(std::string entity, float x, float y);

	/// ��������� ��������
	bool	SetEntityAngle(std::string entity, float angle);

	/// ���������� ���������� X ��������
	float	GetEntityX(std::string entity);

	/// ���������� ���������� Y ��������
	float	GetEntityY(std::string entity);

	/// ���������� ���� �������� �������
	float	GetEntityAngle(std::string entity);

	/// �������� ������ ��������
	bool	GiveHP(std::string entity, float health);

	/// ���� ������ ����
	bool	GiveRose();

	/// �������� ������� ��������
	bool	GiveGunAmmo(int count);

	/// �������� ������������� ��������
	bool	GiveFireAmmo(int count);

	/// �������� ��������� ��������
	bool	GiveForcedAmmo(int count);

	/// �������� �����
	bool	GiveRockets(int count);

	/// ���������� �������� ��� ��������
	float	SetHealth(std::string creature, float health);

	/// �������� �������� ��������
	float	GetHealth(std::string creature);

	/// ������� ����������� �������
	float	Damage(std::string createure, float normalDamage, float fireDamage);

	/// �������� �������� ������� (�������� ������ � Box2DBody)
	bool	SetEntityVelocity(std::string entity, float vx, float vy);

	/// ��������� ���� � �������
	bool	SetEntityImpulse(std::string name, float fx, float fy);

	/// ��������� ������ ������
	bool	AddOrbs(int count);
};
#endif