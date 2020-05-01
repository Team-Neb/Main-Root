#ifndef GLSCENE_H
#define GLSCENE_H
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include <StateManager.h>
#include <Timer.h>
#include <vector>
#include <Parallax.h>



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
        void spawnEnemies(int);     // Spawn enemies at start of game or every new level
        int level;                  // For level switching
        bool is_level_complete;     // To determine whether to move onto next level

        Timer *cinematicTimer = new Timer();        // for intro cinematic
        vector<Parallax *> cinematic;               // to hold all the cinematic scenes
        void initCinematic();
        int cinematicFrames;                        // How many unique frames are in the cinematic
        int currentCinematicFrame;                  // Which scene to display

};

#endif // GLSCENE_H
