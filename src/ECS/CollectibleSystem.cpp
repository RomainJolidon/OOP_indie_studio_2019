/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#include "ECS/CollectibleSystem.hpp"

CollectibleSystem::CollectibleSystem()
{
}

CollectibleSystem::~CollectibleSystem()
{
}

void CollectibleSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage,
    Storage<Collectible> &collectibleStorage,
    Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Destroyer> &destroyerStorage
) const
{
    auto it = playableStorage.componentVector.begin();

    while (it != playableStorage.componentVector.end()) {
        if (process(positionStorage, velocityStorage, collectibleStorage,
            it->entityId, playableStorage, modelStorage, destroyableStorage,
            destroyerStorage)) {
            it = playableStorage.componentVector.begin();
        } else {
            it++;
        }
    }
}

bool CollectibleSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage,
    Storage<Collectible> &collectibleStorage, unsigned long long int entityID,
    Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Destroyer> &destroyerStorage
) const
{
    for (auto &it : collectibleStorage.entityIdxToComponentIdxMap) {
        if ((positionStorage.getComponentForEntity(entityID).y == positionStorage.getComponentForEntity(it.first).y) &&
            (positionStorage.getComponentForEntity(entityID).x == positionStorage.getComponentForEntity(it.first).x)) {
            playableStorage.getComponentForEntity(
                entityID).effect = collectibleStorage.getComponentForEntity(
                it.first).effect;
            modelStorage.removeComponentForEntity(it.first);
            positionStorage.removeComponentForEntity(it.first);
            collectibleStorage.removeComponentForEntity(it.first);
            return true;
        }
    }
    for (auto &it : destroyerStorage.entityIdxToComponentIdxMap) {
        if ((positionStorage.getComponentForEntity(entityID).y == positionStorage.getComponentForEntity(it.first).y) &&
            (positionStorage.getComponentForEntity(entityID).x == positionStorage.getComponentForEntity(it.first).x)) {
            playableStorage.getComponentForEntity(entityID).is_alive = false;
        }
    }
    return false;
}
