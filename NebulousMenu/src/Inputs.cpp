#include "Inputs.h"

Inputs::Inputs()
{
    //ctor
        prev_mouse_X = 0;
        prev_mouse_Y = 0;

        mouse_Translate = 0;
        mouse_Rotate = 0;



}

Inputs::~Inputs()
{
    // ???
}

void Inputs::keyPressed(StateManager *stateManager)

{
    switch(wParam){

        case VK_LEFT:
            break;

        case VK_RIGHT:
            break;

        case VK_UP:
            break;

        case VK_DOWN:
            break;

        case VK_ESCAPE: //pause the game and open popup also quit the program for certain states
            if (stateManager->_gameState == GAME)
            {
                stateManager->_gameState = PAUSED;
            }

            else if (stateManager->_gameState == PAUSED)
            {
                stateManager->_gameState = GAME;
            }
            else if (stateManager->_gameState == HELP)
            {
                stateManager->_gameState = MENU;
            }
            else if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = QUIT;
            }
            break;

        case VK_RETURN: //Enter key commands

            if (stateManager->_gameState == LANDING)
            {
                stateManager->_gameState = MENU; // BAD EDITS
            }
            else if (stateManager->_gameState == PAUSED)
            {
                stateManager->_gameState = MENU;
            }

            break;

        case 0x4E: //N for new game
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = GAME;
            }

        case 0x48: //H for help page
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = HELP;
            }


    }
}

void Inputs::keyPressed(Model * Mdl, StateManager *stateManager)

{
    switch(wParam){

        case VK_LEFT:
            break;

        case VK_RIGHT:
            break;

        case VK_UP:
            break;

        case VK_DOWN:
            break;

        case VK_ESCAPE: //pause the game and open popup also quit the program for certain states
            if (stateManager->_gameState == PAUSED)
            {
                stateManager->_gameState = GAME;
            }
            else if (stateManager->_gameState == HELP)
            {
                stateManager->_gameState = MENU;
            }
            else if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = QUIT;
            }
            else if (stateManager->_gameState == CREDITS)
            {
                stateManager->_gameState = MENU;
            }
            else if (stateManager->_gameState == HELP_INGAME)
            {
                stateManager->_gameState = PAUSED;
            }
            break;


        case VK_SPACE:
            if (stateManager-> _gameState == STORY1)
            {
                stateManager->_gameState = STORY2;
            }
            else if (stateManager->_gameState == STORY2)
            {
                stateManager->_gameState = STORY3;
            }
            else if (stateManager->_gameState == STORY3)
            {
                stateManager->_gameState = STORY4;
            }
            else if (stateManager->_gameState == STORY4)
            {
                stateManager->_gameState = STORY5;
            }
            else if (stateManager->_gameState == STORY5)
            {
                stateManager->_gameState = MENU;
            }
            break;


        case VK_RETURN: //Enter key commands

            if (stateManager->_gameState == LANDING)
            {
                stateManager->_gameState = STORY1; // BAD EDITS
            }
            else if (stateManager->_gameState == PAUSED)
            {
                stateManager->_gameState = MENU;
            }

            break;

        case 0x46: //F for skipping intro
            if (stateManager->_gameState == STORY1)
            {
                stateManager->_gameState = MENU;
            }
            break;

        case 0x4E: //N for new game
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = GAME;
            }
            break;

        case 0x48: //H for help page
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = HELP;
            }
            else if (stateManager->_gameState == PAUSED)
            {
                stateManager->_gameState = HELP_INGAME;
            }
            break;

        case 0x50: // H for help
            if (stateManager->_gameState == GAME)
            {
                stateManager->_gameState = PAUSED;
            }
            break;

        case 0x57: //W to skip from Landing -> Menu & Menu -> Game
            if (stateManager->_gameState == LANDING)
            {
                stateManager->_gameState = MENU;
            }
            else if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = GAME;
            }
            break;

        case 0x43: //C for credits
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = CREDITS;
            }
            break;


    }
}

void Inputs::keyUp()
{


}

void Inputs::mouseEventDown(double x, double y)
{
    prev_mouse_X = x;
    prev_mouse_Y = y;

    switch(wParam) {
        case MK_LBUTTON:
            mouse_Rotate = true;
        break;

        case MK_RBUTTON:
            mouse_Translate = true;
        break;

        case MK_MBUTTON:
        break;

        default: break;

    }


}

void Inputs::mouseEventUp()
{
    mouse_Rotate = false;
    mouse_Translate = false;

}

void Inputs::mouseEventWheel(double Delta)
{

}

void Inputs::mouseEventMove(double x, double y)
{

}
void Inputs::manualParallax(Parallax* plx, float speed)
{
    switch(wParam)
    {
    case VK_LEFT:
        plx->scroll("left", speed);
        break;

        case VK_RIGHT:
        plx->scroll("right", speed);
        break;
    }

}

void Inputs::playerAction(player* ply)
{
    switch(wParam)
    {
        case VK_LEFT:
        ply->actionTrigger = "Left";
        /************** RICHARD'S CODE ***************************/
        ply->setPlayerDirection(-1);
        ply->xPos -= 0.02;
        /*********** END OF RICHARD'S CODE **********************/
        break;

        case VK_RIGHT:
        ply->actionTrigger = "Right";

        /************** RICHARD'S CODE **************************/
        ply->setPlayerDirection(1);
        ply->xPos += 0.02;
        /************* END OF RICHARD'S CODE ******************/
        break;


        case 0X41: // A for Attack
        ply->actionTrigger = "Attack";
            break;

        case VK_UP:
        ply->actionTrigger = "Jump"; // to be fixed
        break;


        case VK_DOWN:
        ply->actionTrigger = "Down"; // crouch to be fixed
        break;

    }

}



