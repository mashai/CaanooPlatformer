#ifndef CPLAYER_COMPONENT_H
#define CPLAYER_COMPONENT_H

#include "CComponent.h"
#include "CKillComponent.h"
#include "CMoverComponent.h"
#include "CShooterComponent.h"
#include "CColliderComponent.h"
#include "CPositionComponent.h"

class CPlayerComponent : public CComponent{
    public:

        //Constructor
        CPlayerComponent(float shootingDelay, int shootingHeight);

        //Destructor
        ~CPlayerComponent(){};

        //onExecute - executes component
        void onExecute();

        //onEvent - handles event
        void onEvent(SDL_Event event);

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //getAmountMoved - returns amount moved on x axis
        int getAmountMoved();


    private:

        int m_direction;
        int m_shootingHeight;
        Vector2 m_initialPos;
        Vector2 m_entitySize;
        Vector2 m_bulletPos;
        float m_shootingDelay;
        float m_lastShootingTime;

        CKillComponent* m_kill;
        CMoverComponent* m_mover;
        CShooterComponent* m_shooter;
        CColliderComponent* m_collider;
        CPositionComponent* m_position;

};

#endif // CPLAYER_COMPONENT_H











