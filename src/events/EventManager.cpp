/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "events/EventManager.hpp"

EventManager::EventManager()
{
    for (bool & i : _keyIsDown)
        i = false;
}

EventManager::~EventManager()
{
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
    irr::s32 id = -1;

    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.GUIEvent.EventType != irr::gui::EGET_BUTTON_CLICKED)
            return true;
    } else if (event.EventType == irr::EET_GUI_EVENT) {
        id = event.GUIEvent.Caller->getID();
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED || event.GUIEvent.EventType == irr::gui::EGET_LISTBOX_CHANGED) {
            if (_guiElements.find(id) != _guiElements.end() &&
                _guiElements[id] != nullptr) {
                _guiElements[id]();
            }
            return (true);
        } else if (event.GUIEvent.EventType == irr::gui::EGET_EDITBOX_ENTER) {
            return (true);
        }
    }
    return (false);
}

irr::s32 EventManager::addGUIElem(const std::function<void(void)>& GUIFun)
{
    irr::s32 id = _guiElements.size() + 1;

    _guiElements[id] = GUIFun;
    return id;
}

void EventManager::clearGUIElem()
{
    _guiElements.clear();
}

bool EventManager::isKeyPressed(const irr::EKEY_CODE &input)
{
    return _keyIsDown[input];
}

