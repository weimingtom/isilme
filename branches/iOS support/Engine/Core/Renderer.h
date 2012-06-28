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
#ifndef RENDERER_H
#define RENDERER_H

#include "Definitions.h"
#include <hge.h>

class ISILME_API Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	/// Отображает сцену уровня
	/// @param level Level*	сцена уровеня
	virtual void	Draw(StatePtr state) = 0;

	/// Изменяет размер окна
	/// @param width int
	/// @param height int
	virtual void	Resize(int width, int height) = 0;

	virtual void	SetWindowed(bool windowed) = 0;

	/// Возвращает, рисуются ли физ. тела
	bool	GetDrawPhisics();

	/// Устанавить прорисовку физики
	void	SetDrawPhisics(bool value);

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

	/// Коэффициент увеличения
	float			mZoom;
private:
	bool mDrawPhisics;
};

/// @class HGERenderer
/// Рендерер использующий HGE
class ISILME_API HGERenderer : public Renderer
{
public:
	HGERenderer(HGE* hge);
	virtual ~HGERenderer();

	virtual void	Draw(StatePtr state);
	virtual void	Resize(int width, int height);
	virtual void	SetWindowed(bool windowed);
	virtual bool	IsWindowed();
	virtual void	BeginScene();
	virtual void	EndScene();
	virtual void	ApplyCamera(CameraPtr camera);
	void DrawBox2DBody(float x, float y, float angle, Box2DBody* body );
protected:
	HGE*			mHGE;
};
#endif