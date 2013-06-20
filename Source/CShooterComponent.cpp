#include "CShooterComponent.h"

//Class CShooterComponent

CShooterComponent::CShooterComponent(int shotDamage, std::string bulletSprite){

    m_id = eShooter;
    m_type = NONE;

    m_hasShot = false;
    m_shotDamage = shotDamage;
    m_bulletSprite = bulletSprite;
}

void CShooterComponent::shoot(Vector2 position, int direction){

    m_hasShot = true;
    m_position = position;
    m_direction = direction;
}

bool CShooterComponent::getShootingData(Vector2 & position, int &direction, int &damage, std::string &sprite){

    if(!m_hasShot) return false;

    position = m_position;
    direction = m_direction;
    damage = m_shotDamage;
    sprite = m_bulletSprite;
    m_hasShot = false;

    return true;
}











