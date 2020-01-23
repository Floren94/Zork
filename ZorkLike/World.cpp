#include "World.h"
#include <vector> 
#include "Room.h"

World::World() { Start(); }

void World::Start() 
{
	for (int i = 1; i <=10; i++) {
		Room *roomptr = new Room(i);
		vectorRooms.push_back(roomptr);
	}

}

void World::UnlockMainDoor()
{
	vectorRooms[4]->OpenMainDoor();
}

void World::DropItem(int room, int secc, int item) const
{
	vectorRooms[room - 1]->ReciveItem(item, secc);
}

void World::PickItem(int room, int secc, int item) const
{
	vectorRooms[room - 1]->GiveItem(item, secc);
}

int32 World::CheckPickItem(int room, int secc, int item) const
{
	return vectorRooms[room - 1]->CheckItemPick(secc, item);
}

std::pair<int, int> World::nextRoom(int dir, int room, int secc) const
{
	return vectorRooms[room - 1]->nextRoom(dir - 1, secc);
}

bool World::CheckDirection(int dir, int room, int secc) const
{
	return vectorRooms[room - 1]->CheckDir(secc, dir -1);
}

FString World::GetRoomDescr(int r, int secc) const
{
	return vectorRooms[r - 1]->GetSeccDescr(secc);
}

FString World::CheckSecc(int r, int secc) const
{
	return vectorRooms[r - 1]->GetRoomDescr(r, secc);
}

std::pair<FString, int> World::LookRoom(int r, int secc) const
{
	return std::make_pair( vectorRooms[r - 1]->CheckLook(secc) , vectorRooms[r - 1]->CheckItemLook(secc));
}
