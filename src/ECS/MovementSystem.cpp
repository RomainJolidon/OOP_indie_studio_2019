/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include <iostream>
#include "ECS/MovementSystem.hpp"

MovementSystem::MovementSystem()
= default;

MovementSystem::~MovementSystem()
= default;

void MovementSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Model> &modelStorage,
    Storage<Orientation> &orientationStorage, Storage<Clock> &clockStorage,
    unsigned long long int clock
) const
{
    for (auto it : velocityStorage.entityIdxToComponentIdxMap) {
        if (positionStorage.hasEntityComponent(it.first) && modelStorage.hasEntityComponent(it.first)) {
            process(positionStorage, velocityStorage, it.first, modelStorage,
                orientationStorage, clockStorage, clock);
        }
    }
}

void MovementSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, unsigned long long int entityID,
    Storage<Model> &modelStorage, Storage<Orientation> &orientationStorage,
    Storage<Clock> &clockStorage, unsigned long long int clock
) const
{
    Position &entityPosition = positionStorage.getComponentForEntity(entityID);
    Velocity &entityVelocity = velocityStorage.getComponentForEntity(entityID);
    Orientation &entityOrientation = orientationStorage.getComponentForEntity(entityID);
    Model &entityModel = modelStorage.getComponentForEntity(entityID);
    Clock &entityClock = clockStorage.getComponentForEntity(entityID);

    if (entityClock.treshold == 0) {
        entityClock.treshold = clock;
    } else if (entityClock.treshold + (entityClock.offset) < clock) {
        entityModel.mesh->setRotation(-90, 0, entityOrientation.angle);
        if (entityPosition.spaceX != entityVelocity.destX ||
            entityPosition.spaceY != entityVelocity.destY) {
            entityModel.mesh->setAnimation(RUN);
            moveToDestination(entityVelocity, entityPosition, entityModel);
            entityPosition.x = (entityVelocity.destX / 100);
            entityPosition.y = (entityVelocity.destY / 100);
            entityClock.treshold = clock;
        } else {
            entityModel.mesh->setAnimation(IDLE);
        }
    }
}

void MovementSystem::moveToDestination(Velocity &entityVelocity,
    Position &entityPosition, Model &entityModel
) const
{
    if (entityPosition.spaceX != entityVelocity.destX) {
        if ((entityVelocity.speedX < 0 &&  entityPosition.spaceX - entityVelocity.destX < -entityVelocity.speedX) ||
            (entityVelocity.speedX > 0 &&  entityVelocity.destX - entityPosition.spaceX < entityVelocity.speedX)) {
            entityModel.mesh->setPosition(entityVelocity.destX, entityPosition.spaceY, 0);
        } else {
            entityModel.mesh->move(entityVelocity.speedX, 0, 0);
        }
        entityPosition.spaceX = entityModel.mesh->getPosition().X;
    }
    if (entityPosition.spaceY != entityVelocity.destY) {
        if ((entityVelocity.speedY < 0 && entityPosition.spaceY - entityVelocity.destY < -entityVelocity.speedY) ||
            (entityVelocity.speedY > 0 && entityVelocity.destY - entityPosition.spaceY < entityVelocity.speedY)) {
            entityModel.mesh->setPosition(entityPosition.spaceX, entityVelocity.destY, 0);
        } else {
            entityModel.mesh->move(0, entityVelocity.speedY, 0);
        }
        entityPosition.spaceY = entityModel.mesh->getPosition().Y;
    }
}



