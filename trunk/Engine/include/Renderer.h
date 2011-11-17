#ifndef RENDERER_H
#define RENDERER_H

#include "Definitions.h"
#include <hge.h>

class IsilmeExport Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	/// Отображает сцену уровня
	/// @param level Level*	сцена уровеня
	virtual void	Draw(LevelPtr level) = 0;

	/// Изменяет размер окна
	/// @param width int
	/// @param height int
	virtual void	Resize(int width, int height) = 0;

	virtual void	SetWindowed(bool windowed) = 0;

	virtual bool	IsWindowed() = 0;

	virtual void	BeginScene() = 0;

	virtual void	EndScene() = 0;

	virtual void	ApplyCamera(CameraPtr camera) = 0;

	/// Установить количество пикселей на один метр
	void			SetMeterToPixelRatio(float ratio);

	/// Переводит метры в пиксели
	float			MeterToPixel(float meterSize);

	/// Переводит пиксели в метры
	float			PixelToMeter(float pixelSize);
protected:
	/// Количество пикселей в одном метре
	float			mMeterToPixelRatio;
};

/// @class HGERenderer
/// Рендерер использующий HGE
class IsilmeExport HGERenderer : public Renderer
{
public:
	HGERenderer(HGE* hge);
	virtual ~HGERenderer();

	virtual void	Draw(LevelPtr level);
	virtual void	Resize(int width, int height);
	virtual void	SetWindowed(bool windowed);
	virtual bool	IsWindowed();
	virtual void	BeginScene();
	virtual void	EndScene();
	virtual void	ApplyCamera(CameraPtr camera);
protected:
	HGE*			mHGE;
};
#endif