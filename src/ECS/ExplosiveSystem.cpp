/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include "scenes/SceneGame.hpp"
#include "ECS/ExplosiveSystem.hpp"

ExplosiveSystem::ExplosiveSystem()
{
}

ExplosiveSystem::~ExplosiveSystem()
{
}

void ExplosiveSystem::update(Storage<Explosive> &explosiveStorage,
    Storage<Collider> &colliderStorage, Storage<Model> &modelStorage,
    Storage<Position> &positionStorage, unsigned long long int clock,
    IScene &scene, std::vector<std::string> &map,
    Storage<Destroyable> &destroyableStorage, Storage<Timer> &timerStorage,
    Instance &instance
)
{
    auto it = explosiveStorage.entityIdxToComponentIdxMap.begin();

    while (it != explosiveStorage.entityIdxToComponentIdxMap.end()) {
        if (process(it->first, explosiveStorage, colliderStorage, modelStorage,
            positionStorage, clock, scene, map, instance, destroyableStorage, timerStorage)) {
            it = explosiveStorage.entityIdxToComponentIdxMap.begin();
        } else {
            it++;
        }
    }
}

bool ExplosiveSystem::process(unsigned long long int id,
    Storage<Explosive> &explosiveStorage, Storage<Collider> &colliderStorage,
    Storage<Model> &modelStorage, Storage<Position> &positionStorage,
    unsigned long long int clock, IScene &scene, std::vector<std::string> &map,
    Instance &instance, Storage<Destroyable> &destroyableStorage,
    Storage<Timer> &timerStorage
)
{
    if (explosiveStorage.getComponentForEntity(id).timer.treshold == 0) {
        explosiveStorage.getComponentForEntity(id).timer.treshold = clock;
    } else if (explosiveStorage.getComponentForEntity(id).timer.treshold + (explosiveStorage.getComponentForEntity(id).timer.offset * 1000) < clock) {
        map[positionStorage.getComponentForEntity(id).y][positionStorage.getComponentForEntity(id).x] = ' ';
        dynamic_cast<SceneGame &>(scene)._config.playSoundEffect(EXPLOSION);
        dynamic_cast<SceneGame &>(scene).CreateFire(positionStorage.getComponentForEntity(id).x, positionStorage.getComponentForEntity(id).y);
        placeFireLine(id, explosiveStorage.getComponentForEntity(id).range, -1,
            0, colliderStorage, modelStorage, positionStorage, explosiveStorage,
            scene, map, destroyableStorage, timerStorage, instance);
        placeFireLine(id, explosiveStorage.getComponentForEntity(id).range, 1,
            0, colliderStorage, modelStorage, positionStorage, explosiveStorage,
            scene, map, destroyableStorage, timerStorage, instance);
        placeFireLine(id, explosiveStorage.getComponentForEntity(id).range, 0,
            -1, colliderStorage, modelStorage, positionStorage, explosiveStorage,
            scene, map, destroyableStorage, timerStorage, instance);
        placeFireLine(id, explosiveStorage.getComponentForEntity(id).range, 0,
            1, colliderStorage, modelStorage, positionStorage, explosiveStorage,
            scene, map, destroyableStorage, timerStorage, instance);
        modelStorage.removeComponentForEntity(id);
        explosiveStorage.removeComponentForEntity(id);
        positionStorage.removeComponentForEntity(id);
        colliderStorage.removeComponentForEntity(id);
        return (true);
    }
    return (false);
}

void ExplosiveSystem::placeFireLine(unsigned long long int id, int range,
    int incrX, int incrY, Storage<Collider> &colliderStorage,
    Storage<Model> &modelStorage, Storage<Position> &positionStorage,
    Storage<Explosive> &explosiveStorage, IScene &scene,
    std::vector<std::string> &map, Storage<Destroyable> &destroyableStorage,
    Storage<Timer> &timerStorage, Instance &instance
)
{
    int x = positionStorage.getComponentForEntity(id).x;
    int y = positionStorage.getComponentForEntity(id).y;
    unsigned long long int destroyableId;
    int randNb = 0;

    for (; range > 0; range--) {
        x += incrX;
        y += incrY;
        if (x < 0 || y < 0 || map[y][x] == '*' || map[y][x] == 'f') {
            break;
        } else if (map[y][x] == 'x') {
            destroyableId = findDestroyable(x, y, map, positionStorage);
            destroyableStorage.removeComponentForEntity(destroyableId);
            positionStorage.removeComponentForEntity(destroyableId);
            colliderStorage.removeComponentForEntity(destroyableId);
            modelStorage.removeComponentForEntity(destroyableId);
            map[y][x] = ' ';
            randNb = std::rand()%40;
                switch (randNb) {
                case 0:
                case 1:
                case 2:
                case 3:
                    dynamic_cast<SceneGame &>(scene).CreateBonus(x, y, SPEED_UP);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    dynamic_cast<SceneGame &>(scene).CreateBonus(x, y, FIRE_UP);
                    break;
                case 8:
                    dynamic_cast<SceneGame &>(scene).CreateBonus(x, y, WALL_PASS);
                    break;
                case 9:
                case 10:
                case 11:
                    dynamic_cast<SceneGame &>(scene).CreateBonus(x, y, BOMB_UP);
                    break;
                default:
                    break;
                }
        }
        if (map[y][x] == 'b') {
            destroyableId = findDestroyable(x, y, map, positionStorage);
            explosiveStorage.getComponentForEntity(destroyableId).timer.offset = 0;
        } else {
            dynamic_cast<SceneGame &>(scene).CreateFire(x, y);
        }
    }
}

unsigned long long int ExplosiveSystem::findDestroyable(int x, int y,
    std::vector<std::string> &map, Storage<Position> &positionStorage
) const
{
    for (auto &it: positionStorage.componentVector) {
        if (it.x == x && it.y == y) {
            return (it.entityId);
        }
    }
    return (0);
}

