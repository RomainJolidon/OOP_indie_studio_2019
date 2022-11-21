/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#ifndef BOMBERMAN_MAPSYSTEM_HPP
#define BOMBERMAN_MAPSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class MapSystem {
    public:
    MapSystem();
    ~MapSystem();
    void update(std::vector<std::string> &map,
        Storage<Position> &positionStorage, Storage<Collider> &colliderStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage, Storage<Explosive> &explosiveStorage
    ) const;
    protected:
    private:
    void process(std::vector<std::string> &map,
        Storage<Position> &positionStorage, unsigned long long int entityID,
        Storage<Collider> &colliderStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage, Storage<Explosive> &explosiveStorage
    ) const;
};

#endif //BOMBERMAN_MAPSYSTEM_HPP
