#include "CMoveToTargetComponent.h"

//Class CMoveToTargetComponent

CMoveToTargetComponent::CMoveToTargetComponent(float sightRadius){

    m_id = eMoveToTarget;
    m_type = UPDATATBLE;

    m_mover = NULL;
    m_position = NULL;
    m_collider = NULL;

    m_target = NULL;
    m_sightRadius = sightRadius;
}

void CMoveToTargetComponent::onExecute(){

    if(m_mover == NULL) return;
    if(m_target == NULL) return;
    if(m_position == NULL) return;
    if(m_collider == NULL) return;

    Vector2 position = m_position->getPosition();
    Vector2 size = m_collider->getSize();

    float distanceLeft = position.x - m_target->posx +  (m_target->width * 0.5f);
    float distanceRight = m_target->posx +  (m_target->width * 0.5f) - (position.x + size.x);

    if(distanceLeft < m_sightRadius && distanceLeft > 0 && m_collider->isCollidingWithType(Vector2(position.x - size.x, position.y + size.y), Collider::eGround)) m_mover->move(-1);
    else if(distanceRight < m_sightRadius && distanceRight > 0 && m_collider->isCollidingWithType(Vector2(position.x + size.x, position.y + size.y), Collider::eGround)) m_mover->move(1);
    else m_mover->move(0);
}

void CMoveToTargetComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eMover) m_mover = (CMoverComponent*)component;
    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
    if(component->getId() == eCollider) m_collider = (CColliderComponent*)component;
}







