#ifndef GAMEDROPS_H
#define GAMEDROPS_H

#include <GL/gl.h>
#include <textureLoader.h>
#include <Timer.h>
#include <windows.h>
#include <math.h>

class GameDrops
{
    public:
        GameDrops();
        virtual ~GameDrops();
        void drawDrop();                        // draw GameDrop object
        void placeDrop(float, float, float);    // place GameDrop object
        void initDrop(GLuint);                  // initialize Drop
        void actions();

        GLuint dropTex;                         // handler Texture;

        void checkPlayerPickup(float, int);


        int getAction();
        void setAction(int);
        int getDropType();
        void setDropType(int);

    protected:

    private:
        float xPos, yPos, zPos;                 // Placement of object
        float xSize, ySize;                     // Scaling factor
        float rotateX, rotateY, rotateZ;        // Rotations for animation

        int frames;                             // Number of frames
        int action;                             // To determine if the object should be drawn on the screen

        float xMin, yMin, xMax, yMax;           // boundaries of the texture

        Timer *TE = new Timer();

        int dropType;                           // Type of drop - defined as 1, 2, or 3
};

#endif // GAMEDROPS_H
