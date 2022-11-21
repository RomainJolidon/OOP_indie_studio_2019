/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_EXPLOSIVESYSTEM_HPP
#define BOMBERMAN_EXPLOSIVESYSTEM_HPP

#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"
#include "Instance.hpp"
#include "visual/VisualManager.hpp"

class ExplosiveSystem {
    public:
    ExplosiveSystem();
    ~ExplosiveSystem();
    void update(Storage<Explosive> &explosiveStorage,
        Storage<Collider> &colliderStorage, Storage<Model> &modelStorage,
        Storage<Position> &positionStorage, unsigned long long int clock,
        IScene &scene, std::vector<std::string> &map,
        Storage<Destroyable> &destroyableStorage, Storage<Timer> &timerStorage,
        Instance &instance
    );

    protected:
    private:
    bool process(unsigned long long int id,
        Storage<Explosive> &explosiveStorage,
        Storage<Collider> &colliderStorage, Storage<Model> &modelStorage,
        Storage<Position> &positionStorage, unsigned long long int clock,
        IScene &scene, std::vector<std::string> &map, Instance &instance,
        Storage<Destroyable> &destroyableStorage, Storage<Timer> &timerStorage
    );
    void placeFireLine(unsigned long long int id, int range, int incrX,
        int incrY, Storage<Collider> &colliderStorage,
        Storage<Model> &modelStorage, Storage<Position> &positionStorage,
        Storage<Explosive> &explosiveStorage, IScene &scene,
        std::vector<std::string> &map, Storage<Destroyable> &destroyableStorage,
        Storage<Timer> &timerStorage, Instance &instance
    );
    unsigned long long int findDestroyable(int x, int y,
        std::vector<std::string> &map, Storage<Position> &positionStorage
    ) const;
};

#endif //BOMBERMAN_EXPLOSIVESYSTEM_HPP
