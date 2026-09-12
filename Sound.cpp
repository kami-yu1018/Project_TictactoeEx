#include"Sound.h"

void Se::PlaySe(int se)
{
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
}

void Se::Reset_SeCheck()
{
	se_ring = 0;
}

void Se::StopSe(int se)
{
	StopSoundMem(se);
}