/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP
#define OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class MovementSystem {
    public:
        MovementSystem();
        ~MovementSystem();
        void update(Storage<Position> &positionStorage,
            Storage<Velocity> &velocityStorage, Storage<Model> &modelStorage,
            Storage<Orientation> &orientationStorage,
            Storage<Clock> &clockStorage, unsigned long long int clock
        ) const;
    protected:
    private:
        void process(Storage<Position> &positionStorage,
            Storage<Velocity> &velocityStorage, unsigned long long int entityID,
            Storage<Model> &modelStorage,
            Storage<Orientation> &orientationStorage,
            Storage<Clock> &clockStorage, unsigned long long int clock
        ) const;
        void moveToDestination(Velocity &entityVelocity,
            Position &entityPosition, Model &entityModel
        ) const;
};

#endif //OOP_ARCADE_2019_MOVEMENTSYSTEM_HPP
