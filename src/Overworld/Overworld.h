#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Game/Game.h"
#include "../Entity/Elodie.h"
#include "../Json/JsonAccessor.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

class Game;
class Elodie;

class Overworld : public Displayable
{
public:
    Overworld(GameView& gameView, bool muted);
    virtual ~Overworld();

    Elodie& getElodie();
    int getCurrentEnv();
    int moveUp();
    int moveDown();
    int moveRight();
    int moveLeft();
    void evolve(std::vector<int> succLevel);
    void display();
    void resetPos();
    void playMusic();
    void stopMusic();

    std::vector<int> getLevelToLoad();
    const std::vector<int>& getLevelsPerSubworld();

    const std::vector<int>& getState();
    void setState(std::vector<int> state);
    void switchOverworlds();//TODO : REMOVE ME (or pass me private)
    void setPosInPath(int pos = 0);
    void setToLevel(std::vector<int> level);
    sf::Music& getMusic();

    void printCoord(std::vector<int> coord); //TODO : REMOVE ME (or pass me private)

private:
    enum states
    {
        UNIL1 = 0,
        UNIL2 = 1,
        CASTLE1 = 2,
        CASTLE2 = 3,
        VOLCANO1 = 4,
        VOLCANO2 = 5,
        FRELJORD1 = 6,
        FRELJORD2 = 7
    };

    sf::RectangleShape fader;

    std::vector<int> currentState;
    std::vector<std::vector<sf::Sprite>> overworldSprites;
    std::vector<std::vector<sf::Texture*>> overworldTextures;
    std::vector<std::vector<sf::VertexArray*>> paths;
    std::vector<std::vector<sf::Sprite*>> pathSprites;
    std::vector < std::vector< std::vector<int> > >levelPos;
    std::vector< std::vector<int> > inPos;
    std::vector< std::vector<int> > outPos;
    std::vector< std::string > trigIn;
    std::vector< std::string > trigOut;
    std::vector<int> levelsPerSubworld;
    std::vector<int> envsPerSubworld;
    std::vector< std::vector<int> > envs;

    int subWorldsNumber ;

    unsigned int curSubWorld = 0;

    size_t curPosInPath = 0;

    std::vector<std::vector<sf::Sprite*>> levelSpotSprites;

    Elodie* elodie;
    sf::Music music;

    int getLevelFromPath();
};

#endif // OVERWORLD_H
