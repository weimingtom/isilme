#ifndef JOINTS_H
#define JOINTS_H

#include <tinyxml.h>
#include <string>
#include "Collisions.h"

class IsilmeExport JointDefinition
{
public:
	std::string	entityA;
	std::string entityB;
	Vector2	pointA;
	Vector2 pointB;
	b2World* world;

	b2JointDef*	def;

	JointDefinition();

	virtual ~JointDefinition();

	void	Parse(TiXmlElement* jointElement);
};

typedef boost::shared_ptr<JointDefinition> JointDefPtr;
//
//class IsilmeExport Joint : public Object
//{
//public:
//	Joint(JointDefPtr def);
//
//	~Joint();
//
//	EntityPtr GetEntityA();
//
//	EntityPtr GetEntityB();
//
//	Vector2 GetPointA();
//
//	Vector2 GetPointB();
//protected:
//	b2Joint* mJoint;
//	b2World* mWorld;
//};

#endif