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
//	���� ���� � ����� Isilme SDK.
//
//		Isilme SDK - ��������� ���������: �� ������ ������������������ �� �/���
//		�������� �� �� �������� ������� ����������� ������������ �������� GNU � ��� ����,
//		� ����� ��� ���� ������������ ������ ���������� ������������ �����������;
//		���� ������ 3 ��������, ���� (�� ������ ������) ����� ����� �������
//		������.
//
//		Isilme SDK ���������������� � �������, ��� ��� ����� ��������,
//		�� ���� ������ ��������; ���� ��� ������� �������� ��������� ����
//		��� ����������� ��� ������������ �����. ��������� ��. � ������� �����������
//		������������ �������� GNU.
//
//		�� ������ ���� �������� ����� ������� ����������� ������������ �������� GNU
//		������ � ���� ����������. ���� ��� �� ���, ��.
//		<http://www.gnu.org/licenses/>.
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>

#include <vector>
#include <list>
#include <set>
#include <map>

#if defined (_MSC_VER) 
#	pragma warning(push)
#	pragma warning (disable: 4251)
#	pragma warning (disable: 4275)
#endif

#include "Definitions.h"
#include "Engine/Config.h"

#include "Core/Action.h"
#include "Core/Behaviour.h"
#include "Core/Bodies.h"
#include "Core/Camera.h"
#include "Core/Collisions.h"
#include "Core/Engine.h"
#include "Core/Entity.h"
#include "Core/EntityDefinition.h"
#include "Core/FactoryManager.h"
#include "Core/Game.h"
#include "Core/Graphics.h"
#include "Core/InputSystem.h"
#include "Core/Joints.h"
#include "Core/Script.h"
#include "Core/SoundSystem.h"
#include "Core/StateManager.h"
#include "Core/LogoState.h"
#include "Core/Level.h"
#include "Core/Layer.h"
#include "Core/Log.h"
#include "Core/MasterFile.h"
#include "Core/Renderer.h"
#include "Core/ResourceManager.h"
#include "Core/State.h"
#include "Core/Query.h"

#include "Engine/ScriptAPI.h"
#include "Journal.h"
#include "Trigger.h"

#include "Graphics/Sprite.h"
#include "Graphics/Animation.h"
#include "Graphics/Particles.h"
#include "Graphics/TriggerGraphics.h"

#include "Palette/EntityPalette.h"

#if defined (_MSC_VER) 
#	pragma warning(pop)
#endif