#include "MenuHandler.h"

MenuHandler::MenuHandler(GameView* gameView) : Displayable(gameView) {
    NewGameItem* newGame = new NewGameItem("New game");
    QuitItem* quit = new QuitItem("Quit");
    EnglishItem* english = new EnglishItem("English");

    std::vector<std::string> lastDiscoveredLevels = {"Level 0","Level 0","Level 0"};
    std::vector<std::string> labels = {"Slot 1", "Slot 2", "Slot 3"};


    title = new Menu("Title menu");
    saveGame = new Menu("Save game");
    loadGame = new Menu("Load game");
    settings = new Menu("Settings");
    language = new Menu("Language");

    title->addItem(newGame);
    title->addItem(saveGame);
    title->addItem(loadGame);
    title->addItem(settings);
    title->addItem(quit);

    SaveHandler* sh = SaveHandler::getInstance();

    for(unsigned int i(0); i<labels.size(); ++i) {
        std::string path = "save/" + labels[i] + ".save";
        sh->setPath(path);

        std::string json = sh->load();

        // creates a temporary json file for the JsonAccessor
        std::ofstream tempJsonFile;
        std::string tempJsonFilePath = "save/temp.json";

        tempJsonFile.open(tempJsonFilePath);
        tempJsonFile << json << std::endl;
        tempJsonFile.close();

        JsonAccessor accessor;
        accessor.load(tempJsonFilePath);

        lastDiscoveredLevels[i] = labels[i];
        std::string key = "lastdiscoveredlevel";

        if(accessor.canTakeElementFrom(key)) {
            lastDiscoveredLevels[i] = "Level "+ Utils::itos(accessor.getInt(key)+1);
        }

        SaveItem* save = new SaveItem(labels[i]);
        sf::Text* t = save->getText();
        t->setString(lastDiscoveredLevels[i]);
        saveGame->addItem(save);

        LoadItem* load = new LoadItem(labels[i]);
        load->setText(t);
        loadGame->addItem(load);

        accessor.close();

        // remove the temporary json
        if(remove(tempJsonFilePath.c_str()) != 0 ) {
            std::cerr << "Error deleting temporary json" << std::endl;
        }

    }

    saveGame->addItem(title, true);
    loadGame->addItem(title, true);

    settings->addItem(language);
    settings->addItem(title, true);

    language->addItem(english);
    language->addItem(settings, true);

    selectedMenu = title;
}

MenuHandler::~MenuHandler() {
    delete title;

    title = NULL;
    saveGame = NULL;
    loadGame = NULL;
    settings = NULL;
    language = NULL;
}

void MenuHandler::display() {
    selectedMenu->draw(gameView);
}

void MenuHandler::incIndex() {
    selectedMenu->incIndex();
}

void MenuHandler::decIndex() {
    selectedMenu->decIndex();
}

std::pair<GameState, MenuComponent*> MenuHandler::execute() {

    if (!selectedMenu->getSelectedItem()->isAMenu()) {
        return selectedMenu->execute();
    } else {
        std::string label = selectedMenu->getSelectedItem()->getText()->getString();
        if (label == "Title menu") {
            selectedMenu = title;
        } else if (label == "Save game") {
            selectedMenu = saveGame;
        } else if (label == "Load game") {
            selectedMenu = loadGame;
        } else if (label == "Settings") {
            selectedMenu = settings;
        } else if (label == "Language") {
            selectedMenu = language;
        }

     std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::INMENU, selectedMenu);
        return p;
    }
}


void MenuHandler::setNextState(GameState state) {
    this->nextState = state;
}

GameState MenuHandler::getNextState() {
    return this->nextState;
}

Menu* MenuHandler::getTitleMenu() {
    return title;
}
