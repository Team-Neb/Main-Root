#ifndef GLSCENE_H
#define GLSCENE_H
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include <StateManager.h>
#include <Timer.h>
#include <vector>
#include <Parallax.h>
#include <GameDrops.h>
#include <textureLoader.h>
#include <_npc.h>



class GLScene
{
    public:
        GLScene();                  //constructor
        virtual ~GLScene();         //Deconstructor
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei,GLsizei);
        GameStates sendState();

        int winMsg(HWND, UINT, WPARAM, LPARAM);
        float screenWidth, screenHeight;


    protected:

    private:

        /****************** RICHARD'S CODE *************************************/
        void spawnEnemies(int);                     // Spawn enemies, type of enemies depend on the current level
        int level;                                  // For keeping track of level - level switching/type of enemy to spawn
        bool is_level_complete;                     // To determine whether to move onto next level

        Timer *cinematicTimer = new Timer();        // To control how often the intro cinematic scene changes
        vector<Parallax *> cinematic;               // to hold all the cinematic scenes
        void initCinematic();                       // Add Parallax objects into vector and apply image texture
        int cinematicFrames;                        // How many unique frames are in the cinematic
        int currentCinematicFrame;                  // Which scene to display for the cinamtic intro

        void spawnGameDrop(float, float, float, int);    // Create and draw GameDrops onto the screen



        vector<GameDrops *>drops;
        vector<textureLoader *> dropTextures;
        vector<_npc *> enemyType2;
        vector<textureLoader *> enemyTextures;
        vector<Parallax *> levels;

        void initDropTextures();
        void initEnemyTextures();
        void initLevelScenes();

        void resetLevel(int);
        void resetGame();

        void drawDrops();

        void updateDrops();
        void updateEnemiesAction();
        void destroyEnemies();

        /**************** END OF RICHARD'S CODE *******************************/

};

#endif // GLSCENE_H
