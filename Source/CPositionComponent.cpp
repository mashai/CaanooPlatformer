#include "CPositionComponent.h"

//Class CPositionComponent

CPositionComponent::CPositionComponent(Vector2 position){

    m_id = ePosition;
    m_type = NONE;

    m_collider = NULL;
    m_position = position;
}

void CPositionComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eCollider)
    {
        CColliderComponent* colliderComponent = (CColliderComponent*)component;
        m_collider = colliderComponent->getCollider();
        m_collider->posx = m_position.x;
        m_collider->posy = m_position.y;
    }
}

void CPositionComponent::move(Vector2 amount){

    m_position = m_position + amount;
    if(m_collider != NULL)
    {
        m_collider->posx = m_position.x;
        m_collider->posy = m_position.y;
    }
}

void CPositionComponent::setPosition(Vector2 position){

    m_position = position;
    if(m_collider != NULL)
    {
        m_collider->posx = m_position.x;
        m_collider->posy = m_position.y;
    }
}



