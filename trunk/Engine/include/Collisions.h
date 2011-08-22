#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <Box2D/Box2D.h>
#include <string>
#include <map>

class IsilmeExport DestructionListener : public b2DestructionListener
{
public:
	DestructionListener();
	virtual ~DestructionListener();
	virtual void SayGoodbye(b2Fixture* fixtuure);
	virtual void SayGoodbye(b2Joint* joint);
protected:
};

class IsilmeExport ContactListener : public b2ContactListener
{
public:
	ContactListener();
	virtual ~ContactListener();
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldMainfold);
protected:
};

class IsilmeExport ContactFilter : public b2ContactFilter
{
public:
	ContactFilter();
	virtual ~ContactFilter();
	virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
protected:
};

// Класс физического движка
class IsilmeExport Box2DEngine
{
public:
	b2World* CreateWorld();
	static Box2DEngine* GetSingleton();

	static EntityPtr	GetEntityAABB(b2World* world, float lx, float ly, float ux, float uy);

	static EntityList	GetEntitiesAABB(b2World* world, float lx, float ly, float ux, float uy);
protected:
	Box2DEngine();
	virtual ~Box2DEngine();

	static Box2DEngine*	mInstance;
};

#endif