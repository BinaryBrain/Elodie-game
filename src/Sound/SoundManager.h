#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <string>

#include <SFML/Audio.hpp>

#include "../env.h"
#include "../const.h"

class SoundManager {
public:
    static SoundManager* getInstance();
    static void kill();

    sf::SoundBuffer* getRandomSoundBuffer(SoundType type);
    std::string getPath(SoundType type, int n);

    void play(sf::SoundBuffer* buffer);
    void play(SoundType type);
protected:
private:
    SoundManager();
    ~SoundManager();

    static SoundManager* soundManagerInstance;
    SoundManager& operator= (SoundManager const&);

    std::map< SoundType, std::map< int, sf::SoundBuffer* > > soundBuffers;
    std::map< SoundType, std::pair< std::string, int > > SOUND_TYPE;
};

#endif // SOUNDSYSTEM_H
