/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#include <iostream>
#include "ECS/EndGameSystem.hpp"

bool EndGameSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
    Storage<Clock> &clockStorage, Storage<Collider> &colliderStorage,
    Storage<Orientation> &orientationStorage, Storage<Model> &modelStorage,
    std::vector<std::string> &map
) const
{
    auto it = playableStorage.componentVector.begin();

    while (it != playableStorage.componentVector.end()) {
        if (process(positionStorage, velocityStorage, it->entityId,
            playableStorage, clockStorage, colliderStorage, orientationStorage,
            modelStorage, map)) {
            it = playableStorage.componentVector.begin();
        } else {
            it++;
        }
    }
    if (playableStorage.componentVector.size() <= 1)
        return true;
    return false;
}

bool EndGameSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, unsigned long long int entityID,
    Storage<Playable> &playableStorage, Storage<Clock> &clockStorage,
    Storage<Collider> &colliderStorage,
    Storage<Orientation> &orientationStorage, Storage<Model> &modelStorage,
    std::vector<std::string> &map
) const
{
    if (!playableStorage.getComponentForEntity(entityID).is_alive) {
        positionStorage.removeComponentForEntity(entityID);
        velocityStorage.removeComponentForEntity(entityID);
        playableStorage.removeComponentForEntity(entityID);
        clockStorage.removeComponentForEntity(entityID);
        colliderStorage.removeComponentForEntity(entityID);
        orientationStorage.removeComponentForEntity(entityID);
        modelStorage.removeComponentForEntity(entityID);
        return true;
    }
    return false;
}
