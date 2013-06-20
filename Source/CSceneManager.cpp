#include "CSceneManager.h"

//Class CSceneManager

CSceneManager::CSceneManager(){
}

CSceneManager::~CSceneManager(){

    OnCleanUp();
}

void CSceneManager::onInit(){

    m_gameWon = false;

    OnCleanUp();

    loadLevel();

    //get player collider and give it to components needing target
    CColliderComponent* playerCollider = (CColliderComponent*)findEntityComponent(CComponent::eCollider, m_playerId);
    Collider* collider = playerCollider->getCollider();

    std::vector<CComponent*> components = findAllComponentsWithId(CComponent::eMoveToTarget);
    for(uint i = 0; i < components.size(); i++)
    {
        CMoveToTargetComponent* moveToTarget = (CMoveToTargetComponent*)components[i];
        moveToTarget->setTarget(collider);
    }

    components = findAllComponentsWithId(CComponent::eShootAtTarget);
    for(uint i = 0; i < components.size(); i++)
    {
        CShootAtTargetComponent* shootAtTarget = (CShootAtTargetComponent*)components[i];
        shootAtTarget->setTarget(collider);
    }
}

void CSceneManager::OnCleanUp(){


    for(uint i = 0; i < m_componentList.size(); i++)
    {
        delete m_componentList[i];
    }

    m_componentList.clear();
    COLLISIONS->clear();
}

void CSceneManager::onEvent(SDL_Event event){

    for(uint i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->onEvent(event);
    }
}

void CSceneManager::onUpdate(){

    //scroll all scrollers by amount player moved
    CPlayerComponent* player = (CPlayerComponent*)findAllComponentsWithId(CComponent::ePlayer).at(0);
    int amount = player->getAmountMoved();

    std::vector<CComponent*> scrollers = findAllComponentsWithId(CComponent::eScroller);
    for(uint i = 0; i < scrollers.size(); i++)
    {
        CScrollerComponent* scroller = (CScrollerComponent*)scrollers[i];
        if(scroller != NULL)scroller->move(amount);
    }

    //check if bullets fired
    checkBulletFired();

    //update all updatable components
    for(uint i = 0; i < m_componentList.size(); i++)
    {
        if(m_componentList[i]->getType() == CComponent::UPDATATBLE)
        {
            m_componentList[i]->onExecute();
        }
    }

    //check if any entity was killed
    CKillComponent* playerKill = (CKillComponent*)findEntityComponent(CComponent::eKill, m_playerId);
    if(playerKill->isDead()) onInit();

    CKillComponent* bossKill = (CKillComponent*)findEntityComponent(CComponent::eKill, m_bossId);
    if(bossKill->isDead()) m_gameWon = true;;

    std::vector<CComponent*> killers = findAllComponentsWithId(CComponent::eKill);
    for(uint i = 0; i < killers.size(); i++)
    {
        CKillComponent* kill = (CKillComponent*)killers[i];
        if(kill->isDead()) removeEntity(kill->getEntityId());
    }
}

void CSceneManager::onRender(){


    //render all drawable components
    for(uint i = 0; i < m_componentList.size(); i++)
    {
        if(m_componentList[i]->getType() == CComponent::DRAWABLE)
        {
            m_componentList[i]->onExecute();
        }
    }
}

