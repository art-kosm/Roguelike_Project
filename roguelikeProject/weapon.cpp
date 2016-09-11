#include "weapon.h"
#include "actor.h"

Weapon::Weapon(const std::string &name, int damage, int x, int y) :
    Item(name, WEAPON, '(', false, false, x, y),
    damage(damage)
{}

void Weapon::useOn(Actor *actor)
{
    actor->takeDamage(damage);
}

int Weapon::getDamage()
{
    return damage;
}
