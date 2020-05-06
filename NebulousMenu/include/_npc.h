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

        GLuint npcTex;                          // handler Texture;


        float xPos, yPos, zPos;                 // Placement
        float xSize, ySize;                     // Scaling factor
        float rotateX, rotateY, rotateZ;        // Rotations

        int frames;                             // Number of frames
        int action;                             // to make action for enemy

        Timer *TE = new Timer();                // Control enemy animation and update position

        bool getHitStatus();                    // Determine if enemy has collided
        void swordCollisionCheck(float, int);   // Check if enemy has collided with player sword
        void placeEnemyRandom();                // Randomly place enemy on screen

    protected:

    private:

        float xMin, yMin, xMax, yMax;           // texture variables

        int enemyHealth;                        // How much health enemy has
        bool enemyHit;                          // Flag
        int previousAction;                     // Record what the enemy object was doing before collision

        float XPOS_MAX;                         // Screen boundaries - how far the enemy will go
        float XPOS_MIN;                         // Screen boundaries - how far the enemy will go
        void checkCollision(float);             // Check if there has been a collision with player based on movement

};

#endif // _NPC_H
