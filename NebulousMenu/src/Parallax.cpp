#include "Parallax.h"


Parallax::Parallax()
{
    //ctor
    xMax = 1.0;
    yMax = 1.0;
    xMin = 0.0;
    yMin = 0.0;

}

Parallax::~Parallax()
{
    //dtor
}
void Parallax::drawSquare(float width, float height)
{
    this->bTexture->binder();
    glScaled(11, 3.33, 1.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMax);
        glVertex3f(-width/height,-1,-8.0f);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height,-1,-8.0f);


        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height,1,-8.0f);

        glTexCoord2f(xMin, yMin);
        glVertex3f(-width/height,1,-8.0f);


    glEnd();
}

void Parallax::drawPopUp(float width, float height) //pause menu
{
    this->bTexture->binder();
    glScaled(7.46, 3.33, 1.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(xMin, yMax);
        glVertex3f(-width/height,-1,-8.0f);

        glTexCoord2f(xMax, yMax);
        glVertex3f(width/height,-1,-8.0f);


        glTexCoord2f(xMax, yMin);
        glVertex3f(width/height,1,-8.0f);

        glTexCoord2f(xMin, yMin);
        glVertex3f(-width/height,1,-8.0f);


    glEnd();

}



void Parallax::parallaxInit(char* fileName) // So that no image over writes another
{

    this->bTexture->loadTexture(fileName);
    this->bTexture->binder();

}
void Parallax::scroll(string dir, float speed)


    {
        if (dir == "up"){yMin -= speed; yMax -= speed;}
        if (dir == "down"){yMin += speed; yMax += speed;}
        if (dir == "left"){xMin -= speed; xMax -= speed;}
        if (dir == "right"){xMin += speed; xMax += speed;}
    }

