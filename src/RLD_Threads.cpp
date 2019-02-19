#include "RLD_Threads.h"
cRLD_CVars gRLD_CVars;
void tRefreshCVars() {
	while (true) {
		if (atoi((const char*)*getFBaseCVar_String("rld_lag")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_lag"), "true") == 0)
			gRLD_CVars.rld_lag = 1;
		else
			gRLD_CVars.rld_lag = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_speedhack")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_speedhack"), "true") == 0)
			gRLD_CVars.rld_speedhack = 1;
		else
			gRLD_CVars.rld_speedhack = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_spinhack")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_spinhack"), "true") == 0)
			gRLD_CVars.rld_spinhack = 1;
		else
			gRLD_CVars.rld_spinhack = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_wdi_autoheal")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_wdi_autoheal"), "true") == 0)
			gRLD_CVars.rld_wdi_autoheal = 1;
		else
			gRLD_CVars.rld_wdi_autoheal = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_record_packets")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_record_packets"), "true") == 0)
			gRLD_CVars.rld_record_packets = 1;
		else
			gRLD_CVars.rld_record_packets = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_play_packets")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_play_packets"), "true") == 0)
			gRLD_CVars.rld_play_packets = 1;
		else
			gRLD_CVars.rld_play_packets = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_start_packet_saving_sequence")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_start_packet_saving_sequence"), "true") == 0)
			gRLD_CVars.rld_start_packet_saving_sequence = 1;
		else
			gRLD_CVars.rld_start_packet_saving_sequence = 0;

		if (atoi((const char*)*getFBaseCVar_String("rld_start_packet_loading_sequence")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_start_packet_loading_sequence"), "true") == 0)
			gRLD_CVars.rld_start_packet_loading_sequence = 1;
		else
			gRLD_CVars.rld_start_packet_loading_sequence = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_crash_server")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_crash_server"), "true") == 0)
			gRLD_CVars.rld_crash_server = 1;
		else
			gRLD_CVars.rld_crash_server = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_wallhack")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_wallhack"), "true") == 0)
			gRLD_CVars.rld_wallhack = 1;
		else
			gRLD_CVars.rld_wallhack = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_send_auth")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_send_auth"), "true") == 0)
			gRLD_CVars.rld_send_auth = 1;
		else
			gRLD_CVars.rld_send_auth = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_req_snapshot")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_req_snapshot"), "true") == 0)
			gRLD_CVars.rld_req_snapshot = 1;
		else
			gRLD_CVars.rld_req_snapshot = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_override")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_override"), "true") == 0)
			gRLD_CVars.rld_override = 1;
		else
			gRLD_CVars.rld_override = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_snd_reqsnap")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_snd_reqsnap"), "true") == 0)
			gRLD_CVars.rld_snd_reqsnap = 1;
		else
			gRLD_CVars.rld_snd_reqsnap = 0;
		if (atoi((const char*)*getFBaseCVar_String("rld_autoshoot")) > 0 || strcmp((const char*)*getFBaseCVar_String("rld_autoshoot"), "true") == 0)
			gRLD_CVars.rld_autoshoot = 1;
		else
			gRLD_CVars.rld_autoshoot = 0;
		
			gRLD_CVars.rld_speedhack_power = atoi((const char*)*getFBaseCVar_String("rld_speedhack_power"));
			gRLD_CVars.rld_crash_packet_length = atoi((const char*)*getFBaseCVar_String("rld_crash_packet_length"));
		Sleep(7);
	}
}

void tAutoHeal() {
	while (true) {
		if (gRLD_CVars.rld_wdi_autoheal == true) {
			update_LocalPlayerInfo();
			if (PlayerClass[LocalPlayer].Health <= 40 && PlayerClass[LocalPlayer].Health > 0)
				orgAddCommandString("use SmallKit", 0);
		}
			Sleep(150);
		
	}
}

void tKeyChecker() {
	bool *glag = (bool*)0x986C89;
	while (true) {
		Spinhack = gRLD_CVars.rld_spinhack;
		if (gRLD_CVars.rld_lag == true) {
			memset((void*)glag, 0x7C, sizeof(bool));
		}

		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
			orgAddCommandString("+use", 0);
			Sleep(5);
			orgAddCommandString("-use", 0);
			Sleep(5);
		}
		else {
			Sleep(2);
		}
		if (gRLD_CVars.rld_override) {
			orgAddCommandString("rld_override 0", 0);
			CPrintf("\\cvWarning: overriding netstate and vote state!\n");
			int *override1 = (int*)0x986CA8;
			int *override2 = (int*)0x985208;
			*override1 = 5;
			*override2 = 1;
			CPrintf("\\cvDone!\n");
		}
		if (gRLD_CVars.rld_snd_reqsnap) {
			orgAddCommandString("rld_snd_reqsnap 0", 0);
			void *edx = NULL;
			AttemptAuthentication(edx);
			RequestSnapshot();
		}

	}
	
}	