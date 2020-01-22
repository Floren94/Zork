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
	RoomIdent location;
	Bag MyBag;
	void Start();
	int32 endGame = 0;
	
private:
	int32 end;
	int32 lifes;


};

