#include "CMoverComponent.h"

//Class CMoverComponent

CMoverComponent::CMoverComponent(float speed, float jumpingImpulse, float gravity){

    m_id = eMover;
    m_type = UPDATATBLE;

    m_speed = speed;
    m_direction = 0;
    m_gravity = gravity;

    m_jumping = false;
    m_jumpingSpeed = 0;
    m_jumpingDirection = 0;
    m_jumpingImpulse = jumpingImpulse;

    m_position = NULL;
    m_collider = NULL;
}

void CMoverComponent::onExecute(){

    if(m_position == NULL) return;
    if(m_collider == NULL) return;

    Rect collisionRect;
    Vector2 size = m_collider->getSize();
    Vector2 groundSize = Vector2(size.x, 3.0f);
    Vector2 position = m_position->getPosition();
    Vector2 belowGroundPos = Vector2(position.x, position.y + (size.y + 1));
    Vector2 groundPos = Vector2(position.x, position.y + (size.y - groundSize.y));

    //check if falling
    if(!m_jumping && !m_collider->isCollidingWithType(belowGroundPos, groundSize, Collider::eGround))
    {
        m_jumping = true;
        m_jumpingDirection = 0;
    }

    if(m_jumping)
    {
        position.y += m_jumpingSpeed;
        position.x += m_speed * m_jumpingDirection;

        //if left screen
        if(position.y >= GRAPHICS->getHeight()) m_jumpingSpeed = 0;

        //if colliding, stop jumping
        if(m_collider->isCollidingWithType(groundPos, groundSize, Collider::eGround, collisionRect))
        {
            m_jumping = false;
            m_jumpingSpeed = 0;
            position.y = collisionRect.y - size.y;
        }

        m_jumpingSpeed += m_gravity;
        m_position->setPosition(position);
    }
    else
    {
        position.x += m_speed * m_direction;

        //if collision, set position just before collision
        //if(m_collider->isCollidingWithType(position, Collider::eActor, collisionRect))
        //{
        //    if(m_direction == 1) position.x = collisionRect.x - size.x;
        //    else if(m_direction == -1) position.x = collisionRect.x  + collisionRect.width;
        //}
        m_position->setPosition(position);
    }
}

void CMoverComponent::onComponentAdded(CComponent* component){

    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
    if(component->getId() == eCollider) m_collider = (CColliderComponent*)component;
}

void CMoverComponent::jump() {

    if(m_jumping) return;

    m_jumping = true;
    m_jumpingDirection = m_direction;
    m_jumpingSpeed = -m_jumpingImpulse;
}






