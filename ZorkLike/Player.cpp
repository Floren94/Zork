#include "Player.h"
#include "Bag.h"

using int32 = int;

Player::Player() { Start();}


void Player::Start() {
	lifes = 3;
	location.roomNum = 1;
	location.roomSecc = 1;
	MyBag.Start();
	
	return;
}

void Player::LooseLife()
{
	lifes++;
}

void Player::WinLife()
{
	lifes--;
}

int32 Player::CheckLife()
{
	if (lifes == MAXLIFES) {return 0;}
	else if (lifes == MINLIFES) { return 1;}
	else { return 2;}
}
