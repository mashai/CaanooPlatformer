#include "CPlayerComponent.h"

//Class CPlayerComponent

CPlayerComponent::CPlayerComponent(float shootingDelay, int shootingHeight){

    m_id = ePlayer;
    m_type = UPDATATBLE;
    m_mover = NULL;

    m_direction = 1;
    m_shootingDelay = shootingDelay;
    m_shootingHeight = shootingHeight;
    m_lastShootingTime = shootingDelay + (SDL_GetTicks() /100);

    m_kill = NULL;
    m_mover = NULL;
    m_shooter = NULL;
    m_collider = NULL;
    m_position = NULL;
}

void CPlayerComponent::onExecute(){

    if(m_position == NULL) return;
    if(m_kill == NULL) return;

    Vector2 position = m_position->getPosition();
    if(position.y >= GRAPHICS->getHeight())
    {
        m_kill->kill();
    }

    if(m_collider == NULL) return;

    //if collision with actor, kill
    if(m_collider->isCollidingWithType(position, Vector2(10, 20), Collider::eActor)) m_kill->kill();

    //if collision with bullet, kill
    if(m_collider->isCollidingWithType(position, Collider::eBullet)) m_kill->kill();

    int direction = m_mover->getDirection();
    if(direction != 0) m_direction = direction;

    if(m_direction == 1) m_bulletPos = Vector2(position.x + m_entitySize.x + 20, (position.y  + m_entitySize.y) - m_shootingHeight);
    else if (m_direction == -1) m_bulletPos = Vector2(position.x - 5, (position.y  + m_entitySize.y) - m_shootingHeight);

}

void CPlayerComponent::onEvent(SDL_Event event){

    float time = SDL_GetTicks() / 100;

    switch (event.type)
    {
        //KEYBOARD
        case SDL_KEYDOWN:

            if(event.key.keysym.sym == SDLK_LEFT && m_mover) m_mover->move(-1);
            else if(event.key.keysym.sym == SDLK_RIGHT && m_mover) m_mover->move(1);
            if(event.key.keysym.sym == SDLK_SPACE && m_mover) m_mover->jump();
            if(event.key.keysym.sym == SDLK_b && m_shooter && time - m_lastShootingTime >= m_shootingDelay)
            {
                m_shooter->shoot(m_bulletPos, m_direction);
                m_lastShootingTime = time;
            }
            break;

          case SDL_KEYUP:

            if((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) && m_mover) m_mover->move(0);;
            break;

        //JOYSTICK
        case SDL_JOYBUTTONDOWN:

             if (event.jbutton.button == CAANOO_BUTTON_X && m_mover) m_mover->jump();
             if (event.jbutton.button == CAANOO_BUTTON_A && m_shooter && time - m_lastShootingTime >= m_shootingDelay)
             {
                    m_shooter->shoot(m_bulletPos, m_direction);
                    m_lastShootingTime = time;
             }
             break;

        case SDL_JOYAXISMOTION:

            if((event.jaxis.value > CAANOO_JOYSTICK_MIN || event.jaxis.value < CAANOO_JOYSTICK_MAX) && m_mover)
            {
                //if left-right movement
                if(event.jaxis.axis == CAANOO_AXIS_X) m_mover->move(event.jaxis.value/CAANOO_JOYSTICK_MAX);

            }
            break;
    }
}

void CPlayerComponent::onComponentAdded(CComponent* component){

    if(component->getId() == eKill) m_kill = (CKillComponent*)component;
    if(component->getId() == eMover) m_mover = (CMoverComponent*)component;
    if(component->getId() == eShooter) m_shooter = (CShooterComponent*)component;
    if(component->getId() == eCollider)
    {
        m_collider = (CColliderComponent*)component;
        m_entitySize = ((CColliderComponent*)component)->getSize();
    }
    if(component->getId() == ePosition)
    {
        m_position = (CPositionComponent*)component;
        m_initialPos = m_position->getPosition();
    }
}

int CPlayerComponent::getAmountMoved(){

    if(m_position == NULL) return 0;

    Vector2 position = m_position->getPosition();
    m_position->setPosition(Vector2(m_initialPos.x, position.y));

    return m_initialPos.x - position.x;
}




