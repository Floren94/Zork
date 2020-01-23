#pragma once
#include <string>
#include <thread> 

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;

struct RoomIdentEnemy
{
	int32 roomNum = 0;
	int32 roomSecc = 0;
};


class Armor
{
public:
	Armor(); //constructor
	bool onCombat = false;
	RoomIdentEnemy location;
	void Start();
	void Appear();
	void LooseLife();
	void Dead();
	int32 CheckLife();
	std::thread t1;
private:
	const int32 MAXLIFES = 2;
	const int32 MINLIFES = 0;
	int32 lifes;
};