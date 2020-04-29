
#include <GLLight.h>
#include "GLScene.h"
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<player.h>
#include <Objects.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <HealthBar.h>
#include <_npc.h>
#include <Timer.h>


Inputs *KbMs = new Inputs();
Model *Mdl = new Model();
Parallax *plx = new Parallax();
Parallax *pause = new Parallax();
player *ply = new player();
StateManager *stateManager = new StateManager;
Parallax *tlt = new Parallax();
Parallax *menu = new Parallax();
Parallax *help = new Parallax();

_checkCollision *hit = new _checkCollision();
HealthBar *healthBar = new HealthBar();

textureLoader *enmsTex = new textureLoader();
_enms enms[1];

// init second enemy object
_npc *enemy2 = new _npc();
textureLoader *enemy2Tex = new textureLoader();


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
    healthBar->initHealthBar("images/heartBar.png");
    enmsTex->loadTexture("images/mon.png");
    enemy2Tex->loadTexture("images/monster2.png");  // load the image to the second enemy monster



    for(int i = 0; i < 1; i++){
        enms[i].initEnemy(enmsTex->tex);
        enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5, -0.5, -2.0);
        enms[i].xSize = enms[i].ySize = float(rand()%12)/65.0;
        if (enms[i].xSize < 0){
            enms[i].enemyFacing  = false;       // facing right, come from left side of player
        }
        else{
            enms[i].enemyFacing = true;         // facing left, come from right side of player
        }
    }

    // placing the enemy and initializing it's values
    enemy2->initEnemy(enemy2Tex->tex);
    enemy2->placeEnemy(-1.37, -1.45, -5.0);

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

    case GAME:
        glPushMatrix();
        plx -> drawSquare(screenHeight, screenWidth);
        glPopMatrix();

        glPushMatrix();
            glTranslated(ply->xPos, ply->yPos , ply->zPos);
            ply->drawPlayer(); // render character
            ply->playerActions(); // render actions
        glPopMatrix();

        for(int i = 0; i < 1; i++){
            if(enms[i].xPos< -2.0){
                enms[i].action = 0;
                enms[i].xMove= 0.005;
                enms[i].rotateZ = 0;
                enms[i].enemyFacing = false;
                enms[i].yPos = -0.5;
            }
            else if(enms[i].xPos > 2.0){
                enms[i].action = 1;
                enms[i].xMove = -0.005;
                enms[i].rotateZ = 0;
                enms[i].enemyFacing = true;
                enms[i].yPos = -0.5;
            }

            enms[i].xPos += enms[i].xMove;

            // check on left. Check if A press, player position - half the size of player is less the position of enms x position + half of enemy size,
            // and check last key hit is true, meant player facing left, and check enemy facing right.
            if (ply->actionTrigger == "Attack" && ply->xPos - ply->xSize/2 < enms[i].xPos + enms[i].xSize/2 && ply->lastKeyHit == true && enms[i].enemyFacing == false){
                if(hit->isLinearCollision(ply->xPos, enms[i].xPos)){
                    enms[i].action = 9; // enemies die
                    //cout << enms[i].xPos+ enms[i].xSize/2 << endl;
                }
            }

            // check on right
            else if (ply->actionTrigger == "Attack" && ply->xPos + ply->xSize/2 > enms[i].xPos - enms[i].xSize/2 && ply->lastKeyHit == false && enms[i].enemyFacing == true){
                if(hit->isLinearCollision(ply->xPos, enms[i].xPos)){
                    enms[i].action = 9; // enemies die
                }
            }
            else if ((ply->actionTrigger == "stand" || ply->actionTrigger == "Left" || ply->actionTrigger == "Right") && (fabs(ply->xPos  - enms[i].xPos + enms[i].xSize/2 < 0.0000001))){
                ply-> health -=1;
            }
            else if ((ply->actionTrigger == "stand" || ply->actionTrigger == "Left" || ply->actionTrigger == "Right") && (ply->xPos  == enms[i].xPos + enms[i].xSize/2)){
                ply-> health -=1;
            }

            enms[i].actions();
        }
        cout<< ply->health;
        healthBar->healthBarActions(ply->health);
        healthBar->drawHealthBar();

        /*if(ply->hasPlayerAttacked() ){
            //check if player sword collided with enemy
            enemy2->swordCollisionCheck(ply->xPos, ply->getPlayerDirection());
            ply->setPlayerAttackStatus(false);
        }

        // This will update the position of the enemy and check for collision
        // If collision was done by movement - then it will update the action variable
        // of the enemy2. The next time it updates - the enemy will perform the appropiate action
        enemy2->actions(ply->xPos);*/


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

