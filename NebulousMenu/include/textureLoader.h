#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <SOIL.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

class textureLoader
{
    public:
        textureLoader();
        virtual ~textureLoader();

        void binder();
        void loadTexture(char* );

        unsigned char* image;
        int width, height;

        GLuint tex;




    protected:

    private:
};

#endif // TEXTURELOADER_H
