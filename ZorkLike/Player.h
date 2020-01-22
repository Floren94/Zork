#pragma once
#include <string>
#include "Bag.h"

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;

struct RoomIdent
{
	int32 roomNum = 0;
	int32 roomSecc = 0;
};

class Player
{
public:
	Player(); // constructor
	int32 endGame = 0;
	RoomIdent location;
	Bag MyBag;
	void Start();
	void LooseLife();
	void WinLife();
	int32 CheckLife();
	
private:
	const int32 MAXLIFES = 3;
	const int32 MINLIFES = 0;
	int32 lifes;
};

