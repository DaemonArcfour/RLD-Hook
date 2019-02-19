#ifndef RLD_CVARS
#define RLD_CVARS
#include "g_Include.h"
class cRLD_CVars {
public:
	bool rld_spinhack = false;
	bool rld_lag = false;
	bool rld_speedhack = false;
	bool rld_wdi_autoheal = false;
	bool rld_record_packets = false;
	bool rld_play_packets = false;
	bool rld_start_packet_saving_sequence = false;
	bool rld_start_packet_loading_sequence = false;
	bool rld_crash_server = false;
	bool rld_wallhack = false;
	bool rld_send_auth = true;
	bool rld_req_snapshot = true;
	bool rld_override = false;
	bool rld_autoshoot = false;
	bool rld_snd_reqsnap = false;
	int rld_speedhack_power = 1;
	int rld_crash_packet_length;
};  cRLD_CVars extern gRLD_CVars;
void Greeting();
void **getFBaseCVar_String(const char* CVarName);
void setCVars();
#endif