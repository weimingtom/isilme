#include "Isilme.h"

// BodyDef

BodyDef::BodyDef() :
	Type(BodyDef::SimpleBody)
{
}

void			BodyDef::ParseB2DBody(TiXmlElement* bodyElement)
{
	// Создаем определение тела
	int isBullet		= 0;
	float angle			= 0;
	int isAllowSleep	= 1;
	int isFixedRotation	= 0;
	int isActive		= 1;

	// Считываем тип тела
	if (strcmp(bodyElement->Attribute("Type"), "Dynamic") == 0)
		B2DBodyDef.type = b2_dynamicBody;
	else if (strcmp(bodyElement->Attribute("Type"), "Kinematic") == 0)
		B2DBodyDef.type = b2_kinematicBody;
	else
		B2DBodyDef.type = b2_staticBody;

	// Запрашиваем параметры тела
	bodyElement->QueryIntAttribute("Bullet", &isBullet);
	bodyElement->QueryIntAttribute("FixedRotation", &isFixedRotation);
	bodyElement->QueryFloatAttribute("Angle", &angle);
	bodyElement->QueryIntAttribute("AllowSleep", &isAllowSleep);
	bodyElement->QueryIntAttribute("Active", &isActive);

	// Устанавливаем параметры тела
	B2DBodyDef.bullet			= (isBullet != 0);
	B2DBodyDef.angle			= angle;
	B2DBodyDef.allowSleep		= (isAllowSleep != 0);
	B2DBodyDef.fixedRotation	= (isFixedRotation != 0);
	B2DBodyDef.active			= (isActive != 0);
	B2DBodyDef.linearDamping	= 0.0f;
	B2DBodyDef.angularDamping	= 0.1f;
	
	bodyElement->QueryFloatAttribute("LinearDumping", &(B2DBodyDef.linearDamping));
	bodyElement->QueryFloatAttribute("AngularDumping", &(B2DBodyDef.angularDamping));

	// Создаем геометрию тела
	TiXmlElement* fixtureElement = bodyElement->FirstChildElement();
	for (fixtureElement; fixtureElement; fixtureElement = fixtureElement->NextSiblingElement())
	{
		b2FixtureDef* fixtureDef = ParseB2DFixture(fixtureElement);
		B2DFixtures.push_back(fixtureDef);
	}
}

b2FixtureDef*	BodyDef::ParseB2DFixture(TiXmlElement* fixtureElement)
{
			
	// Создаем фигуру
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	b2CircleShape circleShape;
	float friction	= 0.3f;
	float density	= 1.0f;
	int maskBits	= 0;
	int categoryBits = 0;
	int isSensor	= 0;
	float restitution = 0.1f;

	// Читаем аттрибуты фигуры
	fixtureElement->QueryFloatAttribute("Friction", &friction);
	fixtureElement->QueryFloatAttribute("Density", &density);
	fixtureElement->QueryIntAttribute("MaskBits", &maskBits);
	fixtureElement->QueryIntAttribute("CategoryBits", &categoryBits);
	fixtureElement->QueryIntAttribute("Sensor", &isSensor);
	fixtureElement->QueryFloatAttribute("Restitution", &restitution);

	// Заполняем параметры
	fixtureDef->restitution = restitution;
	fixtureDef->density = density;
	fixtureDef->isSensor = (isSensor != 0);
	fixtureDef->friction = friction;
	fixtureDef->filter.groupIndex = 0;
	fixtureDef->filter.maskBits = maskBits;
	fixtureDef->filter.categoryBits = categoryBits;

	// Читаем геометрию
	if (strcmp(fixtureElement->Value(), "Box") == 0)
	{
		b2PolygonShape* poligonShape = new b2PolygonShape();
		// Создаем прямоугольник
		float width = 1.0f;
		float height = 1.0f;
		fixtureElement->QueryFloatAttribute("Width", &width);
		fixtureElement->QueryFloatAttribute("Height", &height);
		poligonShape->SetAsBox(width / 2.0f, height / 2.0f);
		fixtureDef->shape = poligonShape;
		
	}
	else if (strcmp(fixtureElement->Value(), "Circle") == 0)
	{
		b2CircleShape* circleShape = new b2CircleShape();
		// Создаем окружность
		float radius = 1.0f;
		fixtureElement->QueryFloatAttribute("Radius", &radius);
		circleShape->m_radius = radius;
		fixtureDef->shape = circleShape;
	}
	else if ((strcmp(fixtureElement->Value(), "Polygon")) == 0)
	{
		// Создаем многоугольник
	}
		
	return fixtureDef;
}

void	BodyDef::Parse(TiXmlElement* bodyElement)
{
	if (bodyElement == 0)
	{
		Type = BodyDef::SimpleBody;
	}
	else
	{
		Type = BodyDef::Box2DBody;
		ParseB2DBody(bodyElement);
	}
}

// Body

Body::~Body()
{
}

BodyDef::BodyType Body::GetType()
{
	return mType;
}

void	Body::SetActive(bool flag)
{
}

// Box2dBody

Box2DBody::Box2DBody(BodyDef* def) 
{
	// Указываем тип
	mType = BodyDef::Box2DBody;

	// Создаем Box2D-тело
	mBody = def->World->CreateBody(&(def->B2DBodyDef));
	
	for (FixtureDefList::iterator it = def->B2DFixtures.begin(); it != def->B2DFixtures.end(); ++it)
	{
		mBody->CreateFixture(*it);
	}
}

Box2DBody::~Box2DBody()
{
	// Уничтожаем Box2D-тело
	mBody->GetWorld()->DestroyBody(mBody);
}

void		Box2DBody::SetEntity(Entity* entity)
{
	mBody->SetUserData((void*)entity);
}

Entity*		Box2DBody::GetEntity()
{
	return (Entity*)(mBody->GetUserData());
}

b2Body*	Box2DBody::GetBox2DBody()
{
	return mBody;
}

Vector2& Box2DBody::GetPosition()
{
	return (Vector2&)(mBody->GetPosition());
}

void Box2DBody::SetPosition(Vector2& position)
{
	mBody->SetTransform(position, mBody->GetAngle());
}

float Box2DBody::GetAngle()
{
	return mBody->GetAngle();
}

void Box2DBody::SetAngle(float angle)
{
	mBody->SetTransform(mBody->GetPosition(), angle);
}

void Box2DBody::SetActive(bool flag)
{
	mBody->SetActive(flag);
}

Vector2	Box2DBody::GetLinearVelocity()
{
	return mBody->GetLinearVelocity();
}

void	Box2DBody::SetLinearVelocity(Vector2& velocity)
{
	mBody->SetLinearVelocity(velocity);
}

Fixture*	Box2DBody::GetFixture(std::string& name)
{
	return mFixtures[name];
}

Fixture*	Box2DBody::CreateFixture(std::string& name, b2FixtureDef* fixtureDef)
{
	Fixture* fixture = mBody->CreateFixture(fixtureDef); 
	fixture->SetUserData((void*)(name.c_str()));
	mFixtures[name] = fixture;
	return fixture;
}

void	Box2DBody::DestroyFixture(std::string& name)
{
	Fixture* fixture = mFixtures[name];
	mBody->DestroyFixture(fixture);
}

void	Box2DBody::DestroyFixture(Fixture* fixture)
{
	std::string name = (const char*)(fixture->GetUserData());
	mBody->DestroyFixture(fixture);
	mFixtures.erase(name);
}

// SimpleBody

SimpleBody::SimpleBody() :
	mPosition(0.0f, 0.0f),
	mAngle(0)
{
	mType = BodyDef::SimpleBody;
}

SimpleBody::~SimpleBody()
{
}

void SimpleBody::SetEntity(Entity* entity)
{
	mEntity = entity;
}

Entity* SimpleBody::GetEntity()
{
	return mEntity;
}

Vector2& SimpleBody::GetPosition()
{
	return mPosition;
}

float	SimpleBody::GetAngle()
{
	return mAngle;
}

void	SimpleBody::SetAngle(float angle)
{
	mAngle = angle;
}

void	SimpleBody::SetPosition(Vector2& position)
{
	mPosition = position;
}

void	SimpleBody::SetLinearVelocity(Vector2& velocity)
{
	
}

Vector2 SimpleBody::GetLinearVelocity()
{
	return Vector2(0.0f, 0.0f);
}

Fixture*	SimpleBody::GetFixture(std::string& fixture)
{
	return 0;
}