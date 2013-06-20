#ifndef CPOSITION_COMPONENT_H
#define CPOSITION_COMPONENT_H

#include "CComponent.h"
#include "CColliderComponent.h"

class CPositionComponent: public CComponent{
    public:

        //Constructor
        CPositionComponent(Vector2 position);

        //Destructor
        ~CPositionComponent(){}

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //move - moves position by given amount
        void move(Vector2 amount);

        //getPosition - return value of position
        Vector2 getPosition() {return m_position;}

        //setPosition - sets a value to position
        void setPosition(Vector2 position);

    protected:

        Vector2 m_position;
        Collider* m_collider;
};

#endif // CPOSITION_COMPONENT_H






