#ifndef CDIE_OFFSCREEN_COMPONENT_H
#define CDIE_OFFSCREEN_COMPONENT_H

#include "CComponent.h"
#include "CKillComponent.h"
#include "CPositionComponent.h"

class CDieOffscreenComponent : public CComponent{
    public:

        //Constructor
        CDieOffscreenComponent();

        //Destructor
        ~CDieOffscreenComponent(){};

        //onExecute - executes the component
        void onExecute();

        //onComponentAdded - informs component another component was added to entity
        void onComponentAdded(CComponent* component);

    protected:

        CKillComponent* m_kill;
        CPositionComponent* m_position;
};

#endif // CDIE_OFFSCREEN_COMPONENT_H















