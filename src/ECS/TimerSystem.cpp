/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include "ECS/TimerSystem.hpp"

void TimerSystem::update(Storage<Timer> &timerStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Position> &positionStorage, Storage<Model> &modelStorage,
    Storage<Collider> &colliderStorage, unsigned long long int clock,
    std::vector<std::string> &map, Storage<Destroyer> &destroyerStorage
)
{
    auto it = timerStorage.entityIdxToComponentIdxMap.begin();

    while (it != timerStorage.entityIdxToComponentIdxMap.end()) {
        if (process(it->first, timerStorage, destroyableStorage,
            positionStorage, modelStorage, colliderStorage, clock, map,
            destroyerStorage)) {
            it = timerStorage.entityIdxToComponentIdxMap.begin();
        } else {
            it++;
        }
    }
}

bool TimerSystem::process(unsigned long long int id,
    Storage<Timer> &timerStorage, Storage<Destroyable> &destroyableStorage,
    Storage<Position> &positionStorage, Storage<Model> &modelStorage,
    Storage<Collider> &colliderStorage, unsigned long long int clock,
    std::vector<std::string> &map, Storage<Destroyer> &destroyerStorage
)
{
    if (timerStorage.getComponentForEntity(id).treshold == 0) {
        timerStorage.getComponentForEntity(id).treshold = clock;
    } else if (timerStorage.getComponentForEntity(id).treshold + (timerStorage.getComponentForEntity(id).offset * 1000) < clock) {
        map[positionStorage.getComponentForEntity(id).y][positionStorage.getComponentForEntity(id).x] = ' ';
        colliderStorage.removeComponentForEntity(id);
        positionStorage.removeComponentForEntity(id);
        timerStorage.removeComponentForEntity(id);
        destroyableStorage.removeComponentForEntity(id);
        destroyerStorage.removeComponentForEntity(id);
        modelStorage.removeComponentForEntity(id);
        return (true);
    }
    return (false);
}