#include "_Sound.h"

_Sound::_Sound()
{
    //ctor
}

_Sound::~_Sound()
{
    //dtor
    engine -> drop();
}

void _Sound::playMusic(char* File)
{
    engine-> play2D(File, true);
}

void _Sound::playSound(char* File)
{
    if(!engine ->isCurrentlyPlaying(File))
    engine-> play2D(File, false,false);
}

void _Sound::pauseSound(char* File)
{

    engine-> play2D(File, true, false);
}

int _Sound::initSounds()
{
    if(!engine){
    cout<< "Errors with the sound engine! \n";
    return 0;
    }
    return 1;
}
