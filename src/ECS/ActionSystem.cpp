/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#include <visual/VisualManager.hpp>
#include <scenes/IScene.hpp>
#include <scenes/SceneGame.hpp>
#include "ECS/ActionSystem.hpp"
#include "ECS/Instance.hpp"

ActionSystem::ActionSystem()
{
}

ActionSystem::~ActionSystem()
{
}

void ActionSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
    Storage<Orientation> &orientationStorage, Instance &instance,
    Storage<Collider> &colliderStorage, Storage<Explosive> &explosiveStorage,
    Storage<Model> &modelStorage, IScene &scene, std::vector<std::string> &map
) const
{
    for (auto &it : playableStorage.componentVector) {
        process(positionStorage, velocityStorage, it.entityId, playableStorage,
            orientationStorage, instance, colliderStorage, explosiveStorage,
            modelStorage, scene, map);
    }
}

void ActionSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, unsigned long long int entityID,
    Storage<Playable> &playableStorage, Storage<Orientation> &orientationStorage,
    Instance &instance, Storage<Collider> &colliderStorage,
    Storage<Explosive> &explosiveStorage, Storage<Model> &modelStorage,
    IScene &scene, std::vector<std::string> &map
) const
{
    Playable &entityPlayable = playableStorage.getComponentForEntity(entityID);
    Velocity &entityVelocity = velocityStorage.getComponentForEntity(entityID);

    if (entityPlayable.action == PUT_BOMB &&
        canPlaceBomb(entityPlayable.entityId, entityPlayable.stats.nbBombs,
            explosiveStorage, positionStorage)) {
        dynamic_cast<SceneGame &>(scene).createBomb(entityVelocity.destX, entityVelocity.destY, entityVelocity.entityId, entityPlayable.stats.range);
    }
    entityPlayable.action = NO_ACTION;
}

bool ActionSystem::canPlaceBomb(unsigned long long int parentId, int maxBomb,
    Storage<Explosive> &explosiveStorage, Storage<Position> &positionStorage
) const
{
    int count = 0;

    for (auto &it: explosiveStorage.componentVector) {
        if (it.parentId == parentId) {
            count++;
        }
        if (positionStorage.getComponentForEntity(it.entityId).x == positionStorage.getComponentForEntity(parentId).x &&
            positionStorage.getComponentForEntity(it.entityId).y == positionStorage.getComponentForEntity(parentId).y) {
            return (false);
        }
    }
    for (auto &it: positionStorage.componentVector) {
        if (it.entityId == parentId)
            continue;
        if (positionStorage.getComponentForEntity(it.entityId).x == positionStorage.getComponentForEntity(parentId).x &&
            positionStorage.getComponentForEntity(it.entityId).y == positionStorage.getComponentForEntity(parentId).y) {
            return (false);
        }
    }
    return count < maxBomb;
}
