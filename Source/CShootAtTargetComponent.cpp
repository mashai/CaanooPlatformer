#include "CShootAtTargetComponent.h"

//Class CShootAtTargetComponent

CShootAtTargetComponent::CShootAtTargetComponent(float sightRadius, float shootingDelay, int shootingHeight){

    m_id = eShootAtTarget;
    m_type = UPDATATBLE;

    m_target = NULL;
    m_sightRadius = sightRadius;
    m_shootingDelay = shootingDelay;
    m_shootingHeight = shootingHeight;
    m_lastShootingTime = shootingDelay + (SDL_GetTicks() /100);

    m_shooter = NULL;
    m_position = NULL;
}

void CShootAtTargetComponent::onExecute(){

    if(m_target == NULL) return;
    if(m_shooter == NULL) return;
    if(m_position == NULL) return;

    Vector2 position = m_position->getPosition();

    //if target out of sight, return
    if(position.x - (m_target->posx + m_target->width) < m_sightRadius)
    {
        Vector2 bulletPos = Vector2(position.x - 10, (position.y  + m_size.y) - m_shootingHeight);

        float time = SDL_GetTicks() / 100;
        if(time - m_lastShootingTime >= m_shootingDelay)
        {
            m_shooter->shoot(bulletPos, -1);
            m_lastShootingTime = time;
        }
    }
    else m_lastShootingTime = m_shootingDelay + (SDL_GetTicks() /100);
}

void CShootAtTargetComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eShooter) m_shooter = (CShooterComponent*)component;
    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
    if(component->getId() == eCollider) m_size = ((CColliderComponent*)component)->getSize();
}









