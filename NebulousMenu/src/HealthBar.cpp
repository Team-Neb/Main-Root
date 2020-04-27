#include "HealthBar.h"
textureLoader *heartTex = new textureLoader();


HealthBar::HealthBar(){
    //ctor

    xPos = -6;
    yPos = 18;
    zPos = -1;

    frames = 5;
    xMin = 0;
    yMin = 0;
    xMax = 1;
    yMax = 1;
}

HealthBar::~HealthBar()
{
    //dtor
}
void HealthBar::drawHealthBar(){

    heartTex->binder();

    glPushMatrix();
    glScalef(0.1,0.02,1);
    glTranslatef(xPos,yPos,zPos);
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

}
