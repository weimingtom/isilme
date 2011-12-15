#include "IsilmePCH.h"
#include "Renderer.h"
#include "Engine.h"
#include "ResourceManager.h"


Renderer::Renderer() :
	mMeterToPixelRatio(64.0f)
{
	//test = new hgeSprite(Engine::GetSingleton()->GetResourceManager()->GetTexture("../Data/Textures/Sprites.png"), 0, 0, 512, 512);
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
	mHGE->Gfx_SetTransform(0.0f ,0.0f, -MeterToPixel(camera->x), -MeterToPixel(camera->y), 0.0f, 1.0f, 1.0f);
}

void	HGERenderer::Draw(LevelPtr level)
{
	CameraPtr	camera = level->GetActiveCamera();

	for (int i = 0 ; i <  level->GetLayersCount(); ++i)
	{
		LayerPtr layer = level->GetLayer(i);
		ApplyCamera(camera);
			
		for (int j = 0; j < layer->Size(); ++j)	
		{
			EntityPtr entity = layer->GetEntity(j);
			GraphicsPtr graphics = entity->GetGraphics();

			float x = MeterToPixel(entity->GetPosition().x);
			float y = MeterToPixel(entity->GetPosition().y);
			float angle = entity->GetAngle();

			graphics->Render(x, y, angle);
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