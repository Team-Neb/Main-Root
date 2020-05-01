#ifndef GLSCENE_H
#define GLSCENE_H
#include <string.h>
#include <windows.h>
#include <GL/glut.h>
#include <StateManager.h>
#include<_Sound.h>



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
};

#endif // GLSCENE_H
