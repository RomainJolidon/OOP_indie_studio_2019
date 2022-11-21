/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#ifndef BOMBERMAN_COLLECTIBLESYSTEM_HPP
#define BOMBERMAN_COLLECTIBLESYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class CollectibleSystem {
    public:
    CollectibleSystem();
    ~CollectibleSystem();
    void update(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage,
        Storage<Collectible> &collectibleStorage,
        Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Destroyer> &destroyerStorage
    ) const;
    protected:
    private:
    bool process(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage,
        Storage<Collectible> &collectibleStorage,
        unsigned long long int entityID, Storage<Playable> &playableStorage,
        Storage<Model> &modelStorage, Storage<Destroyable> &destroyableStorage,
        Storage<Destroyer> &destroyerStorage
    ) const;
};

#endif //BOMBERMAN_COLLECTIBLESYSTEM_HPP
