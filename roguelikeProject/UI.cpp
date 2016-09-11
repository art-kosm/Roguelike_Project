#include "UI.h"

UI::UI()
{
    statusBar = createNewWindow(status_bar_y, status_bar_x, 0, 0);
    statsBar = createNewWindow(stats_bar_y, stats_bar_x, 0, term_y - stats_bar_y);
}

UI::~UI()
{
    destroyWindow(statusBar);
    destroyWindow(statsBar);
}

void UI::refresh()
{
    wrefresh(statusBar);
    wrefresh(statsBar);
}

void UI::writeToStatusBar(const std::string &message)
{
    wprintw(statusBar, message.c_str());
    wrefresh(statusBar);
}

void UI::writeToStatsBar(const std::string &message)
{
    wprintw(statsBar, message.c_str());
    wrefresh(statsBar);
}

void UI::clearStatusBar()
{
    werase(statusBar);
}

void UI::clearStatsBar()
{
    werase(statsBar);
}

void UI::browseInventory(Actor *actor, Actor *partner)
{
    scr_dump("temp.scr");
    openInventoryWindow();
    Inventory *inventory = actor->getInventory();
    vector<Item *> items = inventory->getItems();
    printInventory(actor);
    clearStatusBar();
    writeToStatusBar("Press 'h' for help.\n");

    bool finished = false;
    Item *currentItem = nullptr;
    if (items.size() > 0)
        currentItem = items.front();
    int currentItemPos = 0;
    while (!finished)
    {
        clearStatusBar();
        wattron(inventoryWindow, A_UNDERLINE);
        if (currentItem != nullptr)
            mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
        wrefresh(inventoryWindow);
        wattroff(inventoryWindow, A_UNDERLINE);

        int command = getch();
        switch (command)
        {
            case KEY_UP:
                if (currentItemPos == 0)
                    break;
                mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
                currentItemPos--;
                currentItem = items.at(currentItemPos);
                break;

            case KEY_DOWN:
                if ((unsigned) currentItemPos == items.size() - 1)
                    break;
                mvwprintw(inventoryWindow, currentItemPos + 1, 4, items.at(currentItemPos)->getName().c_str());
                currentItemPos++;
                currentItem = items.at(currentItemPos);
                break;

            case 'w':
                if (currentItem != nullptr && partner == nullptr)
                {
                    clearStatusBar();
                    if (currentItem->getType() != WEAPON)
                    {
                        writeToStatusBar("This is not a weapon!\n");
                        break;
                    }

                    if (inventory->getEquippedWeapon() != currentItem)
                    {
                        inventory->unequipWeapon();
                        inventory->equipWeapon(dynamic_cast<Weapon *>(currentItem));
                        writeToStatusBar("Equipped " + currentItem->getName() + "!\n");
                    }
                    else
                    {
                        inventory->unequipWeapon();
                        writeToStatusBar("Unequipped " + currentItem->getName() + "!\n");
                    }

                }
                break;

            case 'a':
                if (currentItem != nullptr && partner == nullptr)
                {
                    if (currentItem->getType() != ARMOR)
                    {
                        writeToStatusBar("This is not an armor!\n");
                        break;
                    }

                    if (inventory->getEquippedArmor() != currentItem)
                    {
                        inventory->unequipArmor();
                        inventory->equipArmor(dynamic_cast<Armor *>(currentItem));
                        writeToStatusBar("Equipped " + currentItem->getName() + "!\n");
                    }
                    else
                    {
                        inventory->unequipArmor();
                        writeToStatusBar("Unequipped " + currentItem->getName() + "!\n");
                    }
                }
                break;

            case 'd':
                if (currentItem != nullptr && partner == nullptr)
                {
                    dropAnItem(actor, currentItem);
                    items = inventory->getItems();
                    currentItemPos = 0;
                    if (items.size() > 0)
                        currentItem = items.front();
                    else
                        currentItem = nullptr;
                }
                break;

            case 't':
                if (currentItem != nullptr)
                {
                    int partnerMoney = partner->getMoney();
                    int actorPrice = actor->askPrice(currentItem);

                    if (partnerMoney >= actorPrice)
                    {
                        dropAnItem(actor, currentItem);
                        actor->giveMoney(actorPrice);
                        currentItem->setX(partner->getX());
                        currentItem->setY(partner->getY());
                        partner->pickUpItem();
                        partner->takeMoney(actorPrice);

                        writeToStatusBar("Traded " + currentItem->getName() + "!\n");
                        if (actor->getType() == PLAYER)
                            updateStatsBar(actor);
                        else
                            updateStatsBar(partner);

                        items = inventory->getItems();
                        currentItemPos = 0;
                        if (items.size() > 0)
                            currentItem = items.front();
                        else
                            currentItem = nullptr;
                    }
                }
                break;

            case 'h':
                writeToStatusBar("Commands: "
                                 "a -- put on / unequip the armor, "
                                 "w -- take / unequip the weapon, \n"
                                 "d -- drop, "
                                 "t -- trade, "
                                 "p -- drink a potion, "
                                 "g -- use a ???, "
                                 "q -- quit.\n");
                break;

            case 'p':
                if (currentItem != nullptr && partner == nullptr)
                {
                    if (currentItem->getType() != POTION)
                    {
                        clearStatusBar();
                        writeToStatusBar("This is not a potion!\n");
                        break;
                    }
                    currentItem->useOn(actor);
                    clearStatusBar();
                    writeToStatusBar("Drank a " + currentItem->getName() + "!\n");
                    updateStatsBar(actor);

                    inventory->removeItem(currentItem);
                    printInventory(actor);

                    items = inventory->getItems();
                    currentItemPos = 0;

                    if (items.size() > 0)
                        currentItem = items.front();
                    else
                        currentItem = nullptr;
                }
                break;

            case 'g':
                if (currentItem != nullptr && partner == nullptr)
                {
                    if (currentItem->getType() != GRADALIS)
                        break;
                    currentItem->useOn(actor);
                    finished = true;
                }
                break;

            case 'q':
                finished = true;
                break;

            default:
                break;
        }
        wrefresh(inventoryWindow);
    }

    destroyWindow(inventoryWindow);
    scr_restore("temp.scr");
    remove("temp.scr");
}

