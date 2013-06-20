#ifndef CMOVE_TO_TARGET_COMPONENT_H
#define CMOVE_TO_TARGET_COMPONENT_H

#include "CComponent.h"
#include "CMoverComponent.h"
#include "CPositionComponent.h"

class CMoveToTargetComponent : public CComponent{
    public:

        //Constructor
        CMoveToTargetComponent(float sightRadius);

        //Destructor
        ~CMoveToTargetComponent(){};

        //onExecute - executes the component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //setSpeed - sets speed to given value
        void setTarget(Collider* target){m_target = target;}

    protected:

        float m_sightRadius;
        Collider* m_target;

        CMoverComponent* m_mover;
        CPositionComponent* m_position;
        CColliderComponent* m_collider;
};

#endif // CMOVE_TO_TARGET_COMPONENT_H











