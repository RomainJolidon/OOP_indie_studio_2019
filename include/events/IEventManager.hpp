/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_IEVENTMANAGER_HPP
#define BOMBERMAN_IEVENTMANAGER_HPP

#include <irrlicht.h>
#include <iostream>
#include <unordered_map>
#include <functional>

    class IEventManager: public irr::IEventReceiver {
        public:
        ~IEventManager() = default;
        virtual bool OnEvent(const irr::SEvent &event) = 0;
        virtual bool isKeyPressed(const irr::EKEY_CODE &input) = 0;
        virtual irr::s32 addGUIElem(const std::function<void (void)>& GUIFun) = 0;
        virtual void clearGUIElem() = 0;

        protected:
        private:
    };

#endif //BOMBERMAN_IEVENTMANAGER_HPP
