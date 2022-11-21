/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_IGUI_HPP
#define BOMBERMAN_IGUI_HPP

#include <irrlicht.h>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <functional>

typedef std::function<void (void)> GUIinitializer;
typedef std::function<void (void)> ButtonInitializer;

class IGUI {
    public:
    ~IGUI() = default;
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void createButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image,
        const std::string &content, const ButtonInitializer &, unsigned int id
    ) = 0;
    virtual void clearGui() = 0;
    virtual void clearElement(const int& id) = 0;
    virtual void createSeletionList(const irr::core::recti &rectInSpace,
        const std::list<std::string> &contentList, const ButtonInitializer &,
        unsigned int id
    ) = 0;
    virtual void createText(const irr::core::recti &rectInSpace,
        const std::string &content, bool bordered, unsigned long long int id
    ) = 0;
    virtual void createTextBox(const irr::core::recti &rectInSpace,
        const std::string &content, bool bordered, unsigned long long int id
    ) = 0;
    virtual void createImage() = 0;
    virtual void setInitializer(const GUIinitializer&) = 0;
    virtual irr::IEventReceiver& getEventManager() const = 0;
    virtual void display() const = 0;
    virtual irr::gui::IGUIElement * getGUIElement(unsigned int id) = 0;
    protected:
    private:
};

#endif //BOMBERMAN_IGUI_HPP
