#ifndef CMOVE_IN_DIRECTION_COMPONENT_H
#define CMOVE_IN_DIRECTION_COMPONENT_H

#include "CComponent.h"
#include "CPositionComponent.h"

class CMoveInDirectionComponent : public CComponent{
    public:

        //Constructor
        CMoveInDirectionComponent(int direction, float speed = 3.0f);

        //Destructor
        ~CMoveInDirectionComponent(){};

        //onExecute - executes component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

    protected:

        int m_direction;
        float m_speed;
        CPositionComponent* m_position;
};

#endif // CMOVE_IN_DIRECTION_COMPONENT_H














