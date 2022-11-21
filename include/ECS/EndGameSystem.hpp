/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#ifndef BOMBERMAN_ENDGAMESYSTEM_HPP
#define BOMBERMAN_ENDGAMESYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class EndGameSystem {
    public:
    EndGameSystem() = default;
    ~EndGameSystem() = default;
    bool update(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
        Storage<Clock> &clockStorage, Storage<Collider> &colliderStorage,
        Storage<Orientation> &orientationStorage, Storage<Model> &modelStorage,
        std::vector<std::string> &map
    ) const;

    protected:
    private:
    bool process(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, unsigned long long int entityID,
        Storage<Playable> &playableStorage, Storage<Clock> &clockStorage,
        Storage<Collider> &colliderStorage,
        Storage<Orientation> &orientationStorage, Storage<Model> &modelStorage,
        std::vector<std::string> &map
    ) const;
};

#endif //BOMBERMAN_ENDGAMESYSTEM_HPP
