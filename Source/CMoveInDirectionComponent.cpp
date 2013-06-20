#include "CMoveInDirectionComponent.h"

//Class CMoveInDirectionComponent

CMoveInDirectionComponent::CMoveInDirectionComponent(int direction, float speed){

    m_id = eMoveInDirection;
    m_type = UPDATATBLE;

    m_speed = speed;
    m_direction = direction;
    m_position = NULL;
}

void CMoveInDirectionComponent::onExecute(){

    if(m_position == NULL) return;
    m_position->move(Vector2(m_speed * m_direction, 0.0f));
}

void CMoveInDirectionComponent::onComponentAdded(CComponent* component){

    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
}













