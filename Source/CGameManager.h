#ifndef CGAME_MANAGER_H
#define CGAME_MANAGER_H

#include "CSceneManager.h"
#include <SDL.h>
#include <queue>
#include <iostream>


class CGameManager{
    public:

        CGameManager();

        int onExecute();

        //onInit - handles loading of data
        bool onInit();

        //onEvent - handles input events
        void onEvent(SDL_Event event);

        //onUpdate - handles updating of entities and data
        void onUpdate();

        //onrender - handles drawing of entities
        void onRender();

        //onClean - cleans up ressources used
        void onCleanUp();

        //onExit - exits program
        void onExit();

    private:

        bool m_running;
        bool m_debugging;
        int m_frameRate;
        SDL_Joystick* m_joy;
        SDL_Surface* m_screen;
        uint m_debugScreenSprite;
        CSceneManager* m_sceneManager;
        //std::queue<ICommand*> m_commandQueue;
};

#endif // CGAME_MANAGER_H


