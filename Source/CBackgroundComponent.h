#ifndef CBACKGROUND_COMPONENT_H
#define CBACKGROUND_COMPONENT_H

#include "CComponent.h"
#include "CPositionComponent.h"

class CBackgroundComponent : public CComponent{
    public:

        //Constructor
        CBackgroundComponent(std::string image);

        //Destructor
        ~CBackgroundComponent(){};

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

#endif // CBACKGROUND_COMPONENT_H







