#ifndef STATEMANAGER_H
#define STATEMANAGER_H


enum GameStates{LANDING,MENU,GAME,PAUSED,HELP,QUIT,CREDITS}; // Array of different game states to be in.


class StateManager
{
    public:
        StateManager();
        virtual ~StateManager();

         GameStates _gameState = LANDING; // Initialize the starting screen to be LANDING (The landing screen)\


    protected:

    private:
};

#endif // STATEMANAGER_H
