#include "CColliderComponent.h"

//Class CColliderComponent

CColliderComponent::CColliderComponent(int width, int height, Collider::collisionType type, Vector2 offset){

    m_id = eCollider;
    m_type = NONE;

    m_size = Vector2(width, height);
    m_collider = new Collider(0, 0, width, height, type, offset.x, offset.y);
    COLLISIONS->registerCollider(m_collider);
}

CColliderComponent::~CColliderComponent(){

    COLLISIONS->removeCollider(m_collider);
}

bool CColliderComponent::isCollidingWithType(Vector2 position, Collider::collisionType type){

    Rect rectangle;
    return isCollidingWithType(position, m_size, type, rectangle);
}

bool CColliderComponent::isCollidingWithType(Vector2 position, Collider::collisionType type, Rect &colliderRect){

    return isCollidingWithType(position, m_size, type, colliderRect);
}

bool CColliderComponent::isCollidingWithType(Vector2 position, Vector2 size, Collider::collisionType type){

    Rect rectangle;
    return isCollidingWithType(position, size, type, rectangle);
}

bool CColliderComponent::isCollidingWithType(Vector2 position, Vector2 size, Collider::collisionType type, Rect &colliderRect){

    //store collider position
    Vector2 colliderPos = Vector2(m_collider->posx, m_collider->posy);

    //change collider to given position and size
    m_collider->posx = position.x;
    m_collider->posy = position.y;
    m_collider->width = size.x;
    m_collider->height = size.y;

    Collider* collider = COLLISIONS->isCollidingWithType(m_collider, type);

    //restore collider position and size
    m_collider->posx = colliderPos.x;
    m_collider->posy = colliderPos.y;
    m_collider->width = m_size.x;
    m_collider->height = m_size.y;

    if(collider == NULL) return false;

    colliderRect.x = collider->posx;
    colliderRect.y = collider->posy;
    colliderRect.width = collider->width;
    colliderRect.height = collider->height;

    return true;
}



