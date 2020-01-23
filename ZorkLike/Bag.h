#pragma once
#include <string>

// To make it Unreal Friendly as I am used to
using FString = std::string;
using int32 = int;

// objects in the bag
struct BagItems
{
	int32 key = 0;
	int32 lance = 0;
	int32 snack = 0;
};

class Bag
{
public:
	Bag(); // constructor
	BagItems ownedItems;
	int32 maxItems = 1;
	void Start();
	int32 GetItemCount();
	bool TryUseKey();
	bool TryUseLance();
	bool TryUseSnack();
	
private:
	void CalculateItems();
	int32 currentItems;
	int32 itemCount = 0;
};

