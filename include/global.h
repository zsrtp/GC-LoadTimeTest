#pragma once

#include "mod.h"
#include "eventListener.h"
#include "HUDConsole.h"

namespace mod::global
{
	extern mod::Mod* modPtr;
	extern mod::event::EventListener* eventListenerPtr;
	extern mod::HUDConsole* hudConsolePtr;
}