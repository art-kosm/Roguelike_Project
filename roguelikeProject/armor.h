#pragma once

#include "item.h"

class Armor : public Item
{
public:
	Armor(const std::string &name, int damageReduction = 0, int x = 0, int y = 0);
	void useOn(Actor *actor);

private:
	int damageReduction;
};

