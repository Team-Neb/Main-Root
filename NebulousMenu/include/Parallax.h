#ifndef PARALLAX_H
#define PARALLAX_H
#include <iostream>
#include <windows.h>
#include <textureLoader.h>

using namespace std;

class Parallax
{
    public:
        Parallax();
        virtual ~Parallax();

        void drawSquare(float, float); // drawing a square
        void drawPopUp(float, float); // drawing a popup
        void parallaxInit(char *); // initialize with texture
        void scroll(string, float); // to scroll the background

        float xMax, yMax, xMin, yMin;
        textureLoader *bTexture = new textureLoader();



        //float screenWidth, screenHeight;



    protected:

    private:
};

#endif // PARALLAX_H
