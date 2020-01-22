#include "Player.h"
#include "Bag.h"

using int32 = int;

Player::Player() { Start();}


void Player::Start() {
	end = 0;
	lifes = 3;
	location.roomNum = 1;
	location.roomSecc = 1;
	MyBag.Start();
	
	return;
}
