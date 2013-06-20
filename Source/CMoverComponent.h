#ifndef CMOVER_COMPONENT_H
#define CMOVER_COMPONENT_H

#include "CComponent.h"
#include "CPositionComponent.h"
#include "CColliderComponent.h"

class CMoverComponent : public CComponent{
    public:

        //Constructor
        CMoverComponent(float speed, float jumpingImpulse, float gravity = 0.6f);

        //Destructor
        ~CMoverComponent(){};

        //onExecute - executes the component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //jump - makes entity jump
        void jump();

        //move - moves entity in given direction if allowed
        void move(int direction) {m_direction = direction;}

        //setSpeed - sets speed to given value
        void setSpeed(float speed){m_speed = speed;}

        //setSpeed - sets speed to given value
        void setJumpingImpulse(float impulse){m_jumpingImpulse = impulse;}

        //getDirection - returns direction
        int getDirection() {return m_direction; }

    protected:

        int m_direction;
        float m_speed;
        float m_gravity;

        bool m_jumping;
        float m_jumpingSpeed;
        float m_jumpingImpulse;
        int m_jumpingDirection;

        CPositionComponent* m_position;
        CColliderComponent* m_collider;
};

#endif // CMOVER_COMPONENT_H










