#pragma once
#include <vector> 
#include "Room.h"

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;

class World
{
public:
	World(); // constructor
	void Start();
	void UnlockMainDoor();
	void DropItem(int room, int secc, int item) const;
	void PickItem(int room, int secc, int item) const;
	int32 CheckPickItem(int room, int secc, int item) const;
	std::pair<int, int> nextRoom(int dir, int room, int secc) const;
	bool CheckDirection(int dir, int room, int secc) const;
	FString GetRoomDescr(int r, int secc) const;
	std::pair<FString , int> LookRoom(int r, int secc) const;
private:
	std::vector<Room *> vectorRooms;
};

