#include "Armor.h"

Armor::Armor() { Start(); }

void Armor::Start()
{
	lifes = 2;
	location.roomNum = 0;
	location.roomSecc = 0;
}

void Armor::Appear()
{
	location.roomNum = 5;
	location.roomSecc = 3;
}

void Armor::LooseLife()
{
	lifes--;
}

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
