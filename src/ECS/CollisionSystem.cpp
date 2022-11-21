/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "ECS/CollisionSystem.hpp"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Collider> &colliderStorage,
    Storage<Collectible> &collectibleStorage,
    Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Destroyer> &destroyerStorage
) const
{
    for (auto &it : colliderStorage.entityIdxToComponentIdxMap) {
        process(positionStorage, velocityStorage, colliderStorage,
            collectibleStorage, it.first, playableStorage, modelStorage,
            destroyableStorage, destroyerStorage);
    }
}

void CollisionSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Collider> &colliderStorage,
    Storage<Collectible> &collectibleStorage, unsigned long long int entityID,
    Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Destroyer> &destroyerStorage
) const
{
    Position &entityPosition = positionStorage.getComponentForEntity(
        entityID);

    Position *otherEntityPosition;
    Velocity *otherEntityVelocity;
    Collider *otherEntityCollider;

    if (!velocityStorage.hasEntityComponent(entityID) ||
        (velocityStorage.getComponentForEntity(entityID).destX == entityPosition.spaceX &&
            velocityStorage.getComponentForEntity(entityID).destY == entityPosition.spaceY)) {
        return;
    } else if ((velocityStorage.getComponentForEntity(entityID).speedX < 0 && entityPosition.spaceX - velocityStorage.getComponentForEntity(entityID).destX < 100 &&
        entityPosition.spaceX - velocityStorage.getComponentForEntity(entityID).destX != 0) ||
        (velocityStorage.getComponentForEntity(entityID).speedX > 0 && velocityStorage.getComponentForEntity(entityID).destX - entityPosition.spaceX < 100 &&
            velocityStorage.getComponentForEntity(entityID).destX - entityPosition.spaceX != 0) ||
        (velocityStorage.getComponentForEntity(entityID).speedY < 0 && entityPosition.spaceY - velocityStorage.getComponentForEntity(entityID).destY < 100 &&
            entityPosition.spaceY - velocityStorage.getComponentForEntity(entityID).destY != 0) ||
        (velocityStorage.getComponentForEntity(entityID).speedY > 0 && velocityStorage.getComponentForEntity(entityID).destY - entityPosition.spaceY < 100 &&
        velocityStorage.getComponentForEntity(entityID).destY - entityPosition.spaceY != 0)) {
        return;
    }
    Velocity &entityVelocity = velocityStorage.getComponentForEntity(entityID);
    for (auto it : colliderStorage.entityIdxToComponentIdxMap) {
        if (it.first == entityID)
            continue;
        otherEntityPosition = &positionStorage.getComponentForEntity(it.first);
        otherEntityCollider = &colliderStorage.getComponentForEntity(it.first);
        if (velocityStorage.hasEntityComponent(it.first)) {
            otherEntityVelocity = &velocityStorage.getComponentForEntity(it.first);
            if (entityVelocity.destX  < otherEntityVelocity->destX + (otherEntityCollider->width * 100) &&
                entityVelocity.destX >= otherEntityVelocity->destX &&
                entityVelocity.destY < otherEntityVelocity->destY + (otherEntityCollider->height * 100) &&
                entityVelocity.destY >= otherEntityVelocity->destY) {
                entityVelocity.destX = entityPosition.spaceX;
                entityVelocity.destY = entityPosition.spaceY;
                return;
            }
        }
        if (entityVelocity.destX  < otherEntityPosition->spaceX + (otherEntityCollider->width * 100) &&
            entityVelocity.destX >= otherEntityPosition->spaceX &&
            entityVelocity.destY < otherEntityPosition->spaceY + (otherEntityCollider->height * 100) &&
            entityVelocity.destY >= otherEntityPosition->spaceY) {
            if (playableStorage.getComponentForEntity(entityID).stats.wallPass && destroyableStorage.hasEntityComponent(it.first))
                return;
            entityVelocity.destX = entityPosition.spaceX;
            entityVelocity.destY = entityPosition.spaceY;
            return;
        }
    }
}

