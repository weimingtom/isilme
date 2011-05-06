#ifndef STATE_H
#define STATE_H

#include "Level.h"
#include <guichan.hpp>
#include <guichan/hge.hpp>

/// @class State
/// @brief Состояние игры
/// Состояние игры представляет собой сцену уровня и графический интерфейс уровня
class IsilmeExport State
{
public:
	State();
	virtual ~State();

	/// Возвращает графический интерфейс состояния
	gcn::Gui* GetGUI();

	/// Установить графический интерфейс состояния
	void	SetGUI(gcn::Gui* gui);

	/// 
	bool IsPaused();
	void SetPaused(bool pause);
	void Start();

	/// Закрывает состояние
	void Close();

	/// Обновляет состояние
	bool Update(float elapsedTime);

	/// Рисует состояние
	virtual bool Draw(float elapsedTime);

	
	bool IsTransporate();
	void SetTransporate(bool value);
	bool GetPausePrev();
	void SetPausePrev(bool value);

	/// Уровень состояния
	LevelPtr GetLevel();
protected:
	virtual void OnUpdate(float elapsedTime);
	virtual void OnStart();
	virtual void OnResume();
	virtual void OnDraw();
	
private:
	/// Графический интерфейс
	gcn::Gui*	mGUI;

	bool mPausePrev;
	bool isPaused;
	bool isTransporate;

	/// Флаг закрытия состояния
	bool isClosed;

	/// Уровень состояния
	LevelPtr mLevel;

	// Special for GUi
    gcn::HGEGraphics* graphics;
    gcn::HGEInput* input;
    gcn::HGEImageLoader* imageLoader;
};


#endif