#ifndef PLAYER_H
#define PLAYER_H

#include<GL/gl.h>
#include<TextureLoader.h>

typedef struct
{
    float x;
    float y;
    float z;
}vec;

class player
{
    public:
        player();
        virtual ~player();

        void drawPlayer();
        void playerInit(char *);
        void playerActions(); // pass in character variable for actions based on words

        string actionTrigger;
        vec vertices[4];
        float xMin, yMin, xMax, yMax;

        float xPos, yPos, zPos;

    protected:

    private:
};

#endif // PLAYER_H
