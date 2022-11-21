/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_GUI_HPP
#define BOMBERMAN_GUI_HPP

#include "IGUI.hpp"
#include "events/EventManager.hpp"
#include "config/IdGen.hpp"
#include <memory>
#include <vector>

class GUI: public IGUI {
    public:
    GUI(GUIinitializer initFunction, irr::scene::ISceneManager &sceneManager,
        IEventManager &eventManager
    );
    GUI(const GUI&) = default;
    GUI &operator=(const GUI&) = default;
    void load() override ;
    void unload() override ;
    void createButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image,
        const std::string &content, const ButtonInitializer &buttonFun,
        unsigned int id
    ) override ;
    void clearGui() override;
    void clearElement(const int& id) override;
    void createImage() override ;
    void createSeletionList(const irr::core::recti &rectInSpace,
        const std::list<std::string> &contentList,
        const ButtonInitializer &listFun, unsigned int id
    ) override ;
    void createText(const irr::core::recti &rectInSpace,
        const std::string &content, bool bordered, unsigned long long int id
    ) override ;
    void createTextBox(const irr::core::recti &rectInSpace,
        const std::string &content, bool bordered, unsigned long long int id
    ) override ;
    void setInitializer(const GUIinitializer&) override ;
    void display() const override ;
    irr::IEventReceiver& getEventManager() const;
    irr::gui::IGUIElement * getGUIElement(unsigned int id) override ;
    ~GUI();

    protected:
    private:
    IEventManager &_eventManager;
    irr::gui::IGUIEnvironment *_GUIEnv;
    GUIinitializer _initializer;
    irr::gui::IGUIFont *_font;
    std::unordered_map<unsigned int, irr::gui::IGUIElement *> _guiElemList;
    bool _initialized;
};

#endif //BOMBERMAN_GUI_HPP
