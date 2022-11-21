/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#include <iostream>
#include "ECS/MapSystem.hpp"

MapSystem::MapSystem()
{
}

MapSystem::~MapSystem()
{
}

void MapSystem::update(std::vector<std::string> &map,
    Storage<Position> &positionStorage, Storage<Collider> &colliderStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage, Storage<Explosive> &explosiveStorage
) const
{
    for (auto & it : map) {
        for (char &c: it) {
            if (c != '*' && c != 'x')
                c = ' ';
       }
   }
    for (auto it : positionStorage.entityIdxToComponentIdxMap)
        process(map, positionStorage, it.first, colliderStorage,
            destroyableStorage, playableStorage, explosiveStorage);
    /*for (auto & it : map) {
        std::cout << it << std::endl;
    }*/
}

void MapSystem::process(std::vector<std::string> &map,
    Storage<Position> &positionStorage, unsigned long long int entityID,
    Storage<Collider> &colliderStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage, Storage<Explosive> &explosiveStorage
) const
{
    if (colliderStorage.hasEntityComponent(entityID) && destroyableStorage.hasEntityComponent(entityID)) {
        map[positionStorage.getComponentForEntity(
            entityID).y][positionStorage.getComponentForEntity(
            entityID).x] = 'x';
    } else if (colliderStorage.hasEntityComponent(entityID) && playableStorage.hasEntityComponent(entityID)) {
        map[positionStorage.getComponentForEntity(
            entityID).y][positionStorage.getComponentForEntity(
            entityID).x] = 'p';
    } else if (colliderStorage.hasEntityComponent(entityID) && explosiveStorage.hasEntityComponent(entityID)) {
        map[positionStorage.getComponentForEntity(
            entityID).y][positionStorage.getComponentForEntity(
            entityID).x] = 'b';
    }
}