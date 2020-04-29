#ifndef _NPC_H
#define _NPC_H

#include <GL/gl.h>
#include <textureLoader.h>
#include <Timer.h>
#include <windows.h>
#include <math.h>


class _npc
{
    public:
        _npc();
        virtual ~_npc();

        void drawEnemy();                       // draw enemy object
        void placeEnemy(float, float, float);   // place enemy
        void initEnemy(GLuint);                 // initialize enemy
        void actions(float);                    // movement and actions

        GLuint npcTex;                        // handler Texture;


        float xPos, yPos, zPos;                 // Placement
        float xSize, ySize;                     // Scaling factor
        float rotateX, rotateY, rotateZ;        // Rotations

        int frames;                             // Number of frames

        int action;                             // to make action for enemy

        Timer *TE = new Timer();

        bool getHitStatus();
        int getHealth();
        void swordCollisionCheck(float, int);
        void placeEnemyRandom();

    protected:

    private:

        float xMin, yMin, xMax, yMax;

        int enemyHealth;
        bool enemyHit;
        int previousAction;

        float XPOS_MAX;
        float XPOS_MIN;
        void checkCollision(float);

};

#endif // _NPC_H
