/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by jfournier,
*/
#ifndef BOMBERMAN_ACTIONSYSTEM_HPP
#define BOMBERMAN_ACTIONSYSTEM_HPP


#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class ActionSystem {
    public:
    ActionSystem();
    ~ActionSystem();
    void update(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage,
        Storage<Orientation> &orientationStorage, Instance &instance,
        Storage<Collider> &colliderStorage,
        Storage<Explosive> &explosiveStorage, Storage<Model> &modelStorage,
        IScene &scene, std::vector<std::string> &map
    ) const;
    protected:
    private:
    void process(Storage<Position> &positionStorage,
        Storage<Velocity> &velocityStorage, unsigned long long int entityID,
        Storage<Playable> &playableStorage,
        Storage<Orientation> &orientationStorage, Instance &instance,
        Storage<Collider> &colliderStorage,
        Storage<Explosive> &explosiveStorage, Storage<Model> &modelStorage,
        IScene &scene, std::vector<std::string> &map
    ) const;
    bool canPlaceBomb(unsigned long long int parentId, int maxBomb,
        Storage<Explosive> &explosiveStorage, Storage<Position> &positionStorage
    ) const;
};

#endif //BOMBERMAN_ACTIONSYSTEM_HPP
