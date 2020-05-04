
#include <GLLight.h>
#include "GLScene.h"
#include<Inputs.h>
#include<Parallax.h>
#include<player.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_npc.h>       // Richard's enemy class
#include <vector>       // Needed for vector of pointers of various classes
#include <GameDrops.h>  // Richard's game drop class
#include <time.h>

Inputs *KbMs = new Inputs();
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


/**************** RICHARD'S CODE *************************/

const int NUMBER_OF_LEVELS = 2;         // Controls how large the levels vector will be
const int MAX_ENEMIES = 4;              // Controls how large the enemy vector will be and when to end the level
const int NUMBER_OF_ENEMIES = 1;        // Controls how many textures are created for the enemy object
int positionEnemy = 1.5;

/*************** END OF RICHARD'S CODE **********************/


GLScene::GLScene()
{
    //ctor
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);

    /*************** RICHARD'S CODE ***************/
    this->level = 1;                    // Game level 1 by default
    this->is_level_complete = false;    // The selected/first level of the game is never complete by default
    this->cinematicFrames = 5;          // CHANGE THIS DEPENDING ON HOW MANY SCENES IN THE INTRO CINEMATIC
    this->currentCinematicFrame = 0;    // cinematic vector starts at index 0
    /************ END OF RICHARD'S CODE **********/
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

    srand(time(0));

    /************************** RICHARD'S CODE ********************************************/
    // For more random-like behavior
    srand(time(0));

    // Initialize all the needed textures
    this->initDropTextures();
    this->initEnemyTextures();
    this->initLevelScenes();


    // Initialize the cinematic vector with all the needed scenes
    this->initCinematic();
    this->cinematicTimer->start();

    // Create enemy objects for the first level
    this->spawnEnemies(this->level);


    /************************** END OF RICHARD'S CODE **************************************/

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

        /***************************** RICHARD'S CODE ***********************************************/
        // Every 2 seconds update the cinematic vector position and as long as all scenes have not been displayed
        if (this->cinematicTimer->getTicks() > 2000 && currentCinematicFrame != this->cinematicFrames){
            this->currentCinematicFrame += 1;
            this->cinematicTimer->reset();
        }

        // Show the intro cinematic scene if not all scenes have been shown.
        if(currentCinematicFrame != this->cinematicFrames){
            glPushMatrix();
            glScaled(.33, 1, 1.0);
            this->cinematic[currentCinematicFrame]->drawSquare(screenWidth,screenHeight);
            glPopMatrix();
        // Otherwise show the menu page
        }else{
            glPushMatrix();
            glScaled(.33, 1, 1.0);
            menu->drawSquare(screenWidth,screenHeight);
            glPopMatrix();
        }
        /************************* END OF RICHARD'S CODE *********************************************/
        break;
    case HELP:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        help->drawSquare(screenWidth,screenHeight);
        glPopMatrix();
        break;

    case GAME:

        /*********************** RICHARD'S CODE ******************************************************/
        // Add the background parallax image
        glPushMatrix();
            // Choose the proper background based on the current game level
            switch(this->level){
                case 1:
                    this->levels[0]->drawSquare(screenHeight, screenWidth);
                    break;
                case 2:
                    this->levels[1]->drawSquare(screenHeight, screenWidth);
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
        /**************** END OF RICHARD'S CODE ******************************************************/

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


        /************************************** RICHARD'S CODE ***********************************/
        // check if player sword collided with an enemy if player attacked
        // if player has not attacked, then player must have moved.
        // The enemy performs an action based on it's action value and gets drawn
        this->updateEnemiesAction();

        this->updateDrops();


        // Check if all enemy has been killed to move onto next level
        // Current implementation is just a single enemy
        // to see if all enemy objects have been destroyed
        // Destroy enemy objects if they are supposed to die
        this->destroyEnemies();

        // Draw any GameDrops on the screen
        this->drawDrops();
        /************************************************ END OF RICHARD'S CODE ****************************/
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
                KbMs -> keyPressed(stateManager);


            if (stateManager->_gameState == GAME) // The game cannot be controlled while paused
                {
                KbMs -> playerAction(ply);
                /************************************************** RICHARD'S CODE ***************************************/
                switch(this->level){
                    case 1:
                        KbMs->manualParallax(levels[this->level - 1], 0.005);
                        break;
                    case 2:
                        KbMs->manualParallax(levels[this->level - 1], 0.005);
                        break;
                    default:
                        break;
                }
                /*********************************************** END OF RICHARD'S CODE ***********************************/
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

        break;
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;

        break;
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;

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

        break;
        }

        case WM_MOUSEWHEEL:
        {
        break;
        }




    }

}