void UI::openInventoryWindow()
{
    inventoryWindow = createNewWindow(term_y / 3, term_x / 3, term_y / 2 - term_y / 3, term_x / 2 - term_x / 3);
    box(inventoryWindow, 0, 0);
}

WINDOW *UI::createNewWindow(int height, int width, int start_x, int start_y)
{
    WINDOW *window;

    window = newwin(height, width, start_y, start_x);
    wrefresh(window);

    return window;
}

void UI::destroyWindow(WINDOW *window)
{
    wrefresh(window);
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    delwin(window);
}

void UI::printInventory(Actor *actor)
{
    werase(inventoryWindow);
    box(inventoryWindow, 0, 0);
    Inventory *inventory = actor->getInventory();
    vector<Item *>items = inventory->getItems();
    int size = items.size();
    for (int i = 0; i < size; i++)
    {
        mvwprintw(inventoryWindow, i + 1, 1, (std::to_string(i + 1) + ".").c_str());
        mvwprintw(inventoryWindow, i + 1, 4, items.at(i)->getName().c_str());
    }
    wrefresh(inventoryWindow);
}

void UI::dropAnItem(Actor *actor, Item *currentItem)
{
    Inventory *inventory = actor->getInventory();

    if (currentItem == inventory->getEquippedWeapon())
        actor->getInventory()->unequipWeapon();

    if (currentItem == inventory->getEquippedArmor())
        actor->getInventory()->unequipArmor();

    actor->dropItem(currentItem);
    printInventory(actor);
}

void UI::updateStatsBar(Actor *player)
{
    clearStatsBar();
    writeToStatsBar("HP:" + std::to_string(player->getHP()) + "/" + std::to_string(player->getMaxHP()));
    writeToStatsBar(", MP:" + std::to_string(player->getMP()));
    writeToStatsBar(", LEVEL: " + std::to_string(player->getLevel()));
    writeToStatsBar(", GOLD: " + std::to_string(player->getMoney()));
}
