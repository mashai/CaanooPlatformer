#ifndef CCOLLIDER_COMPONENT_H
#define CCOLLIDER_COMPONENT_H

#include "CComponent.h"
#include "CCollisions.h"


class CColliderComponent : public CComponent{
    public:

        //Constructor
        CColliderComponent(int width, int height, Collider::collisionType type, Vector2 offset = Vector2(0,0));

        //Destructor
        ~CColliderComponent();

        //isCollidingWithType - returns true if entity colliding at given position
        bool isCollidingWithType(Vector2 position, Collider::collisionType type);

        //isCollidingWithType- returns true if entity colliding at given position
        bool isCollidingWithType(Vector2 position, Collider::collisionType type, Rect &colliderRect);

        //isCollidingWithType- returns true if entity colliding at given position with given size
        bool isCollidingWithType(Vector2 position, Vector2 size, Collider::collisionType type);

        //isCollidingWithType- returns true if entity colliding at given position with given size
        bool isCollidingWithType(Vector2 position, Vector2 size, Collider::collisionType type, Rect &colliderRect);

        //getCollider - returns collider
        Collider* getCollider() {return m_collider;}

        //removeCollider - removes collider from collisions
        void removeCollider() {COLLISIONS->removeCollider(m_collider);}

        //getSize - returns size
        Vector2 getSize() {return m_size;}

    protected:

        Vector2 m_size;
        Collider* m_collider;
};

#endif // CCOLLIDER_COMPONENT_H









