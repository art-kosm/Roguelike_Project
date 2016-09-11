#include <limits>
#include "actor.h"

Actor::Actor() : hp(1), mp(0), maxHP(8), money(0), level(1), exp(0), perceptionRadius(5), mind(nullptr),
                 locatedOn(nullptr), status(ALIVE), inventory(new Inventory)
{}

Actor::Actor(const string &name, Type type, char symbol, int x, int y, int hp,
             int perceptionRadius, AI *mind, Map *locatedOn) :
    Tile(name, type, symbol),
    hp(hp),
    mp(0),
    maxHP(8),
    money(0),
    level(1),
    exp(0),
    x(x),
    y(y),
    perceptionRadius(perceptionRadius),
    mind(mind),
    locatedOn(locatedOn),
    status(ALIVE),
    inventory(new Inventory)
{
    if (type == TRADER)
        money = std::numeric_limits<int>::max();
}

void Actor::draw(int indent)
{
    if (!isSeen)
        return;

    if (type == HUMANOID)
        attron(COLOR_PAIR(1));

    if (type == CITIZEN)
        attron(COLOR_PAIR(3));

    if (type == DRAGON)
        attron(COLOR_PAIR(5));

    mvaddch(y + indent, x, symbol);

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(5));
}

int Actor::getHP()
{
    return hp;
}

int Actor::getMP()
{
    return mp;
}

int Actor::getMoney()
{
    return money;
}

int Actor::getLevel()
{
    return level;
}

int Actor::getExp()
{
    return exp;
}

int Actor::getX()
{
    return x;
}

int Actor::getY()
{
    return y;
}

int Actor::getPerceptionRadius()
{
    return perceptionRadius;
}

int Actor::askPrice(Item *item)
{
    return mind->askPrice(item);
}

void Actor::takeTurn(Actor *player)
{
    mind->takeTurn(this, player);
}

void Actor::move(int x, int y)
{
    if (x > map_x - 1 || x < 0 || y > map_y - 1 || y < 0)
        return;

    if (!locatedOn->tileIsPassable(x, y))
        return;

    if (locatedOn->isWater(x, y))
    {
        if (type == PLAYER)
            status = DROWNED;
        else
            return;
    }

    Actor *actor = locatedOn->getActorOn(x, y);
    if (actor != nullptr)
    {
        if (type == PLAYER || actor->type == PLAYER)
            attack(actor);

        if (!locatedOn->isEntrance(x, y))
            return;
    }

    this->x = x;
    this->y = y;
}

void Actor::setMap(Map *map)
{
    locatedOn = map;
}

Map *Actor::getMap()
{
    return locatedOn;
}

int Actor::getMaxHP()
{
    return maxHP;
}

void Actor::setAI(AI *mind)
{
    delete this->mind;
    this->mind = mind;
}

void Actor::takeDamage(int damage)
{
    Armor *armor = inventory->getEquippedArmor();
    if (armor != nullptr)
        hp -= damage / armor->getDamageReduction();
    else
        hp -= damage;
    if (hp <= 0)
        status = DEAD;
}

void Actor::restoreHP(int healed)
{
    hp += healed;
    if (hp > maxHP)
        hp = maxHP;
}

bool Actor::isAlive()
{
    return status == ALIVE;
}

Inventory *Actor::getInventory()
{
    return inventory;
}

Item *Actor::pickUpItem()
{
    Item *item = locatedOn->getItemAt(x, y);
    if (item == nullptr)
        return nullptr;

    locatedOn->removeItem(item);
    inventory->addItem(item);
    return item;
}

void Actor::dropItem(Item *item)
{
    if (!inventory->hasItem(item))
        return;
    item->setX(x);
    item->setY(y);
    locatedOn->addItem(item);
    inventory->removeItem(item);
}

void Actor::attack(Actor *actor)
{
    Weapon *weapon = inventory->getEquippedWeapon();
    if (weapon != nullptr)
        weapon->useOn(actor);
}

void Actor::takeMoney(int money)
{
    this->money -= money;
}

void Actor::giveMoney(int money)
{
    this->money += money;
}

void Actor::addExp(int exp)
{
    this->exp += exp;
    if (this->exp >= level * 10)
    {
        level++;
        mp++;
        this->exp = 0;
        maxHP = level * 8;
    }
}

string Actor::talk()
{
    return mind->talk();
}

bool Actor::drowned()
{
    return status == DROWNED;
}

string Actor::castAFlood()
{
    if (mp < 1)
        return "Not enough MP!\n";

    mp--;
    locatedOn->flood();
    return "A flood spell is casted.";
}
