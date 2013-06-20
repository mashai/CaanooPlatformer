#include "CKillComponent.h"

//Class CKillComponent

CKillComponent::CKillComponent(){

    m_id = eKill;
    m_type = NONE;

    m_killed = false;
    m_collider = NULL;
}

void CKillComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eCollider) m_collider = (CColliderComponent*)component;
}

void CKillComponent::kill(){

    m_killed = true;

    if(m_collider != NULL) m_collider->removeCollider();
}
