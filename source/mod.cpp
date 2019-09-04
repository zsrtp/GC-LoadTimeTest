#include "defines.h"
#include "mod.h"
#include "global.h"
#include "systemConsole.h"
#include "patch.h"
#include "controller.h"
#include "tools.h"
#include "array.h"
#include "eventListener.h"
#include "stage.h"
#include "room.h"
#include "game_patches.h"
#include "HUDConsole.h"

#include <tp/f_op_scene_req.h>
#include <tp/m_Do_controller_pad.h>
#include <tp/d_map_path_dmap.h>
#include <tp/evt_control.h>
#include <tp/f_op_scene_req.h>
#include <tp/d_com_inf_game.h>
#include <tp/f_ap_game.h>
#include <tp/f_op_actor_mng.h>
#include <tp/d_a_alink.h>
#include <tp/d_save.h>
#include <tp/JFWSystem.h>
#include <cstdio>
#include <cstring>

namespace mod
{
	Mod* global::modPtr = nullptr;
	event::EventListener* global::eventListenerPtr = nullptr;
	mod::HUDConsole* global::hudConsolePtr = nullptr;


	void main()
	{
		Mod* mod = new Mod();
		mod->init();
	}

	Mod::Mod()
	{
		eventListener = new event::EventListener();
		hudConsole = new HUDConsole("Settings", 0x80);
		global::modPtr = this;
		global::eventListenerPtr = this->eventListener;
		global::hudConsolePtr = this->hudConsole;
	}

	void Mod::init()
	{
		// Perform any necessary assembly overwrites
		game_patch::assemblyOverwrites();

		// Print controls
		strcpy(sysConsolePtr->consoleLine[0].line, "Load Time test");
		
		strcpy(sysConsolePtr->consoleLine[21].line, "Start test: R + A");
		strcpy(sysConsolePtr->consoleLine[22].line, "Stop test: R + B");

		u8 page = 0;

		// General settings
		hudConsole->addWatch(page, "Last Load(f):", &lastLoadFrames, 'u', WatchInterpretation::_u32);
		hudConsole->addWatch(page, "Last Load:", &lastLoadTime, 'f', WatchInterpretation::_float);
		hudConsole->addWatch(page, "Total Load(f):", &totalLoadFrames, 'u', WatchInterpretation::_u32);
		hudConsole->addWatch(page, "Total Time:", &totalLoadTime, 'f', WatchInterpretation::_float);
		//hudConsole->addWatch(page, "Index:", &roomIndex, 'u', WatchInterpretation::_u32);

		// Print
		hudConsole->draw();
		system_console::setState(true, 0);

		//eventListener->addLoadEvent(stage::allStages[Stage_Faron_Woods], 0x1, 0x15, 0xFF, 0xFF, tools::triggerRandomGenerator, event::LoadEventAccuracy::Stage_Room_Spawn);

		//   =================
		//  | Function Hooks  |
		//   =================

		fapGm_Execute_trampoline = patch::hookFunction(tp::f_ap_game::fapGm_Execute,
			[]()
			{
				global::modPtr->procNewFrame();
			}
		);

		evt_control_Skipper_trampoline = patch::hookFunction(tp::evt_control::skipper,
			[](void* evtPtr)
			{
				return global::modPtr->procEvtSkipper(evtPtr);
			}
		);
	}


