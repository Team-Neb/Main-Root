
#include <GLLight.h>
#include "GLScene.h"
#include<Inputs.h>
#include<Model.h>
#include<Parallax.h>
#include<player.h>
#include <Objects.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_npc.h>
#include <Timer.h>
#include <vector>

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

textureLoader *enmsTex = new textureLoader();
_enms enms[10];



// Create vector of _npc pointers to store level 2 enemy objects
// as well as the texture handler for these enemies
vector<_npc *> enemyType2;
textureLoader *enemy2Tex = new textureLoader();

// Creating array of parrallax pointers to store background images of the game levels
vector<Parallax *> gameLevel;
const int NUMBER_OF_LEVELS = 2;



GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);

    // initialize game level to 1 by default
    this->level = 1;
    this->is_level_complete = false;
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

    // Create the number of parallax objects
    for(int i = 0; i < NUMBER_OF_LEVELS; i++){
        gameLevel.push_back(new Parallax());
    }

    // Apply the texture image to the handler
    enemy2Tex->loadTexture("images/monster2.png");  // load the image to the second enemy monster

    // Create enemy objects for the first level
    this->spawnEnemies(this->level);

    // INITIALIZE THE BACKGROUND GAME LEVEL SCENES
    gameLevel[0]->parallaxInit("images/par.png");
    gameLevel[1]->parallaxInit("images/level-2.png");


   // images to import for game states
    ply->playerInit("images/walkAndattack.png");
    plx->parallaxInit("images/par.png");
    pause->parallaxInit("images/pause.jpg");
    tlt->parallaxInit("images/title.png");
    menu->parallaxInit("images/FrontMenu.jpg");
    help->parallaxInit("images/help.jpg");
    enmsTex->loadTexture("images/mon.png");


    for(int i = 0; i < 1; i++){
        enms[i].initEnemy(enmsTex->tex);
        enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5, -0.5, -2.0);
        enms[i].xSize = enms[i].ySize = float(rand()%12)/65.0;
    }

    return true;

}

//function for main to exit game when escape is pressed on certain game states
GameStates GLScene::sendState(){
    return stateManager->_gameState;
}


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

        // Add the background parallax image
        glPushMatrix();
            // Choose the proper background based on the current game level
            switch(this->level){
                case 1:
                    gameLevel[0]->drawSquare(screenHeight, screenWidth);
                    break;
                case 2:
                    gameLevel[1]->drawSquare(screenHeight, screenWidth);
                    break;
                default:
                    break;
            }
        glPopMatrix();

        // If the level has changed - spawn the next type of enemies
        if(this->is_level_complete){
            this->spawnEnemies(this->level);
            this->is_level_complete = false;
        }

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


        //check if player sword collided with an enemy if player attacked
        if(ply->hasPlayerAttacked() ){
            enemyType2[0]->swordCollisionCheck(ply->xPos, ply->getPlayerDirection());
            ply->setPlayerAttackStatus(false);
        }

        // This will update the position of the enemy and check for collision by movement
        // If collision was done by movement - then it will update the action variable
        // of the enemy2. The next time it updates - the enemy will perform the appropiate action
        enemyType2[0]->actions(ply->xPos);


        // Check if enemy has been killed to move onto next level
        // Current implementation is just a single enemy - eventually check vector length
        // to see if all enemy objects have been destroyed
        if(enemyType2[0]->action == 9 && !this->is_level_complete){
            delete enemyType2[0];       // delete enemy object
            enemyType2[0] = nullptr;    // no dangling pointers
            enemyType2.pop_back();      // remove from vector array

            if(enemyType2.empty()){
                    // Put this if statement to prevent game from crashing after 2nd level
                    if(this->level != 2){
                        this->level += 1;
                    }
                this->is_level_complete = true;

            }
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


void GLScene::spawnEnemies(int level)
{
    switch(level){

        // Stevens enemy objects go in here.
        // My enemy objects are placed in level 1 as place holder for now
        case 1:
            for(int i = 0; i < 1; i++){
                enemyType2.push_back(new _npc());
                enemyType2[i]->initEnemy(enemy2Tex->tex);
                enemyType2[i]->placeEnemy(-1.37, -1.45, -5.0);
            }
            break;
        case 2:
            for(int i = 0; i < 1; i++){
                enemyType2.push_back(new _npc());
                enemyType2[i]->initEnemy(enemy2Tex->tex);
                enemyType2[i]->placeEnemyRandom();
                //enemyType2[i]->placeEnemy(-1.37, -1.45, -5.0);
            }
            break;
        default:
            break;
    }
}


