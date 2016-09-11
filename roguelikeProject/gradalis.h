#include "item.h"

class Gradalis : public Item
{
public:
    Gradalis(const string &name, int x = 0, int y = 0);
    void useOn(Actor *actor);
};
