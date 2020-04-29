#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <GL/gl.h>
#include <textureLoader.h>
#include <player.h>



class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar();

        void drawHealthBar();
        void initHealthBar(char *);
        void healthBarActions(int); // pass in character variable for actions based on words
        void placeHealthBar(float, float, float);

        float xPos, yPos, zPos;
        float xMin, yMin, xMax, yMax;
        float frames;
        float xSize, ySize;

    protected:

    private:
};

#endif // HEALTHBAR_H
