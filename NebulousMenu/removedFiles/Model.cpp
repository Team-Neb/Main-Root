#include "Model.h"
#include <textureLoader.h>
textureLoader *tex = new textureLoader();
Model::Model()
{
    //ctor
    RotateX=0.0;
    RotateY=0.0;
    RotateZ=0.0;

    zoom=-8.0;
    xPos=0.0;
    yPos=0.0;
    zPos;

}

Model::~Model()
{
    //dtor
}
void Model::modelInit(char* fileName)
{

    tex->loadTexture(fileName);
}

void Model::drawModel()
{
    tex->binder();
    glColor3f(0.8,0.5,0.0); // to be altered by users for color inputs
    glTranslated(xPos,yPos,zoom);
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);
    glutSolidTeapot(1.5);

    //whatever the model you draw

}
