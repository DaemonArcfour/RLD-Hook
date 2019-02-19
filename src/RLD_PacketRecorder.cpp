#include "RLD_PacketRecorder.h"
char *gNet_Buffer[32768];
int gNet_Buffer_len[32768];
int gNet_Packet_Quantity = 0;
int gNet_Packet_Played = -1;
int gNet_Packet_Backup_Quantity = 0;
int SetRecEnv();
std::string globalPacketDir = "";
int CountPackets(std::string& path);

int SetRecEnv() {
	if (std::string(mapname).length() == 0)
		return -1;
	CreateDirectory("PacketRecorder", NULL);
	std::string PacketDirip = "PacketRecorder\\" + std::string(serverip);
	std::replace(PacketDirip.begin(), PacketDirip.end(), ':', '_');
	CreateDirectory(PacketDirip.c_str(), NULL);
	std::string PacketDirmap = PacketDirip + "\\" + std::string(mapname);
	globalPacketDir = PacketDirmap;
	int ret = CreateDirectory(PacketDirmap.c_str(), NULL);
	return ret;
}

int CountPackets(std::string& path)
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir(path.c_str());
	int counter = -2;
	if (dp != NULL)
	{
		while (ep = readdir(dp))
			counter++;
		(void)closedir(dp);
	}
	else
		perror("Couldn't open the directory");
	return counter;

}

void loadPacket(std::string packet) {
	std::ifstream packetStream(packet, std::ifstream::binary);
	packetStream.seekg(0, packetStream.end);
	long size = packetStream.tellg();
	packetStream.seekg(0);
	char* buffer = new char[size];
	packetStream.read(buffer, size);
	gNet_Buffer[gNet_Packet_Quantity] = new char[size];
	gNet_Buffer_len[gNet_Packet_Quantity] = size;
	memcpy(gNet_Buffer[gNet_Packet_Quantity], buffer, size);
	delete[] buffer;
	packetStream.close();
}
void loadSequence() {
	pr_clearbuf();
	for (int i = 0; i < CountPackets(globalPacketDir); i++) {
		gNet_Packet_Quantity = i;
		loadPacket(globalPacketDir + "\\" + std::string("packet_") + std::to_string(i) + std::string(".bin"));
	}
	gNet_Packet_Backup_Quantity = gNet_Packet_Quantity;
}

void savePacket(char* packet, int size, int sq_num) {
	std::ofstream packetStream(globalPacketDir + "\\" + std::string("packet_") + std::to_string(sq_num) + std::string(".bin"), std::ofstream::binary);
	packetStream.write(packet, size);
	packetStream.close();
}

void saveSequence() {
	for (int i = 0; i <= gNet_Packet_Backup_Quantity; i++)
		savePacket(gNet_Buffer[i], gNet_Buffer_len[i], i);
}


void pr_record(const char *buf, int len) {
	gNet_Buffer[gNet_Packet_Quantity] = new char[1024];
	memcpy(gNet_Buffer[gNet_Packet_Quantity], buf, sizeof(const char*)*len);
	gNet_Buffer_len[gNet_Packet_Quantity] = len;
	gNet_Packet_Quantity++;
	gNet_Packet_Backup_Quantity = gNet_Packet_Quantity;
}

void pr_clearbuf() {
	gNet_Packet_Quantity = 0;
	gNet_Packet_Played = -1;
}

void pr_playpackets() {

}
