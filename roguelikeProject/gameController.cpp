#include <fstream>
#include "gameController.h"
#include "gradalis.h"

GameController::GameController()
{
    initializeColors();

    worldMap = new Map("..//roguelikeProject//world_map.txt");
    worldMap->setName("World map");

    const int initialX = map_x / 2 + 3;
    const int initialY = map_y / 2;
    const int initialHP = 6;
    const int perceptionRadius = 5;

    player = new Actor("player", PLAYER, '@', initialX, initialY, initialHP, perceptionRadius, new PlayerAI(), worldMap);
    player->setSeen(true);
    player->getInventory()->addItem(new Weapon("THE SWORD", 3));
    player->getInventory()->addItem(new Armor("THE ARMOR", 2));

    currentDungeon = nullptr;
    currentMap = worldMap;
    state = playing;

    ui = new UI();
    ui->writeToStatusBar("Press 'h' for help\n");
    ui->updateStatsBar(player);

    score = 0;
}

GameController::~GameController()
{
    delete ui;
    delete worldMap;
    delete player;
}

void GameController::draw()
{
    FieldOfView::calculate(player->getX(), player->getY(), currentMap, player->getPerceptionRadius());
    currentMap->draw(status_bar_y);
    player->draw(status_bar_y);
    ui->refresh();
}

void GameController::processTurn()
{
    ui->clearStatusBar();

    int oldHP = player->getHP();

    char command = getch();
    switch (command)
    {    
    case 2:
        player->move(player->getX(), player->getY() + 1);
        break;

    case 3:
        player->move(player->getX(), player->getY() - 1);
        break;

    case 4:
        player->move(player->getX() - 1, player->getY());
        break;

    case 5:
        player->move(player->getX() + 1, player->getY());
        break;

    case '1':
        player->move(player->getX() - 1, player->getY() + 1);
        break;

    case '2':
        player->move(player->getX(), player->getY() + 1);
        break;

    case '3':
        player->move(player->getX() + 1, player->getY() + 1);
        break;

    case '4':
        player->move(player->getX() - 1, player->getY());
        break;

    case '6':
        player->move(player->getX() + 1, player->getY());
        break;

    case '7':
        player->move(player->getX() - 1, player->getY() - 1);
        break;

    case '8':
        player->move(player->getX(), player->getY() - 1);
        break;

    case '9':
        player->move(player->getX() + 1, player->getY() - 1);
        break;

    case 'e':
        enter();
        break;

    case 'h':
        ui->writeToStatusBar("Commands: "
                             "e -- enter the map, "
                             "i -- browse inventory, "
                             "p -- pick up an item, \n"
                             "t -- talk, "
                             "f -- cast a flood spell, "
                             "q -- quit.\n");
        break;

    case 'i':
        ui->browseInventory(player);
        break;

    case 'p':
        pickUp();
        break;

    case 't':
        talk();
        break;

    case 'f':
        ui->writeToStatusBar(player->castAFlood());
        break;

    case 'q':
        tryToQuit();
        break;

    default:
        break;
    }

    string *message = new string();
    int enemiesKilled = currentMap->processActorsTurns(player, message);
    score += enemiesKilled;
    player->addExp(enemiesKilled);
    if (*message != "")
        ui->writeToStatusBar(*message + "\n");
    int newHP = player->getHP();
    if (newHP < oldHP)
        ui->writeToStatusBar("You were attacked!\n");

    ui->updateStatsBar(player);

    if (!player->isAlive())
    {
        if (player->drowned())
            ui->writeToStatusBar("You drowned!\n");
        state = over;
    }
}

bool GameController::gameIsOver()
{
    return state == over;
}

void GameController::displayScore()
{
    ui->writeToStatusBar("GAME OVER! YOUR SCORE: " + std::to_string(score));

    string path = "..//roguelikeProject//top_score.txt";
    std::ifstream in(path);
    int topScore = 0;
    if (in.is_open())
    {
        in >> topScore;
        in.close();
    }
    ui->writeToStatusBar(". TOP SCORE: " + std::to_string(topScore));

    if (score > topScore)
    {
        std::ofstream out(path);
        out << score;
        out.close();
    }

}

