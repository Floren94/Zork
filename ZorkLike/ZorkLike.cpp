#include <iostream>
#include <string>
#include <stdlib.h>
#include "Player.h"
#include "Armor.h"
#include "World.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void NewTurn();
void GoOrder(FText t);
void DropOrder(FText t);
void PickOrder(FText t);
void UseOrder(FText t);
void LookOrder();
void CheckCombat();
void Attack();
void CheckPick(int item);
void CheckOrder(int32 i, FText t);
int32 CheckMainOrder(FText t);
int32 Direction(FText t);
int32 DropOrPickItem(FText t);
bool CheckItemToss(int32 item);

int32 moveOrder;
int32 dir;
int32 item;
int32 floorItem;
bool canEscape = false;
std::pair<int32, int32> nextRoom;
std::pair<FString, int32> lookPair;

Player MyPlayer;
Bag *bagptr;
Armor enemy;
World world;

char playerMove[256];

int main()
{
	bagptr = &MyPlayer.MyBag;
	PrintIntro();

	do{
		//If the armor is spawned, check if you're figthing it before the turn starts.
		if (canEscape) {
			CheckCombat();
		}
		NewTurn();
		// Check if you won or lost before the next turn.
		if (canEscape && MyPlayer.location.roomNum == 10) {
			MyPlayer.endGame = 1;
		}
	} while (MyPlayer.endGame == 0);

	switch (MyPlayer.endGame) {
	case 1:
		std::cout << std::endl << "+--------------------------------------------------------------------------------+";
		std::cout << std::endl << "**************** Congratulations you did it! Now you are free from the curse. **********************" << std::endl << std::endl;
		break;
	case 2:
		std::cout << std::endl << "+--------------------------------------------------------------------------------+";
		std::cout << std::endl << "**************** Looks like it was too much for you... Your body lays cold on the floor. **********************" << std::endl << std::endl;
		break;
	}
}

void PrintIntro()
{
	std::cout << "TESTING INITIALIZED..." << std::endl << std::endl;
	std::cout << "Coommands: " << std::endl << "-> Go + direction (ex: north)" << std::endl;
	std::cout << "-> Pick + item (ex: key) " << std::endl << "-> Drop + item (ex: snack) " << std::endl;
	std::cout << "-> Use + item (ex: lance) " << std::endl << "-> Look " << std::endl;
	return;
}

void NewTurn() 
{
	std::cout << std::endl << "+--------------------------------------------------------------------------------+" ;
	if (!MyPlayer.onCombat) {
		std::cout << std::endl << world.GetRoomDescr(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;
	}
	else {
		std::cout << std::endl << "++++++++++  ALERT!  ++++++++" << std::endl << "The Guardian's blocking the west side of the hall and willing to kill you!" << std::endl;
	}
	std::cout << ">>> What do you do?" << std::endl;
	std::cin.getline(playerMove, 100);
	moveOrder = CheckMainOrder(playerMove);
	CheckOrder(moveOrder, playerMove);
}

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
		// Command unknown case

	case 0:
		std::cout << "X- Order not understood, please try again." << std::endl;
		break;	
	case 1:
		// Go + direction case
		GoOrder(t);
		break;
	case 2:
		// Look case
		LookOrder();
		break;
	case 3:
		//Drop + item case
		DropOrder(t);
		break;
	case 4:
		//Pick + item case
		PickOrder(t);
		break;
	case 5:
		//Use + item case
		UseOrder(t);
		break;

	case 6:
		MyPlayer.location.roomNum = 6;
		MyPlayer.location.roomSecc = 1;
		bagptr->ownedItems.lance = 1; 
		world.UnlockMainDoor();
		canEscape = true;
		enemy.Appear();
		//std::cout << world.CheckSecc(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;
		break;
	}
}

void GoOrder(FText t)
{
	dir = Direction(t);
	if (dir != 0 && world.CheckDirection(dir, MyPlayer.location.roomNum, MyPlayer.location.roomSecc)) {
		nextRoom = world.nextRoom(dir, MyPlayer.location.roomNum, MyPlayer.location.roomSecc);
		//Can't go west if fighting armor.
		if (MyPlayer.onCombat == true && dir == 4) {
			std::cout << "X- The Guardian is blocking the way!" << std::endl;
		}else{
			MyPlayer.location.roomNum = nextRoom.first;
			MyPlayer.location.roomSecc = nextRoom.second;
		}
	}
	else {
		std::cout << "X- You can't go there." << std::endl;
	}
}

