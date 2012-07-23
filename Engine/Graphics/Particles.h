//  Copyright (C) 2010-2012 VSTU
//
//	This file is part of Isilme SDK.
//
//		Isilme SDK is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		Isilme SDK is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You should have received a copy of the GNU Lesser General Public License
//		along with Isilme SDK.  If not, see <http://www.gnu.org/licenses/>.
//		<http://www.gnu.org/licenses/>.
#ifndef ISILME_GRAPHICS_PARTICLES_H
#define ISILME_GRAPHICS_PARTICLES_H

#include "Definitions.h"
#include "Core/Graphics.h"
#include <hge.h>
#include <hgeparticle.h>

namespace graphics
{
	class Particles;

	// Particle system graphics definition
	class ISILME_API ParticlesDefinition : public GraphicsDefinition
	{
	public:
		virtual ~ParticlesDefinition();

		virtual void	Parse(TiXmlElement* element);
		virtual GraphicsPtr Create();

		std::string		Texture;
		std::string		PSIFile;
	};

	// Particle system graphics
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
}
#endif
