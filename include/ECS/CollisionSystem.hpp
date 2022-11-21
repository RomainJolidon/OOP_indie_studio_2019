/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_COLLISIONSYSTEM_HPP
#define OOP_ARCADE_2019_COLLISIONSYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class CollisionSystem {
    public:
        CollisionSystem();
        ~CollisionSystem();
        void update(Storage<Position> &positionStorage,
            Storage<Velocity> &velocityStorage,
            Storage<Collider> &colliderStorage,
            Storage<Collectible> &collectibleStorage,
            Storage<Playable> &playableStorage, Storage<Model> &modelStorage,
            Storage<Destroyable> &destroyableStorage,
            Storage<Destroyer> &destroyerStorage
        ) const;
    protected:
    private:
        void process(Storage<Position> &positionStorage,
            Storage<Velocity> &velocityStorage,
            Storage<Collider> &colliderStorage,
            Storage<Collectible> &collectibleStorage,
            unsigned long long int entityID, Storage<Playable> &playableStorage,
            Storage<Model> &modelStorage,
            Storage<Destroyable> &destroyableStorage,
            Storage<Destroyer> &destroyerStorage
        ) const;
};

#endif //OOP_ARCADE_2019_COLLISIONSYSTEM_HPP