// RICHARDS CODE
// Create a new enemy object, place into vector of enemy objects
// Apply texture image to the object and finally place it randomly on the screen
// Takes in the scenes current level
void GLScene::spawnEnemies(int level)
{
    switch(level){

        // Stevens enemy objects go in here.
        // My enemy objects are placed in level 1 as place holder for now
        case 1:
            for(int i = 0; i < 1; i++){
                enemyType2.push_back(new _npc());
                enemyType2[i]->initEnemy(enemyTextures[0]->tex);
                enemyType2[i]->placeEnemy(-1.37, -1.65, -5.0);
            }
            break;
        case 2:
            for(int i = this->enemyType2.size(); i < MAX_ENEMIES; i++){
                this->enemyType2.push_back(new _npc());
                this->enemyType2.back()->initEnemy(this->enemyTextures[0]->tex);
                this->enemyType2.back()->placeEnemyRandom();

            }
            /*
                this->enemyType2.push_back(new _npc());
                this->enemyType2[ this->enemyType2.size() - 1]->initEnemy(this->enemyTextures[0]->tex);
                this->enemyType2[ this->enemyType2.size() - 1]->placeEnemyRandom();
                */
            break;
        default:
            break;
    }
}

// RICHARDS CODE
// Create new Parallax objects, up to however many cinematicFrames is defined as
// Place them into vector of cinematic
// Finally parallaxInit all of the newly created objects
//      TO DO: FIND A BETTER WAY TO INIT THE OBJECTS
void GLScene::initCinematic()
{
    // Add Parallax objects into the vector
    for(int i = 0; i < this->cinematicFrames; i++){
        cinematic.push_back(new Parallax());
    };
    cinematic[0]->parallaxInit("images/scene01.png");
    cinematic[1]->parallaxInit("images/scene02.jpg");
    cinematic[2]->parallaxInit("images/scene03.png");
    cinematic[3]->parallaxInit("images/scene04.png");
    cinematic[4]->parallaxInit("images/scene05.png");
}


// RICHARDS CODE
// Create new GameDrop object and place into vector drops at the end
// Apply texture image to the last object in the vector
// Place the object based on the enemy's position that spawned this drop
// Takes in the enemy's x, y, and z Position values
void GLScene::spawnGameDrop(float x, float y ,float z, int type){
    drops.push_back(new GameDrops());
    switch(type){
        case 1:
            drops[drops.size() - 1]->initDrop(this->dropTextures[0]->tex);
            drops[drops.size() - 1]->placeDrop(x, y - 0.2, z);
            drops[drops.size() - 1]->setDropType(1);
            break;
        case 2:
            drops[drops.size() - 1]->initDrop(this->dropTextures[1]->tex);
            drops[drops.size() - 1]->placeDrop(x, y - 0.2, z);
            drops[drops.size() - 1]->setDropType(2);
            break;
        case 3:
            drops[drops.size() - 1]->initDrop(this->dropTextures[2]->tex);
            drops[drops.size() - 1]->placeDrop(x, y - 0.2, z);
            drops[drops.size() - 1]->setDropType(3);
            break;
        default:
            drops[drops.size() - 1]->initDrop(this->dropTextures[0]->tex);
            drops[drops.size() - 1]->placeDrop(x, y - 0.2, z);
            drops[drops.size() - 1]->setDropType(1);
            break;
    }
}





// RICHARD'S CODE
// Holds the drop textures
// Add textureLoader objects into vector dropTextures
// then manually apply the images to each object
void GLScene::initDropTextures()
{
    // Fill the vector with textureLoader objects
    for(int i = 0; i < 3; i++){
        this->dropTextures.push_back(new textureLoader());
    }

    // Apply the texture
    this->dropTextures[0]->loadTexture("images/heart_drop.png");
    this->dropTextures[1]->loadTexture("images/godmode_drop.png");
    this->dropTextures[2]->loadTexture("images/key_drop.png");
}

// RICHARD'S CODE
// Holds the enemy textures
// Add textureLoader objects into vector enemyTextures
// then manually apply the images to each object
void GLScene::initEnemyTextures()
{
    for(int i = 0; i < NUMBER_OF_ENEMIES; i++){
        this->enemyTextures.push_back(new textureLoader());
    }

    this->enemyTextures[0]->loadTexture("images/Skull_Spritesheet.png");
}

// RICHARD'S CODE
// Holds the background scenes for each level
// Add Parallax Objects into the vector levels up to the defined number of levels
// Then manually apply the images to each object
void GLScene::initLevelScenes()
{
    // Create the number of parallax objects for the background scene of each level
    for(int i = 0; i < NUMBER_OF_LEVELS; i++){
        this->levels.push_back(new Parallax());
    }
    // INITIALIZE THE BACKGROUND GAME LEVEL SCENES
    this->levels[0]->parallaxInit("images/par.png");
    this->levels[1]->parallaxInit("images/level-2.png");
}


