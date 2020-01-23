#include "Bag.h"

using int32 = int;

Bag::Bag() { Start(); }

void Bag::Start() {
	maxItems = 1;
	CalculateItems();
	return;
}

//returns numer of items we have
int32  Bag::GetItemCount() {
	CalculateItems();
	return itemCount; 
}

// checks if we have the item we are trying to USE command
bool Bag::TryUseKey()
{
	if (ownedItems.key == 1) {
		return true;
	}
	else return false;
}

bool Bag::TryUseLance()
{
	if (ownedItems.lance == 1) {
		return true;
	}
	else return false;
}

bool Bag::TryUseSnack()
{
	if (ownedItems.snack == 1) {
		return true;
	}
	else return false;
}

//check number of items we have
void  Bag::CalculateItems() {
	itemCount = ownedItems.key + ownedItems.lance + ownedItems.snack;
}


