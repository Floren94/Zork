#include "Room.h"

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;


Room::Room(int n)
{
	switch (n) {
	case  1:
		CreateRoom_1();
		break;
	case  2:
		CreateRoom_2();
		break;
	case  3:
		CreateRoom_3();
		break;
	case  4:
		CreateRoom_4();
		break;
	case  5:
		CreateRoom_5();
		break;
	case  6:
		CreateRoom_6();
		break;
	case  7:
		CreateRoom_7();
		break;
	case  8:
		CreateRoom_8();
		break;
	case  9:
		CreateRoom_9();
		break;
	}
}

FString Room::GetSeccDescr(int secc) 
{
	return sections[secc - 1].description;
}

FString Room::CheckLook(int secc)
{
	if (sections[secc - 1].look == 1) {
		return sections[secc - 1].lookText;
	}
	else {
		return "++You see nothing.";
	}
}

FString Room::GetRoomDescr(int r, int secc)
{
	return "Key: " + std::to_string(sections[secc - 1].key) + " Lance: " + std::to_string(sections[secc - 1].lance) + " Snack: " + std::to_string(sections[secc - 1].snack);
}

int32 Room::CheckItemPick(int secc, int item)
{
	switch (item) {
	case 1:
		if (sections[secc - 1].key = 1) { return 1; }
		break;
	case 2:
		if (sections[secc - 1].lance = 1) { return 2; }
		break;
	case 3:
		if (sections[secc - 1].snack = 1) { return 3; }
		break;
	case 4:
		if (sections[secc - 1].bigbag = 1) { return 4; }
	}
	return 0;
}

int Room::CheckItemLook(int secc)
{
	if (sections[secc - 1].key == 1) {
		return 1;
	}
	else if (sections[secc - 1].lance == 1){
		return 2;
	}
	else if (sections[secc - 1].snack == 1) {
		return 3;
	}
	else if (sections[secc - 1].bigbag == 1) {
		return 4;
	}
	else return 0;
}

bool Room::CheckDir(int secc, int dir)
{
	if (sections[secc - 1].vectorDirections[dir].first > 0) {
		return true;
	}
	return false;
}

std::pair<int, int> Room::nextRoom(int dir, int secc) const
{
	return sections[secc - 1].vectorDirections[dir];
}

void Room::ReciveItem(int item, int secc)
{
	switch (item) {
	case 1:
		sections[secc - 1].key = 1;
		break;
	case 2:
		sections[secc - 1].lance = 1;
		break;
	case 3:
		sections[secc - 1].snack = 1;
		break;
	}
}

void Room::GiveItem(int item, int secc)
{
	switch (item) {
	case 1:
		sections[secc - 1].key = 0;
		break;
	case 2:
		sections[secc - 1].lance = 0;
		break;
	case 3:
		sections[secc - 1].snack = 0;
		break;
	}
}

//implement room 10 (exit) and change for 5.4 when main door is opened.

