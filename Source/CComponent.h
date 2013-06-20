#ifndef CCOMPONENT_H
#define CCOMPONENT_H

#include "CUtils.h"

class CComponent{
    public:

        enum componentId {
        eNull,
        eBackground,
        eCollider,
        eDebug,
        eDieByBullet,
        eDieOffScreen,
        eKill,
        eMover,
        eMoveInDirection,
        eMoveToTarget,
        ePlayer,
        ePosition,
        eScroller,
        eShooter,
        eShootAtTarget,
        eSprite,
        eNumComponents
        };

        enum ComponentType {NONE, DRAWABLE, UPDATATBLE};

        //Constructor
        CComponent(): m_order(0), m_entityId(-1), m_id(eNull), m_type(NONE) {}

        //Destructor
        ~CComponent(){}

        //onInit - handles initialization of component
        virtual void onInit() {}

        //onExecute - executes the component
        virtual void onExecute() {}

        //onEvent - handles event
        virtual void onEvent(SDL_Event event) {}

        //onComponentAdded - informs component another component was added to entity
        virtual void onComponentAdded(CComponent* component){}

        //setOrder - sets the order in which the component should be executed
        void setOrder(int order) {m_order = order;}

        //getOrder - returns order in which component should be executed
        int getOrder() {return m_order;}

        //getEntityId - returns entity's ID
        int getEntityId() {return m_entityId;}

        //getID - returns component's ID
        componentId getId() {return m_id;}

        //getType - returns component's type
        ComponentType getType() {return m_type;}

        //setEntityId - sets entity's id
        void setEntityId(int id) {m_entityId = id;}

    protected:
        int m_order;
        int m_entityId;
        componentId m_id;
        ComponentType m_type;
};

#endif //CCOMPONENT_H





