#include "inventory.h"

Inventory::Inventory() : equippedWeapon(nullptr), equippedArmor(nullptr)
{

}

void Inventory::addItem(Item *item)
{
	items.push_back(item);
}

void Inventory::equipWeapon(Weapon *weapon)
{
	equippedWeapon = weapon;
}

void Inventory::equipArmor(Armor *armor)
{
	equippedArmor = armor;
}

void Inventory::removeItem(Item *item)
{
	for (int i = 0; (unsigned)i < items.size(); i++)
		if (items.at(i) == item)
			items.erase(items.begin() + i);
}

bool Inventory::hasItem(Item *item)
{
	for (int i = 0; (unsigned)i < items.size(); i++)
		if (items.at(i) == item)
			return true;
	return false;
}

vector<Item *> Inventory::getItems()
{
	return items;
}

