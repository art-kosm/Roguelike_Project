#include "armor.h"

Armor::Armor(const string &name, int damageReduction, int x, int y) :
	Item(name, "armor", ']', false, false, x, y),
	damageReduction(damageReduction)
{

}

void Armor::useOn(Actor *actor)
{

}

