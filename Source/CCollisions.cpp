
#include "CCollisions.h"

//Singleton class CCollisions

CCollisions* CCollisions::m_instance = 0;

CCollisions::CCollisions(): m_init(0){}

CCollisions* CCollisions::instance() {

    //if instance has never been called before
    if(m_instance == 0)
    {
        //call constructor
        m_instance = new CCollisions();
    }
    //always return pointer to the CGraphic instance
    return m_instance;
}

bool CCollisions::init(){

    m_init = 1;
    return true;
}

void CCollisions::destroy() {

    clear();

    //delete allocateed memory for CCollisions
    if(m_instance)
    {
        delete m_instance;
    }
    m_instance = 0;
}

void CCollisions::clear(){

    int size = 10;
    size = m_colliderList.size();
    m_colliderList.clear();
}

void CCollisions::registerCollider(Collider* collider){

    //if CCollisions not initialized, return
    if(m_init == 0) return;

    m_colliderList.push_back(collider);
}

void CCollisions::removeCollider(Collider* collider){

    //if CCollisions not initialized, return
    if(m_init == 0) return;

    m_colliderList.remove(collider);
}

Collider* CCollisions::isCollidingWithType(Collider* collider, Collider::collisionType type){

    //if CCollisions not initialized, return
    if(m_init == 0) return NULL;

    for(std::list<Collider*>::iterator it = m_colliderList.begin(); it != m_colliderList.end(); it++)
    {
        if(*it != collider && (*it)->type == type)
        {
            int colliderX = collider->posx + collider->offsetx;
            int otherX = (*it)->posx + (*it)->offsetx;

            //if collision on x-axis
            if(colliderX < (otherX + (*it)->width) && (colliderX + collider->width) > otherX)
            {
                int colliderY = collider->posy - collider->offsety;
                int otherY = (*it)->posy - (*it)->offsety;

                //if collision on y-axis
                if(colliderY < (otherY +(*it)->height) && (colliderY + collider->height) > otherY)
                {
                    return *it;
                }
            }
        }
    }

    return NULL;
}

