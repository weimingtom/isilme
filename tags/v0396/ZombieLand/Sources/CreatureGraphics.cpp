#include "TeddyTerror.h"
#include "Definitions.h"
#include "CreatureGraphics.h"

namespace graphics
{
	void CreatureGraphicsDefinition::Parse(TiXmlElement* element)
	{
		TiXmlElement* stateElement = element->FirstChildElement("Idle");
		if (stateElement)
		{
			IdleLeft = new AnimationDefinition();
			IdleRight = new AnimationDefinition();

			IdleLeft->Parse(stateElement->FirstChildElement("Left"));
			IdleRight->Parse(stateElement->FirstChildElement("Right"));
		}

		stateElement = element->FirstChildElement("Move");
		if (stateElement)
		{
			MoveLeft = new AnimationDefinition();
			MoveRight = new AnimationDefinition();

			MoveLeft->Parse(stateElement->FirstChildElement("Left"));
			MoveRight->Parse(stateElement->FirstChildElement("Right"));
		}

		stateElement = element->FirstChildElement("Jump");
		if (stateElement)
		{
			JumpLeft = new AnimationDefinition();
			JumpRight = new AnimationDefinition();

			JumpLeft->Parse(stateElement->FirstChildElement("Left"));
			JumpRight->Parse(stateElement->FirstChildElement("Right"));
		}
	}

	Graphics* CreatureGraphicsDefinition::Create()
	{
		return new CreatureGraphics(this);
	}

	CreatureGraphics::CreatureGraphics(CreatureGraphicsDefinition* def)
	{
		// Создаем анимации
		mMoveLeft = new Animation(def->MoveLeft);
		mMoveRight = new Animation(def->MoveRight);
		mJumpLeft = new Animation(def->JumpLeft);
		mJumpRight = new Animation(def->JumpRight);
		mIdleLeft = new Animation(def->IdleLeft);
		mIdleRight = new Animation(def->IdleRight);

		// Устанавливаем текущую анимацию
		mCurrentAnimation = mIdleLeft;
	}

	CreatureGraphics::~CreatureGraphics()
	{
	}

	void CreatureGraphics::Update(float elapsedTime)
	{
		// Проверяем сосотояние
		if (GetBehaviour()->GetMoveLeftAction()->IsActive() || GetBehaviour()->GetMoveRightAction()->IsActive())
		{
			if (GetBehaviour()->GetDirection() == DirectionLeft)
				mCurrentAnimation = mMoveLeft;
			else
				mCurrentAnimation = mMoveRight;
		}
		else 
		{
			if (GetBehaviour()->GetDirection() == DirectionLeft)
				mCurrentAnimation = mIdleLeft;
			else
				mCurrentAnimation = mIdleRight;
		}
		// Обновляем анимацию
		mCurrentAnimation->Update(elapsedTime);
	}

	void CreatureGraphics::Render(float x, float y, float angle)
	{
		mCurrentAnimation->Render(x, y, angle);
	}

	CreatureBehaviour* CreatureGraphics::GetBehaviour()
	{
		return (CreatureBehaviour*)GetEntity()->GetBehaviour();
	}
};