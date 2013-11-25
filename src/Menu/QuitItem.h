#ifndef QUITITEM_H
#define QUITITEM_H

#include "../env.h"
#include "MenuItem.h"

class QuitItem : public MenuItem {
public:
    QuitItem(std::string label);
    virtual ~QuitItem();

    GameState execute();
private:
};

#endif // QUITITEM_H