#include "CDieByBulletComponent.h"

//Class CDieByBulletComponent

CDieByBulletComponent::CDieByBulletComponent(int health){

    m_id = eDieByBullet;
    m_type = UPDATATBLE;

    m_kill = NULL;
    m_position = NULL;
    m_collider = NULL;

    m_health = health;
}

void CDieByBulletComponent::onExecute(){

    if(m_kill == NULL) return;
    if(m_position == NULL) return;
    if(m_collider == NULL) return;

    Vector2 position = m_position->getPosition();
    if(m_collider->isCollidingWithType(position, Collider::eBullet)) m_health--;
    if(m_health <= 0) m_kill->kill();
}

void CDieByBulletComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eKill) m_kill = (CKillComponent*)component;
    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
    if(component->getId() == eCollider) m_collider = (CColliderComponent*)component;
}








