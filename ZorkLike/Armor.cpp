#include "Armor.h"

Armor::Armor() { Start(); }

//This Class manages position and lifes of the enemy
void Armor::Start()
{
	lifes = 2;
	location.roomNum = 0;
	location.roomSecc = 0;
}

//moves to room when spawned
void Armor::Appear()
{
	location.roomNum = 5;
	location.roomSecc = 3;
}

void Armor::LooseLife()
{
	lifes--;
}
// removes when killed
void Armor::Dead()
{
	location.roomNum = 0;
	location.roomSecc = 0;
	onCombat = false;
}


int32 Armor::CheckLife()
{
	if (lifes == MAXLIFES) { return 0; }
	else if (lifes == MINLIFES) { return 1; }
	else { return 2; }
}




