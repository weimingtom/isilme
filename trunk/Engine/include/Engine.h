#ifndef ENGINE_H
#define ENGINE_H

#include <LuaCPP.h>
#include "Definitions.h"
#include "LogoState.h"

/// @class Engine
/// Игровой движок, агрегирует в себе средства управления звуком, сценой, ресурсами.
/// В программе может существовать только один экзэмпляр игрового движка.
/// Все подсистемы необходимо инициализировать, либо использовать уже существующую реализацию
/// игры и компонентов, например HGEGame
class IsilmeExport Engine
{
public:
	/// Возвращает Lua
	/// @depricated
	/// @return Lua* 
	Lua*					GetLua();

	/// Демонстрирует логотип
	/// @depricated
	void					ShowLogo();

	/// Возвращает менеджер ресурсов
	/// @return ResourceManager*
	ResourceManager*		GetResourceManager();
	
	/// Устанавливает менеджер ресурсов
	/// @param resourceManager ResourceManager*
	void					SetResourceManager(ResourceManager* resourceManager);

	/// @depricated 
	void					Start(State* startState);
	
	/// Возвращает единственный экзэмпляр движка
	/// @return Engine*
	static Engine*			GetSingleton();

	/// Возвращает подсистему ввода
	/// @return InputSystem*
	InputSystem*			GetInputSystem();

	/// Установить подсистему ввода
	/// Если ранее была установленна какая-либо иная подсистема ввода,
	/// она будет уничтожена.
	/// При уничтожении экзэмпляра движка, подсистема ввода также уничтожается
	/// @param inputSystem InputSystem* подсистема ввода
	void					SetInputSystem(InputSystem* inputSystem);

	/// @return SoundSystem*
	SoundSystem*			GetSoundSystem();

	/// Установить звуковую подсистему
	/// Если ранее была установленна какая-либо иная звуковая подсистема,
	/// она будет уничтожена.
	/// При уничтожении экзэмпляра движка, звуковая подсистема также уничтожается
	/// @param soundSystem SoundSystem* звуковая подсистема
	void					SetSoundSystem(SoundSystem* soundSystem);

	HGE* mHGE;
private:
	Engine();
	virtual ~Engine();

	/// @depricated
	State*					mLogo;

	ResourceManager*		mResourceManager;
	StateManager*			mStateManager;
	InputSystem*			mInputSystem;
	SoundSystem*			mSoundSystem;
	Lua*					mLua;

	// Экземпляр движка
	static Engine* mInstance;
	hgeSprite* mOfielLogo;

};

#endif
