#include "Inputs.h"
#include<_Sound.h>

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

void Inputs::keyPressed(Model * Mdl, StateManager *stateManager)
{
    switch(wParam){

        case VK_LEFT:
            Mdl->RotateX += 10.0;
            break;

        case VK_RIGHT:
             Mdl->RotateX += -10.0;
            break;

        case VK_UP:
              //Mdl->RotateY += 1.0;
            break;

        case VK_DOWN:
             //Mdl->RotateY += -1.0;
            break;
/*
        case 0x41:
             Mdl->zoom += +0.50;
            break;
        case 0x44:
             Mdl->zoom += -0.50;
            break;
*/
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
            else if (stateManager->_gameState == CREDITS)
            {
                stateManager->_gameState = MENU;
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

        case 0x48: //H for help page
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = HELP;
            }
        case 0x43: //C for credits
            if (stateManager->_gameState == MENU)
            {
                stateManager->_gameState = CREDITS;
            }


    }
}

void Inputs::keyUp()
{


}

void Inputs::mouseEventDown(Model * Mdl, double x, double y)
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

void Inputs::mouseEventWheel( Model * Mdl, double Delta)
{
    Mdl->zoom += Delta/100;
}

void Inputs::mouseEventMove(Model * Mdl, double x, double y)
{
    if(mouse_Translate){
        Mdl->xPos += (x-prev_mouse_X)/100;
        Mdl->yPos -= (y-prev_mouse_Y)/100;  // negative because screen is in upper right corner because y = 0
        prev_mouse_X = x;
        prev_mouse_Y = y;
    }
    if(mouse_Rotate){
        Mdl->RotateX += (x-prev_mouse_X)/3;
        Mdl->RotateY += (y-prev_mouse_Y)/3;
        prev_mouse_X = x;
        prev_mouse_Y = y;

    }

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

/*
        case VK_UP:
        plx->scroll("up", speed);
        break;

                                        // We don't need our hero going down the screen lol

        case VK_DOWN:
        plx->scroll("down", speed);
        break;

*/
    }

}

void Inputs::playerAction(player* ply)
{
    switch(wParam)
    {
        case VK_LEFT:
        ply->actionTrigger = "Left";
        break;

        case VK_RIGHT:
        ply->actionTrigger = "Right";
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

void Inputs::keyPressed(_Sound* snd) // SOUND EFFECTS CONFIGS
{
    switch(wParam)
    {
        case 0X41: // A for Attack
        snd->playSound("sounds/SwordSwing01.mp3");
            break;

        case VK_SPACE:
            snd->playSound("sounds/MenuSound.mp3");
            break;

        case VK_RETURN:
        snd->playSound("sounds/MenuSound.mp3");
            break;

        case 0x4E:
        snd->playSound("sounds/MenuSound2.mp3");
            break;

        case VK_ESCAPE:
        snd->playSound("sounds/MenuSound2.mp3");
            break;

        case 0x48:
        snd->playSound("sounds/HelpSound.mp3");
            break;

    }

}

// DIFFERENT MUSIC FOR DIFFERENT SCENES ? ///

void Inputs::keyPressed(StateManager *stateManager, _Sound* snd)
{
    switch(wParam){

        case VK_ESCAPE: //pause the game and open popup also quit the program for certain states
            if (stateManager->_gameState == GAME)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }

            else if (stateManager->_gameState == PAUSED)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }
            else if (stateManager->_gameState == HELP)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }
            else if (stateManager->_gameState == MENU)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }
            break;

        case VK_RETURN:            //Enter key commands

            if (stateManager->_gameState == LANDING)
            {
                snd->playSound("sounds/OptionSound.mp3");
                break;
            }
            else if (stateManager->_gameState == PAUSED)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }

            break;

        case 0x4E: //N for new game
            if (stateManager->_gameState == MENU)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }

        case 0x48: //H for help page
            if (stateManager->_gameState == MENU)
            {
                snd->playSound("sounds/OptionSound.mp3");
            }


    }
}


