#include "Isilme.h"
#include "Joints.h"

// JointDefinition

JointDefinition::JointDefinition()
{
	def = 0;
}

JointDefinition::~JointDefinition()
{
}

void	JointDefinition::Parse(TiXmlElement* jointElement)
{
	std::string type = jointElement->Attribute("Type");
	entityA = jointElement->Attribute("EntityA");
	entityB = jointElement->Attribute("EntityB");

	Vector2	pointA(0.0f, 0.0f);
	Vector2 pointB(0.0f, 0.0f);

	sscanf_s(jointElement->Attribute("PointA"), "%f, %f", &pointA.x, &pointA.y);
	sscanf_s(jointElement->Attribute("PointB"), "%f, %f", &pointB.x, &pointB.y);

	if (type == "Distance")
	{
		b2DistanceJointDef* jDef = new b2DistanceJointDef();
		def = jDef;

		// Длинна соединения
		jDef->length = 1.0f;
		jointElement->QueryFloatAttribute("Length", &jDef->length);

		// Координаты привязки
		jDef->localAnchorA = pointA;
		jDef->localAnchorB = pointB;
	}
	else if (type == "Weld")
	{
		b2WeldJointDef* jDef = new b2WeldJointDef();
		def = jDef;

		// Угол
		jDef->referenceAngle = 0.0f;
		jointElement->QueryFloatAttribute("Angle", &jDef->referenceAngle);

		// Координаты привязки
		jDef->localAnchorA = pointA;
		jDef->localAnchorB = pointB;
	}
	else if (type == "Revolute")
	{
	}

	// Сталкиваются ли связанные тела
	int isCollide = 0;
	jointElement->QueryIntAttribute("Collide", &isCollide);
	def->collideConnected = isCollide != 0;

	// Тела
	def->bodyA = 0;
	def->bodyB = 0;
}
//
//// Joint
//
//Joint::Joint(JointDefinition* def)
//{
//	Entity* entityA = FactoryManager::GetSingleton()->GetEntity(def->entityA);
//	Entity* entityB = FactoryManager::GetSingleton()->GetEntity(def->entityB);
//
//	def->def->bodyA = ((Box2DBody*)(entityA->GetBody()))->GetBox2DBody();
//	def->def->bodyB = ((Box2DBody*)(entityB->GetBody()))->GetBox2DBody();
//
//	mJoint = def->world->CreateJoint(def->def);
//	mWorld = def->world;
//}
//
//Joint::~Joint()
//{
//	mWorld->DestroyJoint(mJoint);
//	mJoint = 0;
//}
//
//Entity* Joint::GetEntityA()
//{
//	return (Entity*)(mJoint->GetBodyA()->GetUserData());
//}
//
//Vector2 Joint::GetPointA()
//{
//	return mJoint->GetAnchorA();
//}
//
//Vector2 Joint::GetPointB()
//{
//	return mJoint->GetAnchorB();
//}
//
//Entity* Joint::GetEntityB()
//{
//	return (Entity*)(mJoint->GetBodyB()->GetUserData());
//}