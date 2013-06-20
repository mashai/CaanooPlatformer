#include "CDieOffscreenComponent.h"

//Class CDieOffscreenComponent

CDieOffscreenComponent::CDieOffscreenComponent(){
    m_id = eDieOffScreen;
    m_type = UPDATATBLE;

    m_kill = NULL;
    m_position = NULL;
}

void CDieOffscreenComponent::onExecute(){

    if(m_kill == NULL) return;
    if(m_position == NULL) return;

    Vector2 position = m_position->getPosition();
    if(position.x < 0 || position.x > GRAPHICS->getWidth()) m_kill->kill();
}

void CDieOffscreenComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eKill) m_kill = (CKillComponent*)component;
    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
}
