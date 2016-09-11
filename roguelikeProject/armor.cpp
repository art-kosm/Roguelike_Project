#include "armor.h"

Armor::Armor(const string &name, int damageReduction, int x, int y) :
    Item(name, ARMOR, ']', false, false, x, y),
    damageReduction(damageReduction)
{}

void Armor::useOn(Actor *)
{}

int Armor::getDamageReduction()
{
    return damageReduction;
}
