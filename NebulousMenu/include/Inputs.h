#ifndef INPUTS_H
#define INPUTS_H
#include<windows.h>
#include<Model.h>
#include <Parallax.h>
#include<player.h>
#include <StateManager.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();

        void keyPressed(Model *, StateManager*);
        void keyUp();

        void manualParallax(Parallax *, float); //move parallax by keys


        void mouseEventDown(Model *, double, double);
        void mouseEventUp();
        void mouseEventWheel(Model *, double);
        void mouseEventMove(Model *, double, double);
        void playerAction(player *);

        double prev_mouse_X;
        double prev_mouse_Y;

        bool mouse_Translate;
        bool mouse_Rotate;


        WPARAM wParam;


    protected:

    private:
};

#endif // INPUTS_H
