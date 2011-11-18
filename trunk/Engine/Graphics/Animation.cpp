#include "IsilmePCH.h"
#include "Animation.h"
#include "ResourceManager.h"

namespace graphics
{	
	Animation::Animation(AnimationDefinition* def)
	{
		mAnimation = new hgeAnimation(def->texture, def->frames, def->fps, def->x, def->y, def->width, def->height);
		mAnimation->Play();
		mAnimation->SetMode(def->loop ? HGEANIM_LOOP : HGEANIM_NOLOOP);
	}

	Animation::~Animation()
	{
		delete mAnimation;
	}

	void Animation::Reset()
	{
		mAnimation->Stop();
		mAnimation->Play();
	}

	void Animation::Render(float x, float y, float angle)
	{
		float width = mAnimation->GetWidth() * GetScale() / 2.0f;
		float height = mAnimation->GetHeight() * GetScale() / 2.0f;
		x -= (width*cos(angle) - height*sin(angle));
		y -= (width*sin(angle) + height*cos(angle));

		mAnimation->RenderEx(x, y, angle, GetScale(), GetScale());
	}

	void Animation::Update(float elapsedTime)
	{
		mAnimation->Update(elapsedTime);
	}

	void AnimationDefinition::Parse(TiXmlElement* defElement)
	{
		const char* textureFile = defElement->GetText();
		texture = Engine::GetSingleton()->GetResourceManager()->GetTexture(textureFile);
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
		frames = 1;
		loop = true;
		fps = 10.0;
		int isLoop = 1;

		defElement->QueryFloatAttribute("X", &x);
		defElement->QueryFloatAttribute("Y", &y);
		defElement->QueryFloatAttribute("Width", &width);
		defElement->QueryFloatAttribute("Height", &height);
		defElement->QueryIntAttribute("Frames", &frames);
		defElement->QueryFloatAttribute("FPS", &fps);
		defElement->QueryIntAttribute("Loop", &isLoop);
		loop = (isLoop != 0);
	}

	AnimationDefinition::AnimationDefinition()
	{
	}

	AnimationDefinition::~AnimationDefinition()
	{
	}

	GraphicsPtr	AnimationDefinition::Create()
	{
		return GraphicsPtr(new Animation(this));
	}
};