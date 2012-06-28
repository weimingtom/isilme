#ifndef CREATURE_GRAPHICS_H
#define CREATURE_GRAPHICS_H

#include <Isilme.h>

namespace graphics
{
	class CreatureGraphicsDefinition : public GraphicsDefinition
	{
	public:
		AnimationDefinition* MoveLeft;
		AnimationDefinition* MoveRight;
		AnimationDefinition* JumpLeft;
		AnimationDefinition* JumpRight;
		AnimationDefinition* DeathLeft;
		AnimationDefinition* DeathRight;
		AnimationDefinition* IdleLeft;
		AnimationDefinition* IdleRight;

		virtual Graphics* Create();
		virtual void Parse(TiXmlElement* element);
	};

	/// @class CreatureGraphics
	/// Рисует существ
	class CreatureGraphics : public Graphics
	{
		friend class CreatureGraphicsDefinition;
	public:
		CreatureGraphics(CreatureGraphicsDefinition* def);
		virtual ~CreatureGraphics();

		virtual void Render(float x, float y, float angle);
		virtual void Update(float elapsedTime);
	protected:
	private:
		CreatureBehaviour* GetBehaviour();

		Animation*	mCurrentAnimation;

		Animation*	mMoveLeft;
		Animation*	mMoveRight;
		Animation*	mJumpLeft;
		Animation*	mJumpRight;
		Animation*	mDeathLeft;
		Animation*	mDeathRight;
		Animation*	mIdleLeft;
		Animation*	mIdleRight;
		Animation*	mAirLeft;
	};
};
#endif