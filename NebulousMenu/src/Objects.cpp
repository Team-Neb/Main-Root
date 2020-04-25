#include "Objects.h"

textureLoader *T1 = new textureLoader();
Timer *Time1 = new Timer();


Objects::Objects()
{
    //ctor
        xPos = 0.0;
        yPos = 0.0;
        zPos = -0.5;

        xSize = 1.0;
        ySize = 1.0;

        rotateX = 0.0;
        rotateY = 0.0;
        rotateZ = 0.0;

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
}

Objects::~Objects()
{
    //dtor
}

void Objects::placeObjects(float x, float y, float z)
{
    xPos = x;
    yPos = y;
    zPos = z;

}
void Objects::objectsInit(char* fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    T1->loadTexture(fileName);
    Time1->start();

    xMin=0.25;
    xMax = 0.0;

    yMin = 0.5;
    yMax = 0.75;

}

void Objects::drawObjects()
{
    T1->binder();
    glPushMatrix();

    glTranslated(xPos, yPos, zPos);
    glRotated(rotateX, 1.0, 0.0, 0.0);
    glRotated(rotateY, 0.0, 1.0, 0.0);
    glRotated(rotateZ, 0.0, 0.0, 1.0);

    glScaled(xSize, ySize, 1.0);
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
