#include <iostream>
#include <string>
#include <stdlib.h>
#include <thread> 
#include <chrono>
#include "Player.h"
#include "Armor.h"
#include "World.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//This is the Game controller. We will control the world, player, and enemy and all that involves them through here.
// We won't use pch here so  Project” > “ Configuration Properties” > “C/C++” > “Precompiled Headers > “Not Using Precompiled Headers“ in case we get an error about pch.h

void PrintIntro();
void NewTurn();
void GoOrder(FText t);
void DropOrder(FText t);
void PickOrder(FText t);
void UseOrder(FText t);
void LookOrder();
void CheckCombat();
void Attack();
void EnemyRoutine();
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
bool startEnemyAtt = false;
std::pair<int32, int32> nextRoom;
std::pair<FString, int32> lookPair;
std::thread th_Att;

Player MyPlayer;
Bag *bagptr;
Armor enemy;
World world;

char playerMove[256];

int main()
{
	// Game starts here
	bagptr = &MyPlayer.MyBag;
	PrintIntro();

	// While we don't win or loose we will keep doing this turn based structure
	do{
		//If the armor is spawned, check if you're figthing it before the turn starts.
		if (canEscape) {
			CheckCombat();
			// Thread that makes battle in real time
			if (startEnemyAtt) {
				startEnemyAtt = false;
				th_Att = std::thread(EnemyRoutine);
				th_Att.detach();
			}
		}
		// We will do our actions here
		NewTurn();
		// Check if you won or lost before the next turn.
		if (canEscape && MyPlayer.location.roomNum == 10) {
			MyPlayer.endGame = 1;
		}
	} while (MyPlayer.endGame == 0);

	//check if you win or loose
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

//prints at start
void PrintIntro()
{
	std::cout << "You wake up in an old mansion. Don't know were you are but something is telling you to leave as fast as you can... " << std::endl << std::endl;
	std::cout << "Coommands: " << std::endl << "-> Go + direction (ex: north)" << std::endl;
	std::cout << "-> Pick + item (ex: key) " << std::endl << "-> Drop + item (ex: snack) " << std::endl;
	std::cout << "-> Use + item (ex: lance) " << std::endl << "-> Look " << std::endl;
	return;
}

void NewTurn() 
{
	std::cout << std::endl << "+--------------------------------------------------------------------------------+" ;
	// prints room description or informs of battle
	if (!MyPlayer.onCombat) {
		std::cout << std::endl << world.GetRoomDescr(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;
	}
	else {
		//Alerts if we are fighting the enemy
		std::cout << std::endl << "++++++++++  ALERT!  ++++++++" << std::endl << "The Guardian's blocking the west side of the hall and willing to kill you!" << std::endl;
	}
	std::cout << ">>> What do you do?" << std::endl;
	//recive order
	std::cin.getline(playerMove, 100);
	if (MyPlayer.endGame != 2){
		moveOrder = CheckMainOrder(playerMove);
		CheckOrder(moveOrder, playerMove);
	}
}

//Check first word to see if matches a known command
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
	/* Debug purposes
	else if ((t.find("Check") != std::string::npos) || (t.find("check") != std::string::npos)) {
		return 6;
	}*/
	return 0;
}
//Check next word to see if we can complete the command
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

	//Shortcut to Boss fight. Case check in mainOrder
	//case 6:
	//	MyPlayer.location.roomNum = 6;
	//	MyPlayer.location.roomSecc = 1;
	//	bagptr->ownedItems.lance = 1; 
	//	world.UnlockMainDoor();
	//	canEscape = true;
	//	enemy.Appear();
	//	//std::cout << world.CheckSecc(MyPlayer.location.roomNum, MyPlayer.location.roomSecc) << std::endl;
	//	break;
	}
}
//Checks next room you're going and moves the player is posible
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
// Look description of the room and if any item is found
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
// Drops item to floor of current room
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
// Picks selected item if in room
void PickOrder(FText t)
{
	item = DropOrPickItem(t);
	CheckPick(item);
}
// Use object if can be used
void UseOrder(FText t)
{
	item = DropOrPickItem(t);

	switch (item) {
	case 0:
		std::cout << "**** You don't have that." << std::endl;
		break;
	case 1:
		//case key. Can only be used in a certain room section. Unlocks main door and spawns enemy
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
		//case lance. Olny if we are fighting the enemy
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
		//Case Snack. Can use it if you lost lifes at some point
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
//Check if item specified is pickable at the moment.
void CheckPick(int item)
{
	floorItem = world.CheckPickItem(MyPlayer.location.roomNum, MyPlayer.location.roomSecc, item);
	if (floorItem == item) {
		// We can carry just ONE item. If we find the bag we will place the rest of them inside. 
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
			// if you find the bag you can place items inside it and carry all of them
			bagptr->maxItems = 3;
			std::cout << "**** You can now place items inside the bag and carry more of them!" << std::endl;
			break;
		}
	}
	else {
		std::cout << "xxx You can't find that item here." << std::endl;
	}
}
// Check if go direction is valid
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
//Check if item specified exists
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
//Check If we have the item we want to drop
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
// Checks if you found the guardian and starts the fight
void CheckCombat() {
	if (enemy.location.roomNum == MyPlayer.location.roomNum &&
		enemy.location.roomSecc == MyPlayer.location.roomSecc &&
		!MyPlayer.onCombat) {
		MyPlayer.onCombat = true;
		enemy.onCombat = true;
		startEnemyAtt = true;
	}
	else if (MyPlayer.onCombat &&
		enemy.location.roomNum != MyPlayer.location.roomNum){
		MyPlayer.onCombat = false;
		enemy.onCombat = false;
	}
}
//40% chance to hit the guardian if you have the lance. Use lance case
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
//Called by thread, guardian routine of attack if in battle
void EnemyRoutine() {

	while (enemy.onCombat)
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (enemy.onCombat) {
			std::cout << std::endl << "+----------------   THE GUARDIAN IS PREPARING TO ATTACK!    ------------------------------------------------------+" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(3));
		if (enemy.onCombat) {
			std::cout << std::endl << "+----------------   YOU WERE HIT BY THE GUARDIAN !    ------------------------------------------------------------+" << std::endl;
			MyPlayer.LooseLife();
			if (MyPlayer.CheckLife() == 1) {
				std::cout << std::endl << "+------------   HE STOPS AND DEEPLY LOOKs INTO YOUR EYES... -ANY LAST WORDS?     ------------------------------+" << std::endl;
				MyPlayer.endGame = 2;
				enemy.onCombat = 0;
				return;
			}
		}
	}

}

