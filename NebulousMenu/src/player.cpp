#include "player.h"
#include <Timer.h>

textureLoader *T = new textureLoader();
Timer *Time = new Timer();

player::player()
{
    //ctor
    vertices[0].x = 0.0;
    vertices[0].y = 0.0;
    vertices[0].z = -1.0;

    vertices[1].x = 1.0;
    vertices[1].y = 0.0;
    vertices[1].z = -1.0;

    vertices[2].x = 1.0;
    vertices[2].y = 1.0;
    vertices[2].z = -1.0;

    vertices[3].x = 0.0;
    vertices[3].y = 1.0;
    vertices[3].z = -1.0;

    xMin=yMin=0.0;
    xMax=yMax=1.0;


    xPos = -0.5;
    yPos = -0.7;
    zPos = -1.0;

}

player::~player()
{
    //dtor
}

void player::drawPlayer()
{
    T->binder();
    glPushMatrix();
    glBegin(GL_QUADS);

    glTexCoord2f(xMin, yMax);
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

    glTexCoord2f(xMax, yMax);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

    glTexCoord2f(xMax, yMin);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

    glTexCoord2f(xMin, yMin);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);



    glEnd();
    glPopMatrix();


}

void player::playerInit(char *fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    T->loadTexture(fileName);
    Time->start();

    xMin=0.25;
    xMax = 0.0;

    yMin = -1.0;
    yMax = 1.0;

}

void player::playerActions()
{
    if (actionTrigger == "stand")
    {
        xMin=0.0;
        xMax = 0.25;

        yMin = 0.5;
        yMax = 0.75;

        yPos = -0.6; // will work on a jump functionality
    }
    if (actionTrigger == "Left")
    {

        if(Time -> getTicks()>80) // edit variable to increase speed
        {

        xMin -= 0.25;
        xMax -= 0.25;

        yMin = 0.25;
        yMax = 0.50;

        Time ->reset();
        }
    }

    if (actionTrigger == "Right")
    {
        if(Time -> getTicks()>80)
        {

        xMin += 0.25;
        xMax += 0.25;

        Time ->reset();
        }


    }
}

