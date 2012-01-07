#ifndef ISILME_GRAPHICS_PARTICLES_H
#define ISILME_GRAPHICS_PARTICLES_H

#include "Definitions.h"
#include "Graphics.h"
#include <hge.h>
#include <hgeparticle.h>

namespace graphics
{
	class Particles;

	// Описание системы частиц
	class ISILME_API ParticlesDefinition : public GraphicsDefinition
	{
	public:
		virtual ~ParticlesDefinition();

		virtual void	Parse(TiXmlElement* element);
		virtual GraphicsPtr Create();

		std::string		Texture;
		std::string		PSIFile;
	};

	// Система частиц как модель сущности
	class ISILME_API Particles : public Graphics
	{
	public:
		Particles(ParticlesDefinition* def);

		virtual ~Particles();

		virtual void	Render(float x, float y, float angle, float ratio);

		virtual void	Update(float elapsedTime);
	private:
		hgeParticleSystem* mSystem;
	};
};
#endif
