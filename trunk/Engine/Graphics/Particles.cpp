#include "Isilme.h"

namespace graphics
{

	ParticlesDefinition::~ParticlesDefinition()
	{
	}

	void	ParticlesDefinition::Parse(TiXmlElement* element)
	{
	}

	Particles::Particles(ParticlesDefinition* def)
	{
		hgeSprite* sprite = new hgeSprite(Engine::GetSingleton()->GetResourceManager()->GetTexture("../Data/Particles/Particles.png"), 0, 0, 32, 32);
		mSystem = new hgeParticleSystem("../Data/Particles/exploid.psi", sprite);
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