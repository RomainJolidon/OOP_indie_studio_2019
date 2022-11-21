/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_INPUTSYSTEM_HPP
#define OOP_ARCADE_2019_INPUTSYSTEM_HPP

#include <events/IEventManager.hpp>
#include "ECSEntity.hpp"
#include "Components.hpp"
#include "Storage.hpp"

class InputSystem {
        public:
        InputSystem();
        ~InputSystem();
        void update(Storage<Playable> &playableStorage,
            Storage<Velocity> &velocityStorage,
            Storage<Position> &positionStorage,
            std::shared_ptr<IEventManager> &eventManager,
            Storage<Orientation> &orientationStorage
        ) const;
        protected:
        private:
        void process(Storage<Playable> &playableStorage,
            Storage<Velocity> &velocityStorage, unsigned long long int entityID,
            std::shared_ptr<IEventManager> &eventManager,
            Storage<Orientation> &orientationStorage,
            Storage<Position> &positionStorage
        ) const;
};

#endif //OOP_ARCADE_2019_INPUTSYSTEM_HPP
