#include "RLD_CVars.h"

void setCVars() {
	orgAddCommandString("set rld_spinhack 0", 0);
	orgAddCommandString("set rld_lag 0", 0);
	orgAddCommandString("set rld_wdi_autoheal 0", 0);
	orgAddCommandString("set rld_speedhack 0", 0);
	orgAddCommandString("set rld_speedhack_power 1", 1);
	orgAddCommandString("set rld_record_packets 0", 0);
	orgAddCommandString("set rld_play_packets 0", 0);
	orgAddCommandString("set rld_start_packet_saving_sequence 0", 0);
	orgAddCommandString("set rld_start_packet_loading_sequence 0", 0);
	orgAddCommandString("set rld_crash_server 0", 0);
	orgAddCommandString("set rld_wallhack 0", 0);
	orgAddCommandString("set rld_crash_packet_length 21845", 0);
	orgAddCommandString("set rld_send_auth 1", 0);
	orgAddCommandString("set rld_req_snapshot 1", 0);
	orgAddCommandString("set rld_override 0", 0);
	orgAddCommandString("set rld_snd_reqsnap 0", 0);
	orgAddCommandString("set rld_autoshoot 0", 0);
	orgAddCommandString("alias autoshoot \"+attack;wait;-attack\"", 0);
}
void Greeting() {
	CPrintf("\\clDa\\cce\\clm\\cco\\cln\\cc's RELOADED DLL v1.666\n");
	CPrintf("\\cc------------RLD_HOOK SETUP------------\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_spinhack 0\\cm /-/-/-/-/-\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_lag 0\\cm /-/-/-/-/-/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_wdi_autoheal 0\\cm /-/-/-\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_speedhack 0\\cm /-/-/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_speedhack_power 0\\cm /-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_crash_server 0\\cm -/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_wallhack 0\\cm -/-/-/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_send_auth 1\\cm /-/-/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_req_snapshot 1\\cm -/-/-/\\cc-\n");
	CPrintf("\\cc-\\cm/-/-/-/-/- \\cvrld_autoshoot 0\\cm /-/-/-/-/\\cc-\n");
	CPrintf("\\cc------------ RLD_HOOK END ------------\n\n");
	CPrintf("\\ccPACKET RECORDER SETUP:\n");
	CPrintf("\\cdrld_record_packets 0\n");
	CPrintf("\\cdrld_play_packets 0\n");
	CPrintf("\\cdrld_start_packet_saving_sequence 0\n");
	CPrintf("\\cdrld_start_packet_loading_sequence 0\n");
}
//I want to die, recode this please.
void **getFBaseCVar_String(const char* CVarName) {
	int cvar = _FindCVar(CVarName, NULL);
	int* dummy;
	return (void **)(*(int(__thiscall **)(int, int **, signed int))(*(DWORD *)cvar + 8))(cvar, &dummy, 3);
};