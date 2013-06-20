#include "CScrollerComponent.h"

//Class CScrollerComponent

CScrollerComponent::CScrollerComponent(float speed){

    m_id = eScroller;
    m_type = NONE;
    m_position = NULL;

    m_speed = speed;
}

void CScrollerComponent::onComponentAdded(CComponent* component){

    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
}

void CScrollerComponent::move(int amount){

    if(m_position == NULL) return;
    m_position->move(Vector2(amount * m_speed, 0.0f));
}

