#ifndef _CHECKCOLLISION_H
#define _CHECKCOLLISION_H

#include <math.h>

class _checkCollision
{
    public:
        _checkCollision();
        virtual ~_checkCollision();

        bool isLinearCollision(float, float); //2D
        bool isRadialCollision(float, float, float, float, float, float); //2D

        bool isCircleRayCollision(float, float, float, float, float); //3D
        bool isCubicCollision(float, float, float, float); //3D
        bool isSpereCollition(float, float, float, float); // 3D

        bool isCollisionFloor(float, float, float);

    protected:

    private:
};

#endif // _CHECKCOLLISION_H