void GameController::initializeColors()
{
    int colorGreen = 1;
    init_pair(colorGreen, COLOR_GREEN, COLOR_BLACK);

    int colorCyan = 2;
    init_pair(colorCyan, COLOR_CYAN, COLOR_BLACK);

    int colorRed = 3;
    init_pair(colorRed, COLOR_RED, COLOR_BLACK);

    int colorBlue = 4;
    init_pair(colorBlue, COLOR_BLUE, COLOR_BLACK);

    int colorYellow = 5;
    init_pair(colorYellow, COLOR_YELLOW, COLOR_BLACK);
}

void GameController::enter()
{
    Entrance *entrance = currentMap->getEntranceOn(player->getX(), player->getY());
    if (entrance == nullptr)
    {
        ui->writeToStatusBar("Unable to enter!\n");
        return;
    }

    Map *previousMap = currentMap;
    currentMap = entrance->getLeadsTo();
    Entrance *pairingEntrance = currentMap->getEntranceByLeadsTo(previousMap);
    player->setMap(currentMap);
    player->move(pairingEntrance->getX(), pairingEntrance->getY());
    ui->writeToStatusBar("You entered " + currentMap->getName() + "!\n");
}

void GameController::pickUp()
{
    if (player->getInventory()->getItems().size() == 15)
    {
        ui->writeToStatusBar("Inventory is full!\n");
        return;
    }

    Item *item = player->pickUpItem();

    if (item == nullptr)
        ui->writeToStatusBar("Unable to pick up!\n");
    else
    {
        ui->writeToStatusBar("Picked up " + item->getName() + "!\n");
        score += 1;
    }
}

void GameController::talk()
{
    int x = player->getX();
    int y = player->getY();

    Actor *trader = getTraderAt(x + 1, y);
    if (trader == nullptr)
        trader = getTraderAt(x, y + 1);
    if (trader == nullptr)
        trader = getTraderAt(x, y - 1);
    if (trader == nullptr)
        trader = getTraderAt(x - 1, y);
    if (trader == nullptr)
        trader = getTraderAt(x + 1, y + 1);
    if (trader == nullptr)
        trader = getTraderAt(x + 1, y - 1);
    if (trader == nullptr)
        trader = getTraderAt(x - 1, y + 1);
    if (trader == nullptr)
        trader = getTraderAt(x - 1, y - 1);

    if (trader != nullptr)
    {
        ui->writeToStatusBar(trader->talk());
        char command = getch();
        switch (command)
        {
        case 'b':
            if (player->getInventory()->getItems().size() == 15)
                ui->writeToStatusBar("Inventory is full!\n");
            else
                ui->browseInventory(trader, player);
            break;

        case 's':
            ui->browseInventory(player, trader);
            break;

        default:
            break;
        }
    }
    else
    {
        Actor *actor = getActorAt(x + 1, y);
        if (actor == nullptr)
            actor = getActorAt(x, y + 1);
        if (actor == nullptr)
            actor = getActorAt(x, y - 1);
        if (actor == nullptr)
            actor = getActorAt(x - 1, y);
        if (actor == nullptr)
            actor = getActorAt(x + 1, y + 1);
        if (actor == nullptr)
            actor = getActorAt(x + 1, y - 1);
        if (actor == nullptr)
            actor = getActorAt(x - 1, y + 1);
        if (actor == nullptr)
            actor = getActorAt(x - 1, y - 1);

        if (actor != nullptr)
            ui->writeToStatusBar(actor->talk());
        else
            ui->writeToStatusBar("Unable to talk!\n");
    }
}

Actor *GameController::getTraderAt(int x, int y)
{
    Actor *actor = currentMap->getActorOn(x, y);
    if (actor != nullptr)
        if (actor->getType() == TRADER)
            return actor;

   return nullptr;
}

Actor *GameController::getActorAt(int x, int y)
{
    Actor *actor = currentMap->getActorOn(x, y);
    if (actor != nullptr)
        if (actor->getType() == CITIZEN || HUMANOID)
            return actor;

   return nullptr;
}

void GameController::tryToQuit()
{
    ui->writeToStatusBar("Quit? (y/n)");
    while (true)
    {
        char command = getch();
        switch (command)
        {
        case 'y':
            state = over;
            ui->clearStatusBar();
            return;

        case 'n':
            ui->clearStatusBar();
            return;

        default:
            break;
        }
    }
}
