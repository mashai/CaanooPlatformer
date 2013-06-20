#ifndef CSHOOT_AT_TARGET_COMPONENT_H
#define CSHOOT_AT_TARGET_COMPONENT_H

#include "CComponent.h"
#include "CShooterComponent.h"
#include "CPositionComponent.h"
#include "CColliderComponent.h"


class CShootAtTargetComponent : public CComponent{
    public:

        //Constructor
        CShootAtTargetComponent(float sightRadius, float shootingDelay, int shootingHeight);

        //Destructor
        ~CShootAtTargetComponent(){};

        //onExecute - executes the component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //setSpeed - sets speed to given value
        void setTarget(Collider* target){m_target = target;}

    protected:

        int m_shootingHeight;
        float m_sightRadius;
        float m_shootingDelay;
        float m_lastShootingTime;
        Collider* m_target;
        Vector2 m_size;

        CShooterComponent* m_shooter;
        CPositionComponent* m_position;
};

#endif // CSHOOT_AT_TARGET_COMPONENT_H













