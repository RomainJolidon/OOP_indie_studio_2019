/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

#include "IEventManager.hpp"

class EventManager: public IEventManager {
    public:
    EventManager();
    bool OnEvent(const irr::SEvent &event) override;
    bool isKeyPressed(const irr::EKEY_CODE &input) override;
    irr::s32 addGUIElem(const std::function<void (void)>& GUIFun) override ;
    void clearGUIElem() override ;
    ~EventManager() override ;

    protected:
    private:
        bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];
        std::unordered_map<irr::s32, std::function<void(void)>> _guiElements;
};

#endif //BOMBERMAN_EVENTMANAGER_HPP
