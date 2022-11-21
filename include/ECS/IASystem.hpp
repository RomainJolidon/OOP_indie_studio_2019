/*
** EPITECH PROJECT, 2023
** IASystem
** File description:
** IASystem by rjolidon,
*/

#ifndef IASYSTEM_HPP
#define IASYSTEM_HPP

#include "Components.hpp"
#include "Storage.hpp"
#include "Instance.hpp"
#include "InputSystem.hpp"
#include "MovementSystem.hpp"
#include "CollisionSystem.hpp"
#include "MapSystem.hpp"

enum Dir{LEFT, RIGHT, UP, DOWN, NO_PREF};

class IASystem
{
    public:
    IASystem();
    ~IASystem();
    void update(Storage<Velocity> &velocityStorage,
        Storage<Collider> &colliderStorage, Storage<Position> &positionStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage,
        Storage<Orientation> &orientationStorage,
        Storage<Explosive> &explosiveStorage, std::vector<std::string> &map,
        Storage<Destroyer> &destroyerStorage
    );
    void process(unsigned long long entityID,
        Storage<Velocity> &velocityStorage, Storage<Collider> &colliderStorage,
        Storage<Position> &positionStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage,
        Storage<Orientation> &orientationStorage,
        Storage<Explosive> &explosiveStorage, std::vector<std::string> &map,
        Storage<Destroyer> &destroyerStorage
    );
    int getDistance(
        float IaPosX, float IaPosY, float targetPosX, float targetPosY);
    void GetClosestTarget(unsigned long long entityID,
        Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage
    );
    bool GetClosestDanger(unsigned long long entityID,
        Storage<Position> &positionStorage,
        Storage<Explosive> &explosiveStorage,
        Storage<Playable> &playableStorage, Storage<Destroyer> &destroyerStorage
    );
    void MoveToTarget(unsigned long long int entityID,
        Storage<Position> &positionStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage, Storage<Velocity> &velocityStorage,
        Storage<Orientation> &orientationStorage, std::vector<std::string> &map
    );
    void MoveToTargetX(IA &targetVelocity, Velocity &iaVelocity,
        Orientation &entityOrientation, std::vector<std::string> &map
    );
    void MoveToTargetY(IA &targetVelocity, Velocity &iaVelocity,
        Orientation &entityOrientation, std::vector<std::string> &map
    );

    void MoveAwayFromBomb(unsigned long long int entityID,
        Storage<Position> &positionStorage,
        Storage<Destroyable> &destroyableStorage,
        Storage<Playable> &playableStorage, Storage<Velocity> &velocityStorage,
        Storage<Orientation> &orientationStorage, std::vector<std::string> &map
    );
    void MoveAwayFromBombX(IA &targetVelocity, Velocity &iaVelocity,
        Orientation &entityOrientation
    );
    void MoveAwayFromBombY(IA &targetVelocity, Velocity &iaVelocity,
        Orientation &entityOrientation
    );
    int isBreakable(int vectorX, int vectorY, std::vector<std::string> &map,
        unsigned long long int entityId, Storage<Position> &positionStorage,
        bool wallPass
    ) const;

    protected:
    private:
        //ECSEntity target;
};

#endif //IASYSTEM_HPP