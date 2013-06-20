#include "CBackgroundComponent.h"

//Class CBackgroundComponent

CBackgroundComponent::CBackgroundComponent(std::string image){

    m_id = eBackground;
    m_type = DRAWABLE;
    m_position = NULL;

    m_graphicId = GRAPHICS->createSprite(image);
    m_width = GRAPHICS->getSpriteWidth(m_graphicId);
    m_height = GRAPHICS->getSpriteHeight(m_graphicId);
    m_screenWidth = GRAPHICS->getWidth();
    m_screenHeight = GRAPHICS->getHeight();
}

void CBackgroundComponent::onExecute(){

    if(m_position == NULL) return;

    Vector2 position = m_position->getPosition();
    if(position.x >= m_screenWidth || position.x <= -m_width) m_position->setPosition(Vector2(0.0f, 0.0f));

    Vector2 offset = position;
    if(position.x > 0) offset.x = position.x - m_width;
    if(position.x < 0) offset.x = position.x + m_width;

    GRAPHICS->drawSprite(m_graphicId, position.x, position.y);
    GRAPHICS->drawSprite(m_graphicId, offset.x, offset.y);

}

void CBackgroundComponent::onComponentAdded(CComponent* component){

    if(component->getId() == ePosition) m_position = (CPositionComponent*)component;
}



