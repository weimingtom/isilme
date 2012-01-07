﻿#ifndef ISILME_GRAPHICS_ANIMATION_H
#define ISILME_GRAPHICS_ANIMATION_H

#include "Definitions.h"

namespace graphics
{

	// Описание анимации
	class ISILME_API AnimationDefinition : public GraphicsDefinition
	{
	public:
		HTEXTURE texture;
		float x;
		float y;
		float height;
		float width;
		int frames;
		float fps;
		bool loop;
		AnimationDefinition();
		virtual ~AnimationDefinition();
		virtual void Parse(TiXmlElement* defElement);
		virtual GraphicsPtr Create();
	};
	
	/// @class Animation
	/// Анимированная модель сущности
	class ISILME_API Animation : public Graphics
	{
	public:
		Animation(AnimationDefinition* def);
		virtual ~Animation();

		virtual void Render(float x, float y, float angle);
		virtual void Update(float elapsedTime);

		virtual void Reset();
	protected:
		hgeAnimation* mAnimation;
	};
};

#endif