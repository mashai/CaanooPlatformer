#ifndef CSCENE_MANAGER_H
#define CSCENE_MANAGER_H

#include "CPositionComponent.h"
#include "CColliderComponent.h"
#include "CSpriteComponent.h"
#include "CScrollerComponent.h"
#include "CBackgroundComponent.h"
#include "CMoverComponent.h"
#include "CPlayerComponent.h"
#include "CMoveToTargetComponent.h"
#include "CKillComponent.h"
#include "CShooterComponent.h"
#include "CMoveInDirectionComponent.h"
#include "CShootAtTargetComponent.h"
#include "CDieByBulletComponent.h"
#include "CDieOffscreenComponent.h"

#include <vector>

class CSceneManager{
    public:

        //Constructor
        CSceneManager();

        //Destructor
        ~CSceneManager();

        //onInit - handles loading of data
        void onInit();

        //onCleanUp - cleans up memory used
        void OnCleanUp();

        //onEvent - handles input events
        void onEvent(SDL_Event event);

        //onUpdate - handles updating of entities
        void onUpdate();

        //onrender - handles drawing of entities
        void onRender();

        //playerWin - return true if player won
        bool playerWin(){return m_gameWon;}

    private:

        //loadLevel - loads scene data
        void loadLevel();

        //checkBulletFired - creates bullet if entity fired
        void checkBulletFired();

        //createEntity - creates an entity with given components
        int createEntity(std::vector<CComponent*> components);

        //removeEntity - deletes entity with given id
        void removeEntity(int id);

        //findAllComponentsWithId - returns a list of components with id
        std::vector<CComponent*> findAllComponentsWithId(CComponent::componentId id);

        //findEntityComponent - returns component with given id from entity with given id
        CComponent* findEntityComponent(CComponent::componentId id, int entityId);

        //member variables
        bool m_gameWon;
        int m_bossId;
        int m_playerId;
        int m_entityCount;
        std::vector<CComponent*> m_componentList;
};

#endif // CSCENE_MANAGER_H



