#ifndef INPUTS_H
#define INPUTS_H
#include<windows.h>
#include <Parallax.h>
#include<player.h>
#include <StateManager.h>

class Inputs
{
    public:
        Inputs();
        virtual ~Inputs();


//        void keyPressed( StateManager*, _Sound*);
        void keyPressed( StateManager*);

//        void keyPressed(Model *, StateManager*);
//        void keyPressed(_Sound *);
        void keyUp(); // key up function to pause soon


//        void keyPressed( StateManager*);
//        void keyUp();


        void manualParallax(Parallax *, float); //move parallax by keys


        void mouseEventDown(double, double);
        void mouseEventUp();
        void mouseEventWheel(double);
        void mouseEventMove(double, double);
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
