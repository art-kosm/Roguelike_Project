#include "weapon.h"
#include "actor.h"

Weapon::Weapon(const std::string &name, int damage, int x, int y) :
	Item(name, "weapon", '(', false, false, x, y),
	damage(damage)
{

}

void Weapon::useOn(Actor *actor)
{
	actor->takeDamage(damage);
}

