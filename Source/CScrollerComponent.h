#ifndef CSCROLLER_COMPONENT_H
#define CSCROLLER_COMPONENT_H

#include "CComponent.h"
#include "CPositionComponent.h"

class CScrollerComponent : public CComponent{
    public:

        //Constructor
        CScrollerComponent(float speed = 1.0f);

        //Destructor
        ~CScrollerComponent(){}

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

        //move - move by amount
        void move(int amount);

        //setSpeed - sets speed to given value
        void setSpeed(float speed) {m_speed = speed;}

        //getSpeed - returns speed
        float getSpeed() {return m_speed;}

    protected:

        float m_speed;
        CPositionComponent* m_position;
};

#endif // CSCROLLER_COMPONENT_H