void CSceneManager::loadLevel(){

    std::vector<CComponent*> components;

    components.push_back(new CPositionComponent(Vector2(0, 0)));
    components.push_back(new CBackgroundComponent("background.bmp"));
    components.push_back(new CScrollerComponent(0.5f));
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(60, 90)));
    components.push_back(new CSpriteComponent("player.bmp"));
    components.push_back(new CColliderComponent(10, 50, Collider::eActor, Vector2(10, 0)));
    components.push_back(new CPlayerComponent(1, 30));
    components.push_back(new CMoverComponent(3, 7));
    components.push_back(new CKillComponent);
    components.push_back(new CShooterComponent(1, "bullet.bmp"));
    m_playerId = createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(50, 140)));
    components.push_back(new CSpriteComponent("rock2.bmp"));
    components.push_back(new CColliderComponent(70, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(140, 170)));
    components.push_back(new CSpriteComponent("rock4.bmp"));
    components.push_back(new CColliderComponent(120, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(235, 140)));
    components.push_back(new CSpriteComponent("rock6.bmp"));
    components.push_back(new CColliderComponent(120, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(400, 140)));
    components.push_back(new CSpriteComponent("rock3.bmp"));
    components.push_back(new CColliderComponent(50, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(500, 140)));
    components.push_back(new CSpriteComponent("rock1.bmp"));
    components.push_back(new CColliderComponent(80, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(590, 170)));
    components.push_back(new CSpriteComponent("rock5.bmp"));
    components.push_back(new CColliderComponent(150, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(630, 100)));
    components.push_back(new CSpriteComponent("rock7.bmp"));
    components.push_back(new CColliderComponent(80, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(750, 150)));
    components.push_back(new CSpriteComponent("rock6.bmp"));
    components.push_back(new CColliderComponent(120, 15, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(890, 170)));
    components.push_back(new CSpriteComponent("rock5.bmp"));
    components.push_back(new CColliderComponent(150, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1030, 130)));
    components.push_back(new CSpriteComponent("rock2.bmp"));
    components.push_back(new CColliderComponent(70, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1140, 100)));
    components.push_back(new CSpriteComponent("rock3.bmp"));
    components.push_back(new CColliderComponent(50, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1220, 180)));
    components.push_back(new CSpriteComponent("rock5.bmp"));
    components.push_back(new CColliderComponent(150, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1350, 180)));
    components.push_back(new CSpriteComponent("rock5.bmp"));
    components.push_back(new CColliderComponent(150, 10, Collider::eGround));
    components.push_back(new CScrollerComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(670, 120)));
    components.push_back(new CSpriteComponent("slimeEnemy.bmp"));
    components.push_back(new CColliderComponent(30, 50, Collider::eActor, Vector2(10, 0)));
    components.push_back(new CMoverComponent(1.5f, 10));
    components.push_back(new CScrollerComponent());
    components.push_back(new CMoveToTargetComponent(100));
    components.push_back(new CKillComponent());
    components.push_back(new CDieByBulletComponent(3));
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1050, 90)));
    components.push_back(new CSpriteComponent("slimeEnemy.bmp"));
    components.push_back(new CColliderComponent(30, 50, Collider::eActor, Vector2(10, 0)));
    components.push_back(new CMoverComponent(1.5f, 10));
    components.push_back(new CScrollerComponent());
    components.push_back(new CMoveToTargetComponent(150));
    components.push_back(new CDieByBulletComponent(3));
    components.push_back(new CKillComponent());
    createEntity(components);

    components.clear();
    components.push_back(new CPositionComponent(Vector2(1400, 115)));
    components.push_back(new CSpriteComponent("squidEnemy.bmp"));
    components.push_back(new CColliderComponent(100, 65, Collider::eActor));
    components.push_back(new CScrollerComponent());
    components.push_back(new CShooterComponent(1, "bullet.bmp"));
    components.push_back(new CShootAtTargetComponent(200, 7, 30));
    components.push_back(new CDieByBulletComponent(10));
    components.push_back(new CKillComponent());
    m_bossId = createEntity(components);
}

void CSceneManager::checkBulletFired(){

    Vector2 position;
    int direction;
    int damage;
    std::string sprite;
    std::vector<CComponent*> components;

    std::vector<CComponent*> shooters = findAllComponentsWithId(CComponent::eShooter);
    for(uint i = 0; i < shooters.size(); i++)
    {
        CShooterComponent* shooter = (CShooterComponent*)shooters[i];
        if(shooter->getShootingData(position, direction, damage, sprite))
        {

            components.clear();
            components.push_back(new CMoveInDirectionComponent(direction, 4));
            components.push_back(new CPositionComponent(position));
            components.push_back(new CSpriteComponent(sprite));
            components.push_back(new CColliderComponent(1, 3, Collider::eBullet));
            components.push_back(new CKillComponent());
            components.push_back(new CScrollerComponent());
            components.push_back(new CDieOffscreenComponent());
            createEntity(components);
        }
    }
}


int CSceneManager::createEntity(std::vector<CComponent*> components){

    for(uint i = 0; i < components.size(); i++)
    {
        components[i]->setEntityId(m_entityCount);
        m_componentList.push_back(components[i]);

        for(uint j = 0; j < components.size(); j++)
        {
            if(i != j) components[i]->onComponentAdded(components[j]);
        }
    }

    m_entityCount++;
    return m_entityCount - 1;
}

void CSceneManager::removeEntity(int id){

    for(uint i = 0; i < m_componentList.size(); i++)
    {
        if(m_componentList[i]->getEntityId() == id) m_componentList.erase(m_componentList.begin() + i);
    }
}

std::vector<CComponent*> CSceneManager::findAllComponentsWithId(CComponent::componentId id){

    std::vector<CComponent*> components;

    for(uint i = 0; i < m_componentList.size(); i++)
    {
        if(m_componentList[i]->getId() == id) components.push_back(m_componentList[i]);
    }

    return components;
}

CComponent* CSceneManager::findEntityComponent(CComponent::componentId id, int entityId){

    for(uint i = 0; i < m_componentList.size(); i++)
    {
        if(m_componentList[i]->getId() == id && m_componentList[i]->getEntityId() == entityId) return m_componentList[i];
    }

    return NULL;
}


