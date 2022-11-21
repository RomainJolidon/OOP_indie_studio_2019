/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_TIMERSYSTEM_HPP
#define BOMBERMAN_TIMERSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class TimerSystem {
    public:
    TimerSystem() = default;
    ~TimerSystem() = default;
    void update(Storage<Timer> &timerStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Position> &positionStorage, Storage<Model> &modelStorage,
        Storage<Collider> &colliderStorage, unsigned long long int clock,
        std::vector<std::string> &map, Storage<Destroyer> &destroyerStorage
    );

    protected:
    private:
    bool process(unsigned long long int id, Storage<Timer> &timerStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Position> &positionStorage, Storage<Model> &modelStorage,
        Storage<Collider> &colliderStorage, unsigned long long int clock,
        std::vector<std::string> &map, Storage<Destroyer> &destroyerStorage
    );
};

#endif //BOMBERMAN_TIMERSYSTEM_HPP
