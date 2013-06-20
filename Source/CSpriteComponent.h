#ifndef CSPRITE_COMPONENT_H
#define CSPRITE_COMPONENT_H

#include "CComponent.h"
#include "CPositionComponent.h"

class CSpriteComponent : public CComponent{
    public:

        //Constructor
        CSpriteComponent(std::string image);

        //Destructor
        ~CSpriteComponent(){}

        //onExecute - executes component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

    protected:

        int m_width;
        int m_height;
        int m_screenWidth;
        int m_screenHeight;
        uint m_graphicId;
        CPositionComponent* m_position;
};

#endif // CSPRITE_COMPONENT_H






