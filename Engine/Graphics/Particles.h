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
	class IsilmeExport ParticlesDefinition : public GraphicsDefinition
	{
	public:
		virtual ~ParticlesDefinition();

		virtual void	Parse(TiXmlElement* element);
		virtual GraphicsPtr Create();
	};

	// Система частиц как модель сущности
	class IsilmeExport Particles : public Graphics
	{
	public:
		Particles(ParticlesDefinition* def);

		virtual ~Particles();

		virtual void	Render(float x, float y, float angle);

		virtual void	Update(float elapsedTime);
	private:
		hgeParticleSystem* mSystem;
	};
};
#endif
