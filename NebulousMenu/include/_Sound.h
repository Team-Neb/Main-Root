#ifndef _SOUND_H
#define _SOUND_H

#include<SNDS/irrKlang.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
using namespace irrklang;

class _Sound
{
    public:
        _Sound();
        virtual ~_Sound();

        _Sound(char* File);
        _Sound* Audio;

        ISoundEngine *engine = createIrrKlangDevice(); // there is more options

        void playMusic(char *);
        void playSound(char *);
        void pauseSound(char *);

        //////////////////////////////////

        void play();
        void stop();
        void setVolume(float fVol);

        int initSounds();



    protected:

    private:
};

#endif // _SOUND_H