// RICHARD'S CODE
void GLScene::resetLevel(int)
{

}

// RICHARD'S CODE
// Reset the entire game
void GLScene::resetGame()
{
    this->level = 1;
    this->is_level_complete = false;

    // Destroy all enemy objects
    for(int i = 0; i < enemyType2.size(); i++){
        // Try to avoid memory leaks
        delete this->enemyType2[i];       // delete enemy object
        this->enemyType2[i] = NULL;       // no dangling pointers
        this->enemyType2.erase(this->enemyType2.begin() + i);
    }

    // Destroy all gamedrop objects
    for(int i = 0; i < drops.size(); i++){
        delete this->drops[i];
        this->drops[i] = NULL;
        this->drops.erase(this->drops.begin() + i);
    }

    // Reset player action and variables
    ply->xPos = 0.0;                    // Reset player position
    // Reset health here STEVEN
    // Reset godmode status here
    ply->setPlayerAttackStatus(false);      // Reset flag determining if attacked
    ply->setKeyStatus(false);           // Reset flag determining if key obtained
    ply->setPlayerDirection(1);         // Player starts off facing right
    ply->actionTrigger = "stand";       // Player starts off with stand animation


    // RESET SOUND


    // RESET HEALTH BAR
}


// RICHARD'S CODE
// Draw's any GameDrop object onto the screen.
// Actions() of drops[i] was/is meant to be IDLE animation.
void GLScene::drawDrops()
{
    // Draw any GameDrops on the screen
    for(int i = 0; i < this->drops.size(); i++){
        drops[i]->actions();        // want rotating IDLE animation
        drops[i]->drawDrop();
    }
}


// RICHARD'S CODE
// Goes through the vector drops checking to see if player has collided with object
// Then checks to see if the drop is supposed to be deleted, if so retrieve drop information type
// and set update proper status flag of player before deleting the object
void GLScene::updateDrops()
{
    for(int i = 0; i < this->drops.size(); i++){
        this->drops[i]->checkPlayerPickup(ply->xPos, ply->getPlayerDirection());      // update the status of game drop object if collision
        if(this->drops[i]->getAction() == 9){
            if(this->drops[i]->getDropType() == 3){
                ply->setKeyStatus(true);
                cout<<"Picked up key!"<<endl;
            }
            cout<<"PICKED UP GAMEDROP OBJECT"<<endl;
            delete this->drops[i];
            this->drops[i] = NULL;
            this->drops.erase(drops.begin() + i);
        }
    }
}


// RICHARD'S CODE
// Goes through the vector enemyType2 updating all of their next action (move left/right)
// If player has attacked, check if enemy collided with player sword before updating action
// Afterwards set's player's attack status to false
void GLScene::updateEnemiesAction()
{

    // Update all enemies. If player has attacked check if there was a sword collision
    for(int i = 0; i < this->enemyType2.size(); i++){
        if(ply->hasPlayerAttacked()){
            this->enemyType2[i]->swordCollisionCheck(ply->xPos, ply->getPlayerDirection() );
        }
        this->enemyType2[i]->actions(ply->xPos);
    }

    ply->setPlayerAttackStatus(false);

}

// RICHARD'S CODE
// Goes through vector enemyType2 deleting any enemy objects whose action value is 9
// Random chance to spawn 1 of 3 types of drops upon enemy death.
// Checks to see if the vector enemyType2 is empty after to determine if move onto next level
void GLScene::destroyEnemies()
{
    // Destroy enemy objects if they are supposed to die and while level not complete
    for(int i = 0; i < this->enemyType2.size(); i++){
        if(this->enemyType2[i]->action == 9 && !this->is_level_complete){

            // Random chance to spawn a GameDrop
            int temp = 0;
            temp = rand() % 10 + 1;
            if(temp >= 10){
                this->spawnGameDrop(this->enemyType2[i]->xPos, this->enemyType2[i]->yPos, -5.0, 3);
            }else if( temp >=7){
                this->spawnGameDrop(this->enemyType2[i]->xPos, this->enemyType2[i]->yPos, -5.0, 2);
            }else{
                this->spawnGameDrop(this->enemyType2[i]->xPos, this->enemyType2[i]->yPos, -5.0, 1);
            }


            // Try to avoid memory leaks
            delete this->enemyType2[i];       // delete enemy object
            this->enemyType2[i] = NULL;       // no dangling pointers
            this->enemyType2.erase(enemyType2.begin() + i);


            // If vector is empty, move onto the next level
            if(this->enemyType2.empty()){
                // Put this if statement to prevent game from crashing after 2nd level
                if(this->level != 2){
                    this->level += 1;
                }
                this->is_level_complete = true;
            }
        }
    }

}