void LookOrder()
{
	lookPair = world.LookRoom(MyPlayer.location.roomNum, MyPlayer.location.roomSecc);
	std::cout << lookPair.first << std::endl;

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
}

void DropOrder(FText t)
{
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
}

void PickOrder(FText t)
{
	item = DropOrPickItem(t);
	CheckPick(item);
}

void UseOrder(FText t)
{
	item = DropOrPickItem(t);

	switch (item) {
	case 0:
		std::cout << "**** You don't have that." << std::endl;
		break;
	case 1:
		if (MyPlayer.location.roomNum == 8 && bagptr->TryUseKey()) {
			std::cout << "**** The key fits the hole! The key breaks after using it but the main door is still unlocked, you can now leave!" << std::endl;
			world.UnlockMainDoor(); 
			bagptr->ownedItems.key = 0;
			canEscape = true;
			enemy.Appear();
		}
		else if (bagptr->TryUseKey()) {
			std::cout << "*** You can't use it here." << std::endl;
		}
		else {
			std::cout << "**** You don't have that." << std::endl;
		}
		break;
	case 2:
		if (MyPlayer.onCombat == true && bagptr->TryUseLance()) {
			Attack();
		}
		else if (bagptr->TryUseLance()) {
			std::cout << "*** No enemies nearby." << std::endl;
		}
		else {
			std::cout << "**** You don't have that." << std::endl;
		}
		break;
	case 3:
		if (MyPlayer.CheckLife() != 0 && bagptr->TryUseSnack()) {
			MyPlayer.WinLife();
			std::cout << "*** You're feeling better! Your body doesn't hurt that much now." << std::endl;
		}
		else if (bagptr->TryUseSnack()) {
			std::cout << "*** You're feeling good and not hungry. Better save it in case you get hurt." << std::endl;
		}
		else {
			std::cout << "**** You don't have that." << std::endl;
		}
		break;
	}
}

void CheckPick(int item)
{
	floorItem = world.CheckPickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
	if (floorItem == item) {
		switch (item) {
		case 0:
			std::cout << "xxx You can't pick that." << std::endl;
			break;
		case 1:
			if (bagptr->GetItemCount() < bagptr->maxItems) {
				bagptr->ownedItems.key = 1;
				world.PickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "**** You picked the key!" << std::endl;
			}
			else {
				std::cout << "xxx You can't carry it. Maybe you can find something to place items inside." << std::endl;
			}
			break;
		case 2:
			if (bagptr->GetItemCount() < bagptr->maxItems) {
				bagptr->ownedItems.lance = 1;
				world.PickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
				std::cout << "**** You picked the lance!" << std::endl;
			}
			else {
				std::cout << "xxx You can't carry it. Maybe you can find something to place items inside." << std::endl;
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
				std::cout << "xxx You can't carry it. Maybe you can find something to place items inside." << std::endl;
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

void CheckCombat() {
	if (enemy.location.roomNum == MyPlayer.location.roomNum &&
		enemy.location.roomSecc == MyPlayer.location.roomSecc) {
		MyPlayer.onCombat = true;
		enemy.onCombat = true;
	}
	else if (MyPlayer.onCombat){
		MyPlayer.onCombat = false;
		enemy.onCombat = false;
	}
}

void Attack()
{
	if (rand() % 100 > 60) {
		enemy.LooseLife();
		if (enemy.CheckLife() == 1) {
			enemy.Dead();
			std::cout << "COMBAT RESULT: HIT!" << std::endl << " --> You hit the Guardian right in it's core! He falls to his knees and the armor breaks while he banishes. He's gone." << std::endl;
		}else{
			std::cout << "COMBAT RESULT: HIT!" << std::endl << " --> The Guardian didn't predict the strike and gets a direct hit! Keep attacking!" << std::endl;
		}
	}
	else {
		std::cout << "COMBAT RESULT: MISS!" << std::endl << " --> The Guardian did predict the strike and blocked it. He's thought but don't give up." << std::endl;
	}
}

