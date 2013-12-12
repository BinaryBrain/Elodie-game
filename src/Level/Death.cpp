#include "Death.h"

Death::Death(GameView * view, bool isMute) : Displayable(view) {
    float viewX(gameView->getWindow()->getSize().x);
    float viewY(gameView->getWindow()->getSize().y);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    font = new sf::Font();
    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");
    text = new sf::Text("You woke up ... ", *font);
    text->setCharacterSize(30);

    texture.loadFromFile("assets/img/sprites/dreamover.png");
    elo.setTexture(texture);
    elo.setScale(GAMEOVER_ELOSCALE, GAMEOVER_ELOSCALE);
    elo.setPosition(WINDOW_WIDTH/2 - (elo.getLocalBounds().width*GAMEOVER_ELOSCALE)/2, WINDOW_HEIGHT/2 - (elo.getLocalBounds().height*GAMEOVER_ELOSCALE)/2);

    text->setPosition(WINDOW_WIDTH/2 - text->getLocalBounds().width/2, WINDOW_HEIGHT/2 + (elo.getLocalBounds().height*GAMEOVER_ELOSCALE)/2 + GAMEOVER_INTERSPACE);


    view->addView(ViewLayer::DEATH, this);

    if (!music.openFromFile(MUSIC_PATH+"/"+DEATH_MUSIC)) {
        // TODO Handle error
    } else {
        music.setLoop(true);

        if(!isMute) {
            music.play();
        }
    }

}

Death::~Death() {
    delete font;
    delete text;
}

void Death::display() {
    gameView->addDrawable(ViewLayer::DEATH, &rect);
    gameView->addDrawable(ViewLayer::DEATH, text);
    gameView->addDrawable(ViewLayer::DEATH, &elo);
}
