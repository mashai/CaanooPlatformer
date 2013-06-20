#ifndef CCOLLISIONS_H
#define CCOLLISIONS_H

#include <list>

#define uint unsigned int
#define COLLISIONS CCollisions::instance()

//Collider class
class Collider{
    public:

        int posx, posy;
        int width, height;
        int offsetx, offsety;
        enum collisionType { eBullet, eActor, eGround, eNumCollisions} type;

        Collider(int x, int y, int w, int h, collisionType t, int ox, int oy): posx(x), posy(y), width(w), height(h), offsetx(ox), offsety(oy), type(t){}

};

//Singleton class CCollisions
class CCollisions {
    public:

        static CCollisions* instance();

        //init - initializes the values needed for CCollisions
		bool init();

		//destroy - deletes the memory used in CCollisions
		void destroy();

		//clear - deletes all colliders
		void clear();

        //createCollider - registers given collider
        void registerCollider(Collider* collider);

        //removeCollider - removes collider from collisions
        void removeCollider(Collider* collider);

        //isColliding - returns collider if collision, else null
        Collider* isCollidingWithType(Collider* collider, Collider::collisionType type);


    private:

        //constructor - only gets called once
        CCollisions();

        //Data members
        bool m_init;
        static CCollisions* m_instance;
        std::list<Collider*> m_colliderList;

};

#endif // CCOLLISIONS_H


