#ifndef RLD_PSEUDOPLAYER
#define RLD_PSEUDOPLAYER
#include "g_Include.h"
class pseudoPlayer {
public:
	int Health = -1;
	char* Name = "NULL";
	bool self = false;
};
extern pseudoPlayer PlayerClass[64];
extern int LocalPlayer;
void update_LocalPlayerInfo();
#endif