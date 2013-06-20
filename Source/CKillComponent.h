#ifndef CKILL_COMPONENT_H
#define CKILL_COMPONENT_H

#include "CComponent.h"
#include "CColliderComponent.h"

class CKillComponent : public CComponent{
    public:

        //Constructor
        CKillComponent();

        //Destructor
        ~CKillComponent(){};

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //isDead - returns true if killed
        bool isDead() {return m_killed;}

        //kill - kills entity
        void kill();

    protected:

        bool m_killed;
        CColliderComponent* m_collider;

};

#endif // CKILL_COMPONENT_H











