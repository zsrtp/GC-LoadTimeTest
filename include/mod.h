#pragma once

#include "defines.h"
#include <tp/d_com_inf_game.h>
#include "eventListener.h"
#include "HUDConsole.h"

namespace mod
{
	class Mod
	{
		public:
			Mod();
			/**
			 * Init this and other stuff in order for all
			 * modifications to work
			 */
			void init();

			/**
			 * Custom event listener that can
			 * schedule function calls
			 */
			event::EventListener* eventListener;
			HUDConsole* hudConsole;

			bool startTest;

			bool initLoad = false;

			u32 loadTimer;
			u32 timerLimit;

			u32 totalLoadFrames;
			u32 lastLoadFrames;
			float totalLoadTime;
			float lastLoadTime;

			u32 roomIndex = 0;
			u32 stageIndex = 0;
			u32 spawnID = 0;


#ifdef TP_US
double frameRate = 29.97;
#elif defined TP_JP
double frameRate = 29.97;
#elif defined TP_EU
double frameRate = 30;
#endif


		// Functions
		private:
			/**
			 * Runs once each frame
			 */
			void procNewFrame();		
			
			/**
			 * Runs when checking if the treasure chest content
			 * should be returned or can be obtained
			 */
			bool procCheckTreasureRupeeReturn(void* unk1, s32 item);

			s32 procEvtSkipper(void* evtPtr);

		// Private members
		//private:
			

		// Hook trampolines
		private:
			void (*fapGm_Execute_trampoline)() = nullptr;
			
			s32 (*evt_control_Skipper_trampoline)(void* eventPtr) = nullptr;

	};
}