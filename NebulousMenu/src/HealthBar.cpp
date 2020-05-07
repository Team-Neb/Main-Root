#include "HealthBar.h"
textureLoader *heartTex = new textureLoader();


HealthBar::HealthBar(){
    //ctor

    xPos = -0.6;//-6.0;
    yPos = 0.35;//18.0;
    zPos = -1;//-1.0;

    frames = 5;
    xMin = 0;
    yMin = 0;
    xMax = 1;
    yMax = 1;
    xSize = 0.1;
    ySize = 0.02;
}

HealthBar::~HealthBar()
{
    //dtor
}
void HealthBar::drawHealthBar(){

    heartTex->binder();

    glTranslatef(xPos,yPos,zPos);
    glScalef(xSize,ySize,1);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(-1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(-1.0, -1.0, 0.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(1.0, -1.0, 0.0);

    glEnd();
    glPopMatrix();

}

void HealthBar::initHealthBar(char* fileName){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    heartTex->loadTexture(fileName);
}


void HealthBar::healthBarActions(int health){
    switch(health){

    case 5:
        xMax = 1;
        xSize = 0.1;
        break;

    case 4:
        xMax = 0.8;
        xSize = 0.08;
        //drawHealthBar();
        break;
    case 3:
        xMax = 0.6;
        xSize = 0.06;
        break;
    case 2:
        xMax = 0.4;
        xSize = 0.04;
        break;
    case 1:
        xMin = 0;
        xMax = 0.2;
        xSize = 0.02;
        //drawHealthBar();
        break;

    }
}
