#include "Level.h"

Level::Level() {

}

Level::Level(std::string filename) {
    loadLevel(filename);
}

Level::~Level() {
    //dtor
}

// Load a level from the file system
void Level::loadLevel(std::string filename) {
    std::string levelSource = FileHandler::getContent(filename);

    Mapper::parse(levelSource, tiles, entities);
    Mapper::beautify(tiles);
}

// Ask the given view to draw a Level frame
void Level::draw(GameView* view) {
    for(unsigned int y=0; y<tiles.size(); y++) {
        for(unsigned int x=0; x<tiles[y].size(); x++) {
            if(tiles[y][x]) {
                tiles[y][x]->setPosition(x*32, y*32);
                view->addDrawable(tiles[y][x]);
            }
        }
    }

    for(EntityMap::iterator entity_ptr = entities.begin(); entity_ptr != entities.end(); ++entity_ptr) {
        Entity* entity = entity_ptr->second;
        sf::Sprite* sprite = entity->getSprite();

        if(sprite) {
            view->addDrawable(sprite);
        }
    }
}
