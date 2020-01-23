#pragma once
#include <string>
#include <vector> 

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;

//Each room can have multiple sections. These are the section params we need.
struct Section
{
	//section numeber in room. 
	int32 secNum;
	// Can I look command in here?
	int32 look = 0;
	//items here
	int32 key = 0;
	int32 lance = 0;
	int32 snack = 0;
	int32 bigbag = 0;
	//Section description at turn start, text when we look command, vector of neraby rooms at North, east, south, west (room, section)
	FString description;
	FString lookText;
	std::vector<std::pair<int32, int32>> vectorDirections;
};

class Room
{
public:
	Room(int n); // constructor
	void CreateRoom_1();
	void CreateRoom_2();
	void CreateRoom_3();
	void CreateRoom_4();
	void CreateRoom_5();
	void CreateRoom_6();
	void CreateRoom_7();
	void CreateRoom_8();
	void CreateRoom_9();
	void CreateRoom_10();
	void OpenMainDoor();
	void ReciveItem(int item, int secc);
	void GiveItem(int item, int secc);
	FString GetSeccDescr(int secc);
	FString CheckLook(int secc); 
	int32 CheckItemPick(int secc, int item);
	int32 CheckItemLook(int secc);
	bool CheckDir(int secc, int dir);
	std::pair<int, int> nextRoom(int dir, int secc) const;
private:
	std::vector <Section> sections;
};

