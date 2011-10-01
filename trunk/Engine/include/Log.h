#ifndef ISILME_LOG_H
#define ISILME_LOG_H

#include "Definitions.h"
#include "Engine.h"
#include <hge.h>

#define LOG_W(format, ...) Engine::GetSingleton()->mHGE->System_Log(format, __VA_ARGS__)
#define LOG_E(format, ...) Engine::GetSingleton()->mHGE->System_Log(format, __VA_ARGS__)
#define LOG_D(format, ...) Engine::GetSingleton()->mHGE->System_Log(format, __VA_ARGS__)
#define LOG_M(format, ...) Engine::GetSingleton()->mHGE->System_Log(format, __VA_ARGS__)

#endif