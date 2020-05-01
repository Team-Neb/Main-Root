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
        void actions();                      // NOT USED

        GLuint dropTex;                         // handler Texture;

        bool getHitStatus();                    // NOT USED
        int getHealth();                        // NOT USED
        void swordCollisionCheck(float, int);   // NOT USED
        void placeEnemyRandom();                // NOT USED


        int getAction();
        void setAction(int);

    protected:

    private:
        float xPos, yPos, zPos;                 // Placement of object
        float xSize, ySize;                     // Scaling factor
        float rotateX, rotateY, rotateZ;        // Rotations for animation

        int frames;                             // Number of frames
        int action;                             // To determine if the object should be drawn on the screen

        float xMin, yMin, xMax, yMax;           // boundaries of the texture

        Timer *TE = new Timer();                // NOT USED
        void checkCollision(float);             // NOT USED
};

#endif // GAMEDROPS_H
