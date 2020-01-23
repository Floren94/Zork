#include <iostream>
#include "Player.h"
#include "Bag.h"

using int32 = int;

//This class manages our player location and lifes. Also our bag Class that is linked to our player
Player::Player() { Start();}

void Player::Start() {
	lifes = 3;
	location.roomNum = 1;
	location.roomSecc = 1;
	MyBag.Start();
	
	return;
}

//increse or reduce life
void Player::LooseLife()
{
	lifes--; 
}

void Player::WinLife()
{
	lifes++;
}

//checks if dead, alive or full life
int32 Player::CheckLife()
{
	if (lifes == MAXLIFES) {return 0;}
	else if (lifes == MINLIFES) { return 1;}
	else { return 2;}
}
