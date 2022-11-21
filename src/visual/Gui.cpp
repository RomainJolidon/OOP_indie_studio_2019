/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "visual/Gui.hpp"
#include <utility>

GUI::GUI(GUIinitializer initFunction, irr::scene::ISceneManager &sceneManager,
    IEventManager &eventManager
) :
_eventManager(eventManager), _GUIEnv(nullptr), _initializer(nullptr), _font(nullptr), _initialized(false)
{
    _GUIEnv = sceneManager.getGUIEnvironment();
    if (!_GUIEnv)
        std::cerr << "Failed to load GUI env" << std::endl;
    _initializer = std::move(initFunction);
    _font = _GUIEnv->getFont("../assets/fonts/Overgrow.png");
    irr::gui::IGUISkin *skin = _GUIEnv->getSkin();
    skin->setFont(_font);
}

GUI::~GUI()
{
    _GUIEnv->drop();
}

void GUI::createButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image,
    const std::string &content, const ButtonInitializer &buttonFun,
    unsigned int id
)
{
    irr::gui::IGUIButton *button = _GUIEnv->addButton(rectInSpace, nullptr,
        _eventManager.addGUIElem(buttonFun), std::wstring(content.begin(), content.end()).c_str());
    if (image != nullptr) {
        button->setUseAlphaChannel(true);
        button->setDrawBorder(0);
        button->setImage(image);
    }
    _guiElemList[id] = button;
}

void GUI::createSeletionList(const irr::core::recti &rectInSpace,
    const std::list<std::string> &contentList, const ButtonInitializer &listFun,
    unsigned int id
)
{
    irr::gui::IGUIListBox *list =
    _GUIEnv->addListBox(rectInSpace, nullptr, _eventManager.addGUIElem(listFun), true);

    for (auto &it: contentList) {
        list->addItem(std::wstring(it.begin(), it.end()).c_str());
    }
    _guiElemList[id] = list;
}

void GUI::createText(const irr::core::recti &rectInSpace,
    const std::string &content, bool bordered, unsigned long long int id
)
{
    irr::gui::IGUIStaticText *text = _GUIEnv->addStaticText(std::wstring(content.begin(), content.end()).c_str(), rectInSpace, bordered, true);

    text->setOverrideFont(_font);
    _guiElemList[id] = text;
}

void GUI::createTextBox(const irr::core::recti &rectInSpace,
    const std::string &content, bool bordered, unsigned long long int id
)
{
    irr::gui::IGUIEditBox *text = _GUIEnv->addEditBox(std::wstring(content.begin(), content.end()).c_str(), rectInSpace, bordered);

    text->setOverrideFont(_font);
    _guiElemList[id] = text;
}

void GUI::load()
{
    if (!_initialized && _initializer) {
        _initializer();
        _initialized = true;
    } else {
        for (auto& elem: _guiElemList) {
            elem.second->setVisible(true);
        }
    }
}

void GUI::unload()
{
    for (auto& elem: _guiElemList) {
        elem.second->setVisible(false);
    }
}

void GUI::setInitializer(const GUIinitializer &initFunction)
{
    _initializer = initFunction;
}

void GUI::display() const
{
    _GUIEnv->drawAll(); // affiche le contenu du HUD. a appeler en dernier
}

irr::IEventReceiver &GUI::getEventManager() const
{
    return (_eventManager);
}

irr::gui::IGUIElement * GUI::getGUIElement(unsigned int id)
{
    if (_guiElemList.find(id) == _guiElemList.end())
        return (nullptr);
    for (auto &it: _guiElemList) {
        if (it.first == id) {
            return (it.second);
        }
    }
    return (nullptr);
}

void GUI::clearGui()
{
    for (auto &it : _guiElemList)
        it.second->remove();
    _guiElemList.clear();
}

void GUI::clearElement(const int& id)
{
    _guiElemList.erase(id);
}

void GUI::createImage()
{
    _GUIEnv->addImage({0, 0, 200, 200}, nullptr, -1, L"salut", true);
}

