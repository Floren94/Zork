#include "World.h"
#include <vector> 
#include "Room.h"

//This class manages the world we are moving in. Creates each room on it and can be acces by the Game COntroller
World::World() { Start(); }

void World::Start() 
{
	//creates 10 rooms to build the map. Each room is build as it should in the constructor.
	for (int i = 1; i <=10; i++) {
		Room *roomptr = new Room(i);
		vectorRooms.push_back(roomptr);
	}
}

//Opens main door
void World::UnlockMainDoor()
{
	vectorRooms[4]->OpenMainDoor();
}

//puts item in specified room
void World::DropItem(int room, int secc, int item) const
{
	vectorRooms[room - 1]->ReciveItem(item, secc);
}
//picks item in specified room
void World::PickItem(int room, int secc, int item) const
{
	vectorRooms[room - 1]->GiveItem(item, secc);
}
//Checks if item is in specified Room 
int32 World::CheckPickItem(int room, int secc, int item) const
{
	return vectorRooms[room - 1]->CheckItemPick(secc, item);
}
//takes direction and returns the next room we are moving to
std::pair<int, int> World::nextRoom(int dir, int room, int secc) const
{
	return vectorRooms[room - 1]->nextRoom(dir - 1, secc);
}
//Checks if you can move to that direction from the actual room
bool World::CheckDirection(int dir, int room, int secc) const
{
	return vectorRooms[room - 1]->CheckDir(secc, dir -1);
}
//room description show in your next turn
FString World::GetRoomDescr(int r, int secc) const
{
	return vectorRooms[r - 1]->GetSeccDescr(secc);
}
//Returns if room has a look description order and first item you see
std::pair<FString, int> World::LookRoom(int r, int secc) const
{
	return std::make_pair( vectorRooms[r - 1]->CheckLook(secc) , vectorRooms[r - 1]->CheckItemLook(secc));
}
