#include <iostream>
#include <string>
#include "Player.h"
#include "World.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void NewTurn();
void CheckPick(int item);
void CheckOrder(int32 i, FText t);
int32 CheckMainOrder(FText t);
int32 Direction(FText t);
int32 DropOrPickItem(FText t);
bool CheckItemToss(int32 item);

int32 moveOrder;
int32 dir;
int32 item;
bool canEscape = false;
std::pair<int32, int32> nextRoom;
std::pair<FString, int32> lookPair;

Player MyPlayer;
Bag *bagptr;
World world;

char playerMove[256];

int main()
{
	bagptr = &MyPlayer.MyBag;
	PrintIntro();
	do{
		NewTurn();
	} while (MyPlayer.endGame == 0);
}

void PrintIntro()
{
	std::cout << "TESTING INITIALIZED..." << std::endl;
	std::cout << "Room: " << MyPlayer.location.roomNum; 
	std::cout << " Section: " << MyPlayer.location.roomSecc << std::endl;
	std::cout << "Bag Num: " << bagptr->GetItemCount() << std::endl;
	return;
}

void NewTurn() 
{
	std::cout << world.GetRoomDescr(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;

	std::cout << ">>> What do you do?" << std::endl;
	std::cin.getline(playerMove, 100);
	moveOrder = CheckMainOrder(playerMove);
	CheckOrder(moveOrder, playerMove);
}

// Last command use (key hole, snack life++, lance will come with npc. Extra command for exit so you can win)
int32 CheckMainOrder(FText t)
{
	if ((t.find("Go") != std::string::npos) || (t.find("go") != std::string::npos)) {
		return 1;
	}
	else if ((t.find("Look") != std::string::npos) || (t.find("look") != std::string::npos)) {
		return 2;
	}
	else if ((t.find("Drop") != std::string::npos) || (t.find("drop") != std::string::npos)) {
		return 3;
	}
	else if ((t.find("Pick") != std::string::npos) || (t.find("pick") != std::string::npos)) {
		return 4;
	}
	else if ((t.find("Use") != std::string::npos) || (t.find("use") != std::string::npos)) {
		return 5;
	}
	else if ((t.find("Check") != std::string::npos) || (t.find("check") != std::string::npos)) {
		return 6;
	}
	return 0;
}

void CheckOrder(int32 i, FText t)
{

	switch (i) {
	case 0:
		std::cout << "X- Order not understood, please try again." << std::endl;
		break;	
	case 1:
		dir = Direction(t);
		if (dir != 0 && world.CheckDirection(dir, MyPlayer.location.roomNum, MyPlayer.location.roomSecc)) {
			nextRoom = world.nextRoom(dir, MyPlayer.location.roomNum, MyPlayer.location.roomSecc);
			MyPlayer.location.roomNum = nextRoom.first;
			MyPlayer.location.roomSecc = nextRoom.second;
		}
		else {
			std::cout << "X- You can't go there." << std::endl;
		}
		break;
	case 2:

		if (MyPlayer.location.roomNum == 5 && MyPlayer.location.roomSecc == 4 && canEscape) {
			std::cout << "**** Congratulations you escaped! ****" << std::endl;
			MyPlayer.endGame = 1;
			return;
		}

		lookPair = world.LookRoom(MyPlayer.location.roomNum, MyPlayer.location.roomSecc);
		std::cout << lookPair.first << std::endl;

		// 
		if (MyPlayer.location.roomNum == 8 && bagptr->TryUseKey()) {
			std::cout << "**** And you do! The main door is unlocked, you can now leave!" << std::endl;
			canEscape = true;
		}


		switch (lookPair.second) {
		case 1:
			std::cout << "*** You found the key! Pick it!" << std::endl;
			break;
		case 2:
			std::cout << "*** You found a lance, you could you use it to defend yourself." << std::endl;
			break;
		case 3:
			std::cout << "*** You found a snack, you can eat it later." << std::endl;
			break;
		case 4:
			std::cout << "*** You found a bag! Pick it so you can place an extra items inside it!" << std::endl;
			break;
		}
		break;
	case 3:
		item = DropOrPickItem(t);

		if (item != 0 && item != 4) {
			if (CheckItemToss(item)) {
				world.DropItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "___ Item dropped to the floor." << std::endl;
			}
			else {
			std::cout << "You don't have that..." << std::endl;
			}
		}
		else {
			std::cout << "You can't drop that..." << std::endl;
		}
		break;
	case 4:
		item = DropOrPickItem(t);
		CheckPick(item);
		break;
	case 5:
		std::cout << "Use what?" << std::endl;
		break;

	case 6:
		std::cout << world.CheckSecc(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;
		break;
	}
}

int32 Direction(FText t) {
	if ((t.find("North") != std::string::npos) || (t.find("north") != std::string::npos)) {
		return 1;
	}
	else if ((t.find("East") != std::string::npos) || (t.find("east") != std::string::npos)) {
		return 2;
	}
	else if ((t.find("South") != std::string::npos) || (t.find("south") != std::string::npos)) {
		return 3;
	}
	else if ((t.find("West") != std::string::npos) || (t.find("west") != std::string::npos)) {
		return 4;
	}
	return 0;
}

int32 DropOrPickItem(FText t) {

	if ((t.find("Key") != std::string::npos) || (t.find("key") != std::string::npos)) {
		return 1;
	}
	else if ((t.find("Lance") != std::string::npos) || (t.find("lance") != std::string::npos)) {
		return 2;
	}
	else if ((t.find("Snack") != std::string::npos) || (t.find("snack") != std::string::npos)) {
		return 3;
	}
	else if ((t.find("Bag") != std::string::npos) || (t.find("bag") != std::string::npos)) {
		return 4;
	}
	return 0;
}

bool CheckItemToss(int32 item)
{
	switch (item) {
	case 1:
		if (bagptr->ownedItems.key == 1) { 
			bagptr->ownedItems.key = 0;
			return true; 
		}
		break;
	case 2:
		if (bagptr->ownedItems.lance == 1) {
			bagptr->ownedItems.lance = 0;
			return true;
		}
		break;
	case 3:
		if (bagptr->ownedItems.snack == 1) {
			bagptr->ownedItems.snack = 0;
			return true;
		}
		break;
	}
	return false;
}

void CheckPick(int item)
{
	//function that returns bool if actual item is present (choose item to pick when more than 1))
	lookPair = world.LookRoom(MyPlayer.location.roomNum, MyPlayer.location.roomSecc);
	if (lookPair.second == item) {
		switch (item) {
		case 0:
			std::cout << "xxx You can't pick that." << std::endl;
			break;
		case 1:
			if (bagptr->GetItemCount() < bagptr->maxItems ){ 
				bagptr->ownedItems.key = 1;
				world.PickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "**** You picked the key!" << std::endl;
			}
			else {
				std::cout << "xxx You can't carry it." << std::endl;
			}
			break;
		case 2:
			if (bagptr->GetItemCount() < bagptr->maxItems) {
				bagptr->ownedItems.lance = 1;
				world.PickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "**** You picked the lance!" << std::endl;
			}
			else {
				std::cout << "xxx You can't carry it." << std::endl;
			}
			break;
			break;
		case 3:
			if (bagptr->GetItemCount() < bagptr->maxItems) {
				bagptr->ownedItems.snack = 1;
				world.PickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "**** You picked a snack!" << std::endl;
			}
			else {
				std::cout << "xxx You can't carry it." << std::endl;
			}
			break;
			break;
		case 4:
				bagptr->maxItems = 3;
				std::cout << "**** You can now place items inside the bag and carry more of them!" << std::endl;
			break;
		}
	}
	else {
		std::cout << "xxx You can't find that item here." << std::endl;
	}
}
