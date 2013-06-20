#ifndef CSHOOTER_COMPONENT_H
#define CSHOOTER_COMPONENT_H

#include "CComponent.h"

class CShooterComponent : public CComponent{
    public:

        //Constructor
        CShooterComponent(int shotDamage, std::string bulletSprite);

        //Destructor
        ~CShooterComponent(){};

        //shoot - makes entity shoot at given position in given direction
        virtual void shoot(Vector2 position, int direction);

        //getShootingData - returns bullet position, direction, damage and sprite if bullet has been shot
        bool getShootingData(Vector2 & position, int &direction, int &damage, std::string &sprite);

    protected:

        bool m_hasShot;
        int m_direction;
        int m_shotDamage;
        Vector2 m_position;
        std::string m_bulletSprite;
};

#endif // CSHOOTER_COMPONENT_H












