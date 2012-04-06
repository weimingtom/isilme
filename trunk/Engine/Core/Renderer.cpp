//  Copyright (C) 2010-2012 Alexander Alimov
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
//
//	Этот файл — часть Isilme SDK.
//
//		Isilme SDK - свободная программа: вы можете перераспространять ее и/или
//		изменять ее на условиях Меньшей стандартной общественной лицензии GNU в том виде,
//		в каком она была опубликована Фондом свободного программного обеспечения;
//		либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
//		версии.
//
//		Isilme SDK распространяется в надежде, что она будет полезной,
//		но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
//		или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей стандартной
//		общественной лицензии GNU.
//
//		Вы должны были получить копию Меньшей стандартной общественной лицензии GNU
//		вместе с этой программой. Если это не так, см.
//		<http://www.gnu.org/licenses/>.
#include "IsilmePCH.h"
#include "Renderer.h"
#include "Engine.h"
#include "ResourceManager.h"
#include <cmath>

static HTEXTURE phisicsTexture = 0;

Renderer::Renderer() :
	mMeterToPixelRatio(64.0f)
{
	mDrawPhisics = false;
}

Renderer::~Renderer()
{
}

void	Renderer::SetMeterToPixelRatio(float ratio)
{
	mMeterToPixelRatio = ratio;
}

float Renderer::MeterToPixel(float meterSize)
{
	return mMeterToPixelRatio * meterSize;
}

float	Renderer::PixelToMeter(float pixelSize)
{
	return pixelSize / mMeterToPixelRatio;
}

bool Renderer::GetDrawPhisics()
{
	return mDrawPhisics;
}

void Renderer::SetDrawPhisics( bool value )
{
	mDrawPhisics = value;
}

// HGERenderer

HGERenderer::HGERenderer(HGE* hge)
{
	mHGE = hge;
}

HGERenderer::~HGERenderer()
{
}

void	HGERenderer::BeginScene()
{
	mHGE->Gfx_BeginScene();
	mHGE->Gfx_Clear(0);
}

void	HGERenderer::EndScene()
{
	mHGE->Gfx_EndScene();
}

void	HGERenderer::ApplyCamera(CameraPtr camera)
{
	mHGE->Gfx_SetTransform(0.0f ,0.0f, std::floor(-MeterToPixel(camera->x)), std::floor(-MeterToPixel(camera->y)), 0.0f, 1.0f, 1.0f);
}

void	HGERenderer::Draw(StatePtr state)
{
	LevelPtr level = state->GetLevel();
	CameraPtr	camera = state->GetCamera();

	for (int i = 0 ; i <  level->GetLayersCount(); ++i)
	{
		LayerPtr layer = level->GetLayer(i);

		if (!layer->IsVisible())
			continue;

		ApplyCamera(camera);
			
		for (int j = 0; j < layer->Size(); ++j)	
		{
			EntityPtr entity = layer->GetEntity(j);
			GraphicsPtr graphics = entity->GetGraphics();

			float x = MeterToPixel(entity->GetPosition().x);
			float y = MeterToPixel(entity->GetPosition().y);
			float angle = entity->GetAngle();

			graphics->Render(x, y, angle);

			if (GetDrawPhisics() && entity->GetBody()->GetType() == BodyDef::Box2DBody)
			{
				DrawBox2DBody(x, y, angle, (Box2DBody*)(entity->GetBody()));
			}
		}
	}
//	test->Render(0, 0);
}

void	HGERenderer::Resize(int width, int height)
{
	mHGE->System_SetState(HGE_SCREENWIDTH, width);
	mHGE->System_SetState(HGE_SCREENHEIGHT, height);
}

void	HGERenderer::SetWindowed(bool windowed)
{
	mHGE->System_SetState(HGE_WINDOWED, windowed);
}

bool	HGERenderer::IsWindowed()
{
	return mHGE->System_GetState(HGE_WINDOWED);
}

void HGERenderer::DrawBox2DBody(float x, float y, float angle, Box2DBody* ibody )
{
	//if (!phisicsTexture)
	//	phisicsTexture = mHGE->Texture_Create(32, 32);

	angle = -angle;
	b2Body* body = ibody->GetBox2DBody();
	b2Fixture* fixture = body->GetFixtureList();
	while (fixture)
	{
		if (fixture->GetType() ==  b2Shape::e_polygon)
		{
			b2PolygonShape* shape = (b2PolygonShape*)(fixture->GetShape());
			for (int i = 0; i < shape->GetVertexCount(); ++i)
			{
				b2Vec2 v1 = i != 0 ? mMeterToPixelRatio * shape->GetVertex(i-1) : mMeterToPixelRatio * shape->GetVertex(shape->GetVertexCount() - 1);
				b2Vec2 v2 = mMeterToPixelRatio * shape->GetVertex(i);
				
				b2Vec2 start(v1.x * cos(angle) + v1.y * sin(angle), -v1.x * sin(angle) + v1.y * cos(angle));
				start += b2Vec2(x,y);
				b2Vec2 end(v2.x * cos(angle) + v2.y * sin(angle), -v2.x * sin(angle) + v2.y * cos(angle));
				end += b2Vec2(x,y);

				mHGE->Gfx_RenderLine(
					start.x, 
					start.y, 
					end.x, 
					end.y, 0xFFFFFFFF, 0.0f);
			}
		}
		else if (fixture->GetType() ==  b2Shape::e_circle)
		{
			b2CircleShape* shape = (b2CircleShape*)(fixture->GetShape());
			for (int i = 0; i < 17; ++i)
			{
				b2Vec2 v1 = mMeterToPixelRatio * b2Vec2(shape->m_radius * cos(6.28f / 16.0f * i), shape->m_radius * sin(6.28f / 16.0f * i));
				b2Vec2 v2 = mMeterToPixelRatio * b2Vec2(shape->m_radius * cos(6.28f / 16.0f * (i + 1)), shape->m_radius * sin(6.28f / 16.0f * (i+1)));

				b2Vec2 start(v1.x * cos(angle) + v1.y * sin(angle), -v1.x * sin(angle) + v1.y * cos(angle));
				start += b2Vec2(x,y);
				b2Vec2 end(v2.x * cos(angle) + v2.y * sin(angle), -v2.x * sin(angle) + v2.y * cos(angle));
				end += b2Vec2(x,y);

				mHGE->Gfx_RenderLine(
					start.x, 
					start.y, 
					end.x, 
					end.y, 0xFFFFFFFF, 0.0f);
			}
		}

		fixture = fixture->GetNext();
	}
}
