#include "traderAI.h"
#include "potion.h"

TraderAI::TraderAI()
{}

void TraderAI::takeTurn(Actor *actor, Actor *player)
{
    CitizenAI::takeTurn(actor, player);

    Inventory *inventory = actor->getInventory();
    vector<Item *> items = inventory->getItems();
    int inventorySize = items.size();
    if (inventorySize != 1 || items.at(0)->getType() != POTION)
    {
        for (int i = 0; i < inventorySize; i++)
            inventory->removeItem(items.at(i));
        inventory->addItem(new Potion());
    }
}

int TraderAI::askPrice(Item *)
{
    return 5;
}

string TraderAI::talk()
{
    return "'Wanna buy or sell something?'\n";
}
