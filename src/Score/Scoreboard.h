#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../Displayable/Displayable.h"
#include "../Game/Game.h"
#include "../Game/GameView.h"
#include "../Score/ScoreManager.h"
#include "../Utils/Utils.h"
#include "../const.h"
#include "../font.h"

#include <SFML/Audio.hpp>

class Scoreboard : public Displayable {
public:
    Scoreboard(GameView* view);
    virtual ~Scoreboard();

    void display();

private:
    sf::RectangleShape rect;
    sf::Text damagesTakenText;
    sf::Text enemiesKilledText;
    sf::Text pointsText;
};

#endif // SCOREBOARD_H