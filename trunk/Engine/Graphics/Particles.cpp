#include "IsilmePCH.h"
#include "Particles.h"
#include "ResourceManager.h"

namespace graphics
{

	ParticlesDefinition::~ParticlesDefinition()
	{
	}

	void	ParticlesDefinition::Parse(TiXmlElement* element)
	{
		Texture = "";
		PSIFile = "";

		if (element->Attribute("Texture"))
			Texture = element->Attribute("Texture");

		PSIFile = element->Value();
	}

	Particles::Particles(ParticlesDefinition* def)
	{
		hgeSprite* sprite = new hgeSprite(Engine::GetSingleton()->GetResourceManager()->GetTexture(def->Texture), 0, 0, 32, 32);
		mSystem = new hgeParticleSystem(def->PSIFile.c_str(), sprite);
		mSystem->Fire();
	}

	Particles::~Particles()
	{
	}

	void	Particles::Render(float x, float y, float angle)
	{
		mSystem->MoveTo(x, y, true);
		mSystem->Render();
	}

	void	Particles::Update(float elapsedTime)
	{
		mSystem->Update(elapsedTime);
	}

	GraphicsPtr ParticlesDefinition::Create()
	{
		return GraphicsPtr(new Particles(this));
	}
};