#include "Isilme.h"

Renderer::Renderer() :
	mMeterToPixelRatio(64.0f)
{
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

void	HGERenderer::ApplyCamera(Camera* camera)
{
	mHGE->Gfx_SetTransform(0.0f ,0.0f, -MeterToPixel(camera->x), -MeterToPixel(camera->y), 0.0f, 1.0f, 1.0f);
}

void	HGERenderer::Draw(LevelPtr level)
{

	LayerList*	layers = level->GetLayers();
	Camera*		camera = level->GetCamera();

	for (LayerList::iterator it = layers->begin(); it != layers->end(); ++it)
	{
		LayerPtr layer = *it;
		ApplyCamera(camera);
			
		for (EntityList::iterator i = layer->GetObjects()->begin(); i != layer->GetObjects()->end(); ++i)
		{
			GraphicsPtr graphics = (*i)->GetGraphics();

			float x = MeterToPixel((*i)->GetPosition().x);
			float y = MeterToPixel((*i)->GetPosition().y);
			float angle = (*i)->GetAngle();

			graphics->Render(x, y, angle);
		}
	}

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