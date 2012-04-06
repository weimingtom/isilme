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
#ifndef ISILME_GRAPHICS_STATEGRAPHICS_H
#define ISILME_GRAPHICS_STATEGRAPHICS_H

#include "Definitions.h"
#include "SpecialGraphics.h"
#include "../Core/FactoryManager.h"
#include "../Palette/GraphicsPalette.h"

namespace graphics
{
	template <class T>
	class StateGraphicsDef : public GraphicsDefinition
	{
	public:
		virtual GraphicsPtr Create();
		virtual void Parse(TiXmlElement* element);

		typedef std::map<std::string, GraphicsDefPtr> GraphicsMap;
		GraphicsMap Palette;
		std::string		State;
	};

	/// Графика по состояниям
	template <class T>
	class StateGraphics : public SpecialGraphics<T>
	{
	public:
		StateGraphics(StateGraphicsDef<T>* def);
		virtual ~StateGraphics();

		/// Установить графику для состояния
		void	SetState(std::string state);

		GraphicsPtr	GetState();

		GraphicsPtr GetState(std::string name);

		/// Изображает текущее состояние
		virtual void Render(float x, float y, float angle);

		virtual void Update(float elapsedTime);

		virtual void SelectState();
	protected:
	private:
		GraphicsMap mGraphics;
		GraphicsPtr mCurrentGraphics;
	};


	/// IMPLEMENTATION

	template<class T>
	StateGraphics<T>::StateGraphics(StateGraphicsDef<T>* def) :
		SpecialGraphics<T>(def)
	{
		// Создаем графику каждого состояния
		for (StateGraphicsDef<T>::GraphicsMap::iterator it = def->Palette.begin(); it != def->Palette.end(); ++it)
		{
			GraphicsPtr g = it->second->Create();
			mGraphics[it->first] = g;
		}

		// Устанавливаем текущую графику
		SetState(def->State);
	}
	
	template<class T>
	StateGraphics<T>::~StateGraphics()
	{
		mGraphics.clear();
		mCurrentGraphics.reset();
	}

	template<class T>
	GraphicsPtr StateGraphics<T>::GetState(std::string name)
	{
		GraphicsMap::iterator it = mGraphics.find(name);
		return it->second;
	}

	template<class T>
	void StateGraphics<T>::SetState(std::string state)
	{
		GraphicsMap::iterator it = mGraphics.find(state);
		if (it != mGraphics.end())
		{
			mCurrentGraphics = it->second;
			mCurrentGraphics->SetScale(GetScale());
		}
	}

	template<class T>
	void StateGraphics<T>::Render(float x, float y, float angle)
	{
		mCurrentGraphics->Render(x, y, angle);
		Graphics::Render(x,y,angle);
	}

	template<class T>
	void StateGraphics<T>::Update(float elapsedTime)
	{
		SelectState();
		mCurrentGraphics->Update(elapsedTime);
		Graphics::Update(elapsedTime);
	}

	template<class T>
	void StateGraphics<T>::SelectState()
	{
	}

	template<class T>
	GraphicsPtr StateGraphics<T>::GetState()
	{
		return mCurrentGraphics;
	}

	template<class T>
	GraphicsPtr StateGraphicsDef<T>::Create()
	{
		GraphicsPtr g(new StateGraphics<T>(this));

		return g;
	}

	template<class T>
	void StateGraphicsDef<T>::Parse(TiXmlElement* element)
	{
		GraphicsDefinition::Parse(element);

		TiXmlElement* stateElement = element->FirstChildElement("State");
		char* state = const_cast<char*>(element->Attribute("State"));

		while (stateElement)
		{
			char* name = const_cast<char*>(stateElement->Attribute("Name"));
			if (name == 0) name = "Default";
			
			if (state == 0)
				state = name;

			TiXmlElement* graphicsElement = stateElement->FirstChildElement();

			std::string type = graphicsElement->Value();
			GraphicsDefPtr def = FactoryManager::GetSingleton()->GetGraphicsPalette()->GetFactory(type)->LoadDefinition(graphicsElement);
			Palette[name] = def;

			stateElement = stateElement->NextSiblingElement("State");
		}

		State = state;
	}
};

#endif