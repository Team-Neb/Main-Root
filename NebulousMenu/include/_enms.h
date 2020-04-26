#ifndef _ENMS_H
#define _ENMS_H

#include <GL/gl.h>
#include <textureLoader.h>
#include <Timer.h>
#include <windows.h>
#include <math.h>

#define PI 3.14159
#define gravity 9.81
class _enms
{
    public:
        _enms();
        virtual ~_enms();

        void drawEnemy();                       // draw enemy object
        void placeEnemy(float, float, float);   // place enemy
        void initEnemy(GLuint);                 // initialize enemy
        void actions();                         // movement and actions

        bool isEnemyLive();                     // status of enemy
        GLuint EnemyTex;                        // handler Texture;

        float xPos, yPos, zPos;                 // Placement
        float xSize, ySize;                     // Scaling factor
        float rotateX, rotateY, rotateZ;        // Rotations

        int frames;                             // Number of frames

        float xMove;                            // moving speed on x axis
        int action;                             // to make action for enemy

        Timer *TE = new Timer();

        float theta, v, t;                      // angle, velocity, time;


    protected:

    private:
        float xMin, yMin, xMax, yMax;
};

#endif // _ENMS_H
