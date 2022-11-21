/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_ISCENE_HPP
#define BOMBERMAN_ISCENE_HPP

#include <irrlicht.h>
#include <memory>
#include <functional>

#include "SceneIndex.hpp"
#include "visual/VisualManager.hpp"
#include "visual/IGUI.hpp"

typedef std::function<void (void)> initializer;
class IScene {
    public:
    ~IScene() = default;
    virtual irr::scene::IMeshSceneNode *addMesh(const std::string &meshPath) = 0;
    virtual irr::scene::IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &meshPath) = 0;
    virtual void display() const = 0;
    virtual void oneCycleLoop() = 0;
    virtual const irr::scene::ISceneManager& getScene() const = 0;
    virtual bool isSceneLoaded() const = 0;
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void addButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image, const std::string &content, const ButtonInitializer&) = 0;
    virtual void addText(const irr::core::recti &rectInSpace, const std::string &content, bool bordered) = 0;
    virtual void addImage(const irr::core::recti &rectInSpace, const std::string &path) = 0;
    virtual VisualManager &getVisualManager() const = 0;
    virtual irr::scene::ISceneManager &getSceneManager() const = 0;
    virtual irr::video::IVideoDriver &getVideoDriver() const = 0;
    protected:
    private:

};

#endif //BOMBERMAN_ISCENE_HPP
