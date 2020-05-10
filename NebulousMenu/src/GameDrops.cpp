#include "GameDrops.h"

GameDrops::GameDrops()
{
    //ctor
    this->xPos = this->yPos = 0;
    this->zPos = -5;

    // 0.3
    this->xSize = this->ySize = 0.15 ;
    this->frames = 1;
    this->xMin = 0;
    this->yMin = 0;
    this->xMax = 1;
    this->yMax = 1;
    this->action = 1;

    this->rotateY = 0;
    this->dropType = 0;
}

GameDrops::~GameDrops()
{
    //dtor
}

void GameDrops::drawDrop()
{
    glBindTexture(GL_TEXTURE_2D, this->dropTex);
    glPushMatrix();
        glTranslatef(xPos,yPos,zPos);
        //glRotatef(rotateY,0.0,1.0,0.0);
        glScalef(xSize,ySize,1);

        glBegin(GL_POLYGON);
            glTexCoord2f(xMin,yMin);
            glVertex3f(1.0, 1.0, -1.0);
            glTexCoord2f(xMax,yMin);
            glVertex3f(-1.0, 1.0, -1.0);
            glTexCoord2f(xMax,yMax);
            glVertex3f(-1.0, -1.0, -1.0);
            glTexCoord2f(xMin,yMax);
            glVertex3f(1.0, -1.0, -1.0);

        glEnd();
    glPopMatrix();
}

void GameDrops::placeDrop(float x, float y, float z)
{
    this->xPos = x;
    this->yPos = y;
    this->zPos = z;
}
void GameDrops::initDrop(GLuint tex)
{
    this->dropTex = tex;
    TE->start();
}


int GameDrops::getAction()
{
    return this->action;
}

void GameDrops::setAction(int value)
{
    this->action = value;
}

void GameDrops::actions()
{
    switch(action){
        case 1:
            if(TE->getTicks() > 60){
                rotateY += 5;
                TE->reset();
            }
            break;
        default:
            break;
    }
}


void GameDrops::checkPlayerPickup(float playerX, int direction)
{
    switch(direction){
        case -1:
            if( (this->xPos) <= (playerX + 0.75) && (this->xPos) >= (playerX)){
                this->action = 9;
            }
            break;
        case 1:
            if( (this->xPos) >= (playerX + 0.75) && (this->xPos) <= (playerX + 1.25) ) {
                this->action = 9;
            }
            break;
        default:
            break;
    }
}



int GameDrops::getDropType()
{
    return this->dropType;
}

void GameDrops::setDropType(int value)
{
    this->dropType = value;
}
