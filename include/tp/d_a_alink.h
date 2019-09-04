#pragma once

#include "defines.h"

namespace tp::d_a_alink
{
	// Should try to fill in the variables at some point
	struct LadderVars
	{
		u8 unk_0[0x28];
		float ladderClimbInitSpeed;
		u8 unk_2c[0x4];
		float ladderReachTopClimbUpSpeed;
		u8 unk_30[0x4];
		float ladderTopStartClimbDownSpeed;
		u8 unk_34[0x4];
		float ladderBottomGetOffSpeed;
		u8 unk_38[0x8];
		float ladderClimbSpeed;
		u8 unk_40[0x10];
		float wallClimbHorizontalSpeed;
		u8 unk_58[0x4];
		float wallClimbVerticalSpeed;
		u8 unk_5c[0x4];
	} __attribute__((__packed__));

	static_assert(sizeof(LadderVars) == 0x70);

	extern "C"
	{
		void setStickData();
		bool checkHeavyStateOn(s32 unk1, s32 unk2);
		bool checkTreasureRupeeReturn(void* unk1, s32 item);

		// Variables
		extern LadderVars ladderVars;
	}
}