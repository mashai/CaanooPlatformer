#ifndef CDIE_BY_BULLET_COMPONENT_H
#define CDIE_BY_BULLET_COMPONENT_H

#include "CComponent.h"
#include "CKillComponent.h"
#include "CPositionComponent.h"
#include "CColliderComponent.h"

class CDieByBulletComponent : public CComponent{
    public:

        //Constructor
        CDieByBulletComponent(int health);

        //Destructor
        ~CDieByBulletComponent(){};

        //onExecute - executes the component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

    protected:

        int m_health;

        CKillComponent* m_kill;
        CPositionComponent* m_position;
        CColliderComponent* m_collider;
};

#endif // CMOVE_TO_TARGET_COMPONENT_H












