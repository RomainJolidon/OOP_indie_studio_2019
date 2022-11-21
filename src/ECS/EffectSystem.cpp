/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#include "ECS/EffectSystem.hpp"

void EffectSystem::update(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
    Storage<Clock> &clockStorage, Instance &instance,
    Storage<Collider> &colliderStorage, Storage<Explosive> &explosiveStorage,
    Storage<Model> &modelStorage, std::vector<std::string> &map
) const
{
    for (auto &it : playableStorage.entityIdxToComponentIdxMap) {
        process(positionStorage, velocityStorage, it.first, playableStorage,
            clockStorage, instance, colliderStorage, explosiveStorage,
            modelStorage, map);
    }
}

void EffectSystem::process(Storage<Position> &positionStorage,
    Storage<Velocity> &velocityStorage, unsigned long long int entityID,
    Storage<Playable> &playableStorage, Storage<Clock> &clockStorage,
    Instance &instance, Storage<Collider> &colliderStorage,
    Storage<Explosive> &explosiveStorage, Storage<Model> &modelStorage, std::vector<std::string> &map
) const
{
    if (playableStorage.getComponentForEntity(entityID).effect == SPEED_UP) {
        velocityStorage.getComponentForEntity(entityID).speedX = velocityStorage.getComponentForEntity(entityID).speedX < 0 ?
            velocityStorage.getComponentForEntity(entityID).speedX - 5 : velocityStorage.getComponentForEntity(entityID).speedX + 5;
        velocityStorage.getComponentForEntity(entityID).speedY = velocityStorage.getComponentForEntity(entityID).speedY < 0 ?
            velocityStorage.getComponentForEntity(entityID).speedY - 5 : velocityStorage.getComponentForEntity(entityID).speedY + 5;
        playableStorage.getComponentForEntity(entityID).effect = NO_EFFECT;
    } else if (playableStorage.getComponentForEntity(entityID).effect == BOMB_UP) {
        playableStorage.getComponentForEntity(entityID).stats.nbBombs++;
        playableStorage.getComponentForEntity(entityID).effect = NO_EFFECT;
    } else if (playableStorage.getComponentForEntity(entityID).effect == FIRE_UP) {
        playableStorage.getComponentForEntity(entityID).stats.range++;
        playableStorage.getComponentForEntity(entityID).effect = NO_EFFECT;
    } else if (playableStorage.getComponentForEntity(entityID).effect == WALL_PASS) {
        playableStorage.getComponentForEntity(entityID).stats.wallPass = true;
        playableStorage.getComponentForEntity(entityID).effect = NO_EFFECT;
    }
}
