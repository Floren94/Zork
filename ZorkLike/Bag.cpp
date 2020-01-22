#include "Bag.h"

using int32 = int;

Bag::Bag() { Start(); }

int32  Bag::GetItemCount() {
	CalculateItems();
	return itemCount; 
}

bool Bag::TryUseKey()
{
	if (ownedItems.key == 1) {
		return true;
	}
	else return false;
}

void Bag::Start() {
	maxItems =  1;
	CalculateItems();
	return;
}

void  Bag::CalculateItems() {
	itemCount = ownedItems.key + ownedItems.lance + ownedItems.snack;
}

void Bag::KeyObtained() {
	ownedItems.key++;
	CalculateItems();
}

