
#include <GLLight.h>
#include "GLScene.h"
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<player.h>
#include <Objects.h>
#include <_enms.h>
#include <_checkCollision.h>
#include<_Sound.h>

Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *plx = new Parallax();
Parallax *pause = new Parallax();
player *ply = new player();
StateManager *stateManager = new StateManager;
Parallax *tlt = new Parallax();
Parallax *menu = new Parallax();
Parallax *help = new Parallax();
Parallax *storyOne = new Parallax();
Parallax *storyTwo = new Parallax();
Parallax *storyThree = new Parallax();
Parallax *storyFour = new Parallax();
Parallax *storyFive = new Parallax();
Parallax *continueScreen = new Parallax();




// implement story slides thru parallax

_checkCollision *hit = new _checkCollision();

textureLoader *enmsTex = new textureLoader();
_enms enms[10];

// Sound adding

_Sound *snds = new _Sound();


GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH); // For better animation transitions
    glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f); // Input the background color
    glClearDepth(1.0f);      // To choose what is in the front and in the back like layers
    glEnable(GL_DEPTH_TEST); // To calculate the depth perception
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_COLOR_MATERIAL); // This is for rendering the base color of an object (glColor3f)
    GLLight Light(GL_LIGHT0);
    Light.setLight(GL_LIGHT0); // create light instance

   // images to import for game states
    ply->playerInit("images/walkAndattack.png");
    plx->parallaxInit("images/par.png");
    pause->parallaxInit("images/pause.jpg");
    tlt->parallaxInit("images/title.png");
    menu->parallaxInit("images/FrontMenu.jpg");
    help->parallaxInit("images/help.jpg");
    enmsTex->loadTexture("images/mon.png");

    storyOne->parallaxInit("images/scene01.png");
    storyTwo->parallaxInit("images/scene02.jpg");
    storyThree->parallaxInit("images/scene03.png");
    storyFour->parallaxInit("images/scene04.png");
    storyFive->parallaxInit("images/scene05.png");

    // Here is where we'll load story slides for the narrative


    for(int i = 0; i < 10; i++){
        enms[i].initEnemy(enmsTex->tex);
        enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5, -0.5, -2.0);
        enms[i].xSize = enms[i].ySize = float(rand()%12)/65.0;
    }

    snds->initSounds();
    snds->playMusic("sounds/WiiTheme.mp3"); // Switch back to sounds/NebulousTheme.mp3


    return true;

}

//function for main to exit game when escape is pressed on certain game states
GameStates GLScene::sendState(){
    return stateManager->_gameState;}


GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    stateManager->_gameState;
    //  State manager used to manipulate game states
    switch(stateManager->_gameState){
    case LANDING:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        tlt->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case MENU:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        menu->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case HELP:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        help->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case STORY1:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        storyOne->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case STORY2:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        storyTwo->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case STORY3:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        storyThree->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case STORY4:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        storyFour->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case STORY5:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        storyFive->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case GAME:

        glPushMatrix();
        plx -> drawSquare(screenHeight, screenWidth);
        glPopMatrix();

        glPushMatrix();
            glTranslated(ply->xPos, ply->yPos , ply->zPos);
            ply->drawPlayer(); // render character
            ply->playerActions(); // render actions
        glPopMatrix();


        for(int i = 0; i < 10; i++){
            if(enms[i].xPos< -2.0){
                enms[i].action = 0;
                enms[i].xMove= 0.005;
                enms[i].rotateZ = 0;
                enms[i].yPos = -0.5;
            }
            else if(enms[i].xPos > 2.0){
                enms[i].action = 1;
                enms[i].xMove = -0.005;
                enms[i].rotateZ = 0;
                enms[i].yPos = -0.5;
            }

            enms[i].xPos += enms[i].xMove;

            if (ply->actionTrigger == "Attack" && ply->xPos > enms[i].xPos){
                if(hit->isLinearCollision(ply->xPos, enms[i].xPos)){
                    enms[i].action = 9; // enemies die
                }
            }


            if (ply->actionTrigger == "Attack" && ply->xPos < enms[i].xPos){
                if(hit->isLinearCollision(ply->xPos, enms[i].xPos)){
                    enms[i].action = 9; // enemies die
                }
            }
            enms[i].actions();
        }


        break;

    case PAUSED: // pop up pause menu

        glPushMatrix();
        plx -> drawSquare(screenHeight, screenWidth);// drawing the game behind the pop screen
        glPopMatrix();
        glPushMatrix();
        glScaled(.75, .75, 1.0); // reduced scaling to reduce size
        pause -> drawPopUp(screenHeight, screenWidth);
        glPopMatrix();

        break;
        default:
        break;


    }
    //plx -> scroll("left", 0.0001);




}


GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //call this every time after modelview
}

int GLScene::winMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    	switch (uMsg)
    	{


            case WM_KEYDOWN:
            {
                KbMs ->wParam = wParam;    //second variable refernces one here other is in a differnt file
                KbMs -> keyPressed(Mdl, stateManager);
                KbMs -> keyPressed(snds);

            if (stateManager->_gameState == GAME) // The game cannot be controlled while paused
                {
                KbMs -> playerAction(ply);
                KbMs -> manualParallax(plx, 0.005);
                }
                break;
            }

            case WM_KEYUP:
            {
                ply->actionTrigger="stand";
                break;

            }

case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            KbMs->mouseEventDown(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            KbMs->mouseEventUp();
        break;
        }

        case WM_MOUSEMOVE:
        {
             KbMs->mouseEventMove(Mdl,LOWORD(lParam),HIWORD(lParam));
        break;
        }

        case WM_MOUSEWHEEL:
        {
            KbMs->mouseEventWheel(Mdl,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;
        }




    }

}


/*

GLvoid GLScene::drawGLScene(_Sound* snd)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    stateManager->_gameState;
    _Sound -> _gameState;
    //  State manager used to manipulate game states
    switch(stateManager->_gameState){
    case LANDING:


        break;

    case MENU:


        break;

    case HELP:

        break;

    case GAME:


        break;

    case PAUSED: // pop up pause menu

        break;
        default:
        break;


    }
}
*/
