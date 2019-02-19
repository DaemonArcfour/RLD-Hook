#ifndef RLD_PACKETMANAGEMENT
#define RLD_PACKETMANAGEMENT
#include "g_Include.h"
void loadPacket(std::string packet);
void loadSequence();
void savePacket(char* packet, int size, int sq_num);
void saveSequence();
void pr_record(const char *buf, int len);
void pr_clearbuf();
void pr_playpackets();
int SetRecEnv();
extern std::string globalPacketDir;
char extern *gNet_Buffer[32768];
int extern gNet_Buffer_len[32768];
int extern gNet_Packet_Quantity;
int extern gNet_Packet_Played;
int extern gNet_Packet_Backup_Quantity;
#endif