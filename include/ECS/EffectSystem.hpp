/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#ifndef BOMBERMAN_EFFECTSYSTEM_HPP
#define BOMBERMAN_EFFECTSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class EffectSystem {
    public:
    EffectSystem() = default;
    ~EffectSystem() = default;
    void update(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
        Storage<Clock> &clockStorage, Instance &instance,
        Storage<Collider> &colliderStorage, Storage<Explosive> &explosiveStorage,
        Storage<Model> &modelStorage, std::vector<std::string> &map
    ) const;

    protected:
    private:
    void process(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, unsigned long long int entityID,
        Storage<Playable> &playableStorage, Storage<Clock> &clockStorage,
        Instance &instance, Storage<Collider> &colliderStorage,
        Storage<Explosive> &explosiveStorage, Storage<Model> &modelStorage, std::vector<std::string> &map
    ) const;
};

#endif //BOMBERMAN_EFFECTSYSTEM_HPP
