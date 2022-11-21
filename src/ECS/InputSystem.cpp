/*
** EPITECH PROJECT, 2023
** OOParcade2019
** File description:
** Created by jfournier,
*/

#include "ECS/InputSystem.hpp"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update(Storage<Playable> &playableStorage,
    Storage<Velocity> &velocityStorage, Storage<Position> &positionStorage,
    std::shared_ptr<IEventManager> &eventManager,
    Storage<Orientation> &orientationStorage
) const
{
    for (auto &it : playableStorage.componentVector) {
        if (!it.isAI && velocityStorage.hasEntityComponent(it.entityId)) {
            process(playableStorage, velocityStorage, it.entityId, eventManager,
                orientationStorage, positionStorage);
        }
    }
}

void InputSystem::process(Storage<Playable> &playableStorage,
    Storage<Velocity> &velocityStorage, unsigned long long int entityID,
    std::shared_ptr<IEventManager> &eventManager,
    Storage<Orientation> &orientationStorage, Storage<Position> &positionStorage
) const
{
    Velocity &entityVelocity = velocityStorage.getComponentForEntity(entityID);
    Orientation &entityOrientation = orientationStorage.getComponentForEntity(entityID);
    Playable &entityPlayable = playableStorage.getComponentForEntity(entityID);
    Position &entityPosition = positionStorage.getComponentForEntity(entityID);

    if (entityPosition.spaceX == entityVelocity.destX && entityPosition.spaceY == entityVelocity.destY) {
        if (eventManager->isKeyPressed(entityPlayable.left)) {
            entityVelocity.destX -= 100;
            entityVelocity.speedX =  entityVelocity.speedX > 0 ? -entityVelocity.speedX : entityVelocity.speedX;
            entityOrientation.angle = 270;
        } else if (eventManager->isKeyPressed(entityPlayable.right)) {
            entityVelocity.destX += 100;
            entityVelocity.speedX =  entityVelocity.speedX < 0 ? -entityVelocity.speedX : entityVelocity.speedX;
            entityOrientation.angle = 90;
        } else if (eventManager->isKeyPressed(entityPlayable.up)) {
            entityVelocity.destY += 100;
            entityVelocity.speedY =  entityVelocity.speedY < 0 ? -entityVelocity.speedY : entityVelocity.speedY;
            entityOrientation.angle = 180;
        } else if (eventManager->isKeyPressed(entityPlayable.down)) {
            entityVelocity.destY -= 100;
            entityVelocity.speedY =  entityVelocity.speedY > 0 ? -entityVelocity.speedY : entityVelocity.speedY;
            entityOrientation.angle = 360;
        }
    }
    if (eventManager->isKeyPressed(entityPlayable.bomb)) {
        entityPlayable.action = PUT_BOMB;
    }
}


