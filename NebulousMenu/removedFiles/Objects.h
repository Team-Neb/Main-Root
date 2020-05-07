#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/gl.h>
#include<textureLoader.h>
#include <Timer.h>
#include<player.h>

class Objects
{
    public:
        Objects();
        virtual ~Objects();

        void objectsInit(char *);
        void placeObjects(float, float, float);
        void drawObjects();

        bool isObjectLive = true;
        GLuint objectTex;

        bool liveObject;

        float xPos;
        float yPos;
        float zPos;

        float xSize;
        float ySize;

        float rotateX;
        float rotateY;
        float rotateZ;

        float xMin;
        float xMax;
        float yMin;
        float yMax;

        vec vertices[4];

    protected:

    private:
};

#endif // OBJECTS_H