void Room::CreateRoom_1()
{
	for (int i = 1; i <= 2; i++) {
		Section secc;
		secc.secNum = i;
		if (i == 1){
			secc.description = "--You're at the end of a room that extends to the east.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(1, 2));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
		}
		else {
			secc.description = "--You're at the enter of a room, you see a door to the south.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(2, 3));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(1, 1));
					break;
				}
			}
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_2()
{
	for (int i = 1; i <= 4; i++) {
		Section secc;
		secc.secNum = i;
		switch (i) {
		case  1:
			secc.description = "--You're at the start of a corridor that extends to the west and then turns left. You see the hall to the east.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(5, 1));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(2, 2));
					break;
				}
			}
			break;
		case  2:
			secc.description = "--You're still at the corridor.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(2, 1));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(2, 3));
					break;
				}
			}
			break;
		case  3:
			secc.description = "--You're at the corridor and see a door to the north. Here the corridor turns.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(1, 2));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(2, 2));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(2, 4));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
			break;
		case  4:
			secc.description = "--You're at the end of a corridor. You see doors to the south and west.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(2, 3));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(3, 1));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(4, 1));
					break;
				}
			}
			break;
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_3()
{
	for (int i = 1; i <= 2; i++) {
		Section secc;
		secc.look = 1;
		secc.lookText = "++It seems that someone threw his stuff on a rush.";
		secc.secNum = i;
		if (i == 1) {
			secc.description = "--You're in a room, you see a door to the west. This place is a mess, everything is on the floor.";
			secc.bigbag = 1;
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(2, 4));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(3, 2));
					break;
				}
			}
		}
		else {
			secc.description = "--You're in a bathroom, you see doors to the north and to the east.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(4, 1));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(3, 1));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_4()
{
	for (int i = 1; i <= 2; i++) {
		Section secc;
		secc.secNum = i;
		if (i == 1) {
			secc.description = "--You're at the guest room, you see doors to the east and south.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(4, 2));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(2, 4));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(3, 2));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
		}
		else {
			secc.description = "--You're still at the guest room and you see a big Armor. There is an empty spot... looks like another one is missing.";
			secc.snack = 1;
			secc.look = 1;
			secc.lookText = "++Looks like someone ate here. The leftovers are still fresh.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(4, 1));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_5()
{
	for (int i = 1; i <= 4; i++) {
		Section secc;
		secc.secNum = i;
		switch (i) {
		case  1:
			secc.description = "--You're at the left side of the hall. You see a corridor to the west.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(5, 2));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(2, 1));
					break;
				}
			}
			break;
		case  2:
			secc.description = "--You're at the center of the hall. You see the main door to the south.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(5, 3));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(5, 4));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(5, 1));
					break;
				}
			}
			break;
		case  3:
			secc.description = "--You're at the right side of the hall. You see a corridor to the east.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(6, 1));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(5, 2));
					break;
				}
			}
			break;
		case  4:
			secc.description = "--You're at the entrance of the hall. The main door is in front of you, this looks like the way out.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(5, 2));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
			break;
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_6()
{
	for (int i = 1; i <= 4; i++) {
		Section secc;
		secc.secNum = i;
		switch (i) {
		case  1:
			secc.description = "--You're at the start of a corridor that extends to the east and then turns right. You see a door to the south.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(6, 2));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(7, 1));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(5, 3));
					break;
				}
			}
			break;
		case  2:
			secc.description = "--You're still at the corridor";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(6, 3));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(6, 1));
					break;
				}
			}
			break;
		case  3:
			secc.description = "--You're at the corridor, you see doors but all of them are blocked. Here the corridor turns.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(6, 4));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(6, 2));
					break;
				}
			}
			break;
		case  4:
			secc.description = "--You're at the end of a corridor. You see a door to the south.";
			for (int i = 0; i <= 3; i++) {
				switch (i) {
				case  0:
					secc.vectorDirections.push_back(std::make_pair(6, 3));
					break;
				case  1:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				case  2:
					secc.vectorDirections.push_back(std::make_pair(8, 1));
					break;
				case  3:
					secc.vectorDirections.push_back(std::make_pair(0, 0));
					break;
				}
			}
			break;
		}
		sections.push_back(secc);
	}
}

void Room::CreateRoom_7()
{
	Section secc;
	secc.secNum = 0;
		secc.description = "--You're at a dark room full of dust. All you see is a door half opened to the east.";
		for (int i = 0; i <= 3; i++) {
			switch (i) {
			case  0:
				secc.vectorDirections.push_back(std::make_pair(6, 1));
				break;
			case  1:
				secc.vectorDirections.push_back(std::make_pair(9, 1));
				break;
			case  2:
				secc.vectorDirections.push_back(std::make_pair(0, 0));
				break;
			case  3:
				secc.vectorDirections.push_back(std::make_pair(0, 0));
				break;
			}
		}
		sections.push_back(secc);
}

void Room::CreateRoom_8()
{
	Section secc;
	secc.secNum = 1;
	secc.description = "--You're in a room full of weapons. There's a wierd hole on one of the walls and a door to the north."; 
	for (int i = 0; i <= 3; i++) {
		switch (i) {
		case  0:
			secc.vectorDirections.push_back(std::make_pair(6, 4));
			break;
		case  1:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		case  2:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		case  3:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		}
	}
	secc.look = 1;
	secc.lance = 1;
	secc.lookText = "++ It looks like you could use a key on that hole...";
	sections.push_back(secc);
}

void Room::CreateRoom_9()
{
	Section secc;
	secc.secNum = 1;
	secc.description = "--There are stairs behind the door. You follow them and find yourself in the second floor. ";
	secc.description += "This floor is destroyed and full of rune. All you see is the stairs to the south and an arm from a dead man under the runes.";
	for (int i = 0; i <= 3; i++) {
		switch (i) {
		case  0:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		case  1:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		case  2:
			secc.vectorDirections.push_back(std::make_pair(7, 1));
			break;
		case  3:
			secc.vectorDirections.push_back(std::make_pair(0, 0));
			break;
		}
	}
	secc.key = 1;
	secc.look = 1;
	secc.lookText = "++Looks like the poor guy got trapped on his way out.";
	sections.push_back(secc);
}






