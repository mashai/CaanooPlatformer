#include "CSpriteComponent.h"

//Class CSpriteComponent

CSpriteComponent::CSpriteComponent(std::string image){

    m_id = eSprite;
    m_type = DRAWABLE;
    m_position = NULL;

    m_graphicId = GRAPHICS->createSprite(image);
    m_width = GRAPHICS->getSpriteWidth(m_graphicId);
    m_height = GRAPHICS->getSpriteHeight(m_graphicId);
    m_screenWidth = GRAPHICS->getWidth();
    m_screenHeight = GRAPHICS->getHeight();
}

void CSpriteComponent::onExecute(){

    if(m_position == NULL) return;
    Vector2 position = m_position->getPosition();
    if(position.x > m_screenWidth || position.y > m_screenHeight) return;
    GRAPHICS->drawSprite(m_graphicId, position.x, position.y);
}

void CSpriteComponent::onComponentAdded(CComponent* component){

    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
}