	void Mod::procNewFrame()
	{
		if (startTest == true) {

			strcpy(sysConsolePtr->consoleLine[24].line, "Test Started");

			if (gameInfo.nextStageVars.triggerLoad && !initLoad) {
				initLoad = true;
				lastLoadFrames = 0; //new load changes value to 0
				loadTimer = 0; //new load resets load timer
			}

			if (isLoading)
			{
				totalLoadFrames++; //increase counter by 1 per frame during loads
				lastLoadFrames++; //increase last load counter by 1 per frame during loads
			}
			else {
				totalLoadTime = totalLoadFrames / frameRate;
				lastLoadTime = lastLoadFrames / frameRate;

				loadTimer++;

				initLoad = false;
			}

			timerLimit = 60;

			if (roomIndex == 13) {
				stageIndex = 1;
				spawnID = 0;
			}
			else if (roomIndex == 14) {
				stageIndex = 2;
			}
			else if (roomIndex == 15) {
				stageIndex = 3;
			}
			else if (roomIndex == 28) {
				stageIndex = 4;
			}
			else if (roomIndex == 29) {
				stageIndex = 5;
			}
			else if (roomIndex == 30) {
				stageIndex = 6;
			}
			else if (roomIndex == 43) {
				stageIndex = 7;
			}
			else if (roomIndex == 44) {
				stageIndex = 8;
			}
			else if (roomIndex == 45) {
				stageIndex = 9;
			}
			else if (roomIndex == 54) {
				stageIndex = 10;
			}
			else if (roomIndex == 55) {
				stageIndex = 11;
			}
			else if (roomIndex == 56) {
				stageIndex = 12;
			}
			else if (roomIndex == 72) {
				stageIndex = 13;
			}
			else if (roomIndex == 73) {
				stageIndex = 14;
			}
			else if (roomIndex == 74) {
				stageIndex = 15;
			}
			else if (roomIndex == 83) {
				stageIndex = 16;
			}
			else if (roomIndex == 84) {
				stageIndex = 17;
			}
			else if (roomIndex == 85) {
				stageIndex = 18;
			}
			else if (roomIndex == 86) {
				stageIndex = 19;
			}
			else if (roomIndex == 93) {
				stageIndex = 20;
			}
			else if (roomIndex == 106) {
				stageIndex = 21;
			}
			else if (roomIndex == 108) {
				stageIndex = 22;
			}
			else if (roomIndex == 109) {
				stageIndex = 23;
			}
			else if (roomIndex == 110) {
				stageIndex = 24;
			}
			else if (roomIndex == 127) {
				stageIndex = 25;
			}
			else if (roomIndex == 128) {
				stageIndex = 26;
			}
			else if (roomIndex == 129) {
				stageIndex = 27;
			}
			else if (roomIndex == 141) {
				stageIndex = 28;
			}
			else if (roomIndex == 142) {
				stageIndex = 29;
			}
			else if (roomIndex == 143) {
				stageIndex = 30;
			}
			else if (roomIndex == 144) {
				stageIndex = 31;
			}
			else if (roomIndex == 194) {
				stageIndex = 32;
			}
			else if (roomIndex == 195) {
				stageIndex = 33;
			}
			else if (roomIndex == 196) {
				stageIndex = 34;
			}
			else if (roomIndex == 197) {
				stageIndex = 35;
			}
			else if (roomIndex == 198) {
				stageIndex = 36;
			}
			else if (roomIndex == 199) {
				stageIndex = 37;
			}
			else if (roomIndex == 200) {
				stageIndex = 38;
			}
			else if (roomIndex == 201) {
				stageIndex = 39;
			}
			else if (roomIndex == 202) {
				stageIndex = 40;
			}
			else if (roomIndex == 203) {
				stageIndex = 41;
			}
			else if (roomIndex == 204) {
				stageIndex = 42;
			}
			else if (roomIndex == 206) {
				stageIndex = 43;
			}
			else if (roomIndex == 207) {
				stageIndex = 44;
			}
			else if (roomIndex == 217) {
				stageIndex = 45;
			}
			else if (roomIndex == 218) {
				stageIndex = 46;
			}
			else if (roomIndex == 221) {
				stageIndex = 47;
			}
			else if (roomIndex == 222) {
				stageIndex = 48;
			}
			else if (roomIndex == 223) {
				stageIndex = 49;
			}
			else if (roomIndex == 225) {
				stageIndex = 50;
				spawnID = 13;
			}
			else if (roomIndex == 228) {
				stageIndex = 51;
				spawnID = 0;
			}
			else if (roomIndex == 230) {
				stageIndex = 52;
			}
			else if (roomIndex == 235) {
				stageIndex = 53;
				spawnID = 1;
			}
			else if (roomIndex == 236) {
				spawnID = 0;	
			}
			else if (roomIndex == 238) {
				stageIndex = 54;
			}
			else if (roomIndex == 240) {
				stageIndex = 55;
			}
			else if (roomIndex == 255) {
				stageIndex = 56;
			}
			else if (roomIndex == 258) {
				stageIndex = 57;
			}
			else if (roomIndex == 259) {
				stageIndex = 58;
			}
			else if (roomIndex == 260) {
				stageIndex = 59;
			}
			else if (roomIndex == 261) {
				stageIndex = 60;
			}
			else if (roomIndex == 262) {
				stageIndex = 61;
			}
			else if (roomIndex == 263) {
				stageIndex = 62;
			}
			else if (roomIndex == 264) {
				stageIndex = 63;
			}
			else if (roomIndex == 265) {
				stageIndex = 64;
			}
			else if (roomIndex == 271) {
				stageIndex = 65;
			}
			else if (roomIndex == 275) {
				stageIndex = 66;
			}
			else if (roomIndex == 276) {
				stageIndex = 67;
			}
			else if (roomIndex == 283) {
				stageIndex = 68;
			}
			else if (roomIndex == 284) {
				stageIndex = 69;
			}
			else if (roomIndex == 285) {
				stageIndex = 69;
				spawnID = 10;
			}
			else if (roomIndex == 286) {
				stageIndex = 70;
				spawnID = 0;
			}
			else if (roomIndex == 287) {
				stageIndex = 71;
			}
			else if (roomIndex == 288) {
				stageIndex = 72;
			}
			else if (roomIndex == 294) {
				stageIndex = 73;
			}
			else if (roomIndex == 295) {
				stageIndex = 74;
			}

			if (loadTimer >= timerLimit && !initLoad) {
				tools::triggerSaveLoad(stage::allStages[stageIndex], room::allRooms[roomIndex], spawnID, 0, 0);
			}

			if (loadTimer >= timerLimit) {
				roomIndex++;
			}


		}
		else {
			strcpy(sysConsolePtr->consoleLine[24].line, "");
		}

		if(controller::checkForButtonInputSingleFrame((controller::PadInputs::Button_R | controller::PadInputs::Button_Z)))
		{
			// Toggle console			
			system_console::setState(!sysConsolePtr->consoleEnabled, 0);
		}

		if (controller::checkForButtonInputSingleFrame((controller::PadInputs::Button_R | controller::PadInputs::Button_A)))
		{
			startTest = true;
		}

		if (controller::checkForButtonInputSingleFrame((controller::PadInputs::Button_R | controller::PadInputs::Button_B)))
		{
			lastLoadFrames = 0;
			lastLoadTime = 0;
			totalLoadFrames = 0;
			totalLoadTime = 0;
			startTest = false;
			roomIndex = 0;
			stageIndex = 0;
		}

		if(sysConsolePtr->consoleEnabled)
		{
			// Parse inputs of this frame
			switch(tp::m_do_controller_pad::cpadInfo.buttonInputTrg)
			{
				case controller::PadInputs::Button_A:
					hudConsole->performAction(ConsoleActions::Option_Increase);
				break;

				case controller::PadInputs::Button_X:
					hudConsole->performAction(ConsoleActions::Option_Increase, 10);
				break;

				case controller::PadInputs::Button_B:
					hudConsole->performAction(ConsoleActions::Option_Decrease);
				break;

				case controller::PadInputs::Button_Y:
					hudConsole->performAction(ConsoleActions::Option_Decrease, 10);
				break;

				case controller::PadInputs::Button_DPad_Up:
					hudConsole->performAction(ConsoleActions::Move_Up);
				break;

				case controller::PadInputs::Button_DPad_Down:
					hudConsole->performAction(ConsoleActions::Move_Down);
				break;

				case controller::PadInputs::Button_DPad_Left:
					hudConsole->performAction(ConsoleActions::Move_Left);
				break;

				case controller::PadInputs::Button_DPad_Right:
					hudConsole->performAction(ConsoleActions::Move_Right);
				break;
			}
			hudConsole->draw();
		}

		// Call original function
		fapGm_Execute_trampoline();
	}

	s32 Mod::procEvtSkipper(void* evtPtr)
	{
		// Call original function
		return evt_control_Skipper_trampoline(evtPtr);
	}
}
