/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef OOP_INDIE_STUDIO_2019_VISUALMANAGER_HPP
#define OOP_INDIE_STUDIO_2019_VISUALMANAGER_HPP

#include <iostream>
#include <string>
#include "Mesh.hpp"
#include "AnimatedMesh.hpp"
#include "events/EventManager.hpp"
#include "config/IdGen.hpp"

class VisualManager {
    public:
    VisualManager(const std::string &title, int width, int height);
    virtual std::shared_ptr<IMesh> getNewAnimatedMesh(
        irr::scene::IAnimatedMeshSceneNode *idleNode,
        irr::scene::IAnimatedMeshSceneNode *runningNode,
        irr::video::ITexture *texture, const irr::core::vector3df &pos,
        const irr::core::vector3df &rot
    ) const;
    virtual std::shared_ptr<IMesh> getNewMesh(
        irr::scene::IMeshSceneNode *node, irr::video::ITexture *texture,
        const irr::core::vector3df &pos, const irr::core::vector3df &rot
    ) const;
    bool isRunning() const;
    irr::IrrlichtDevice& getDevice() const;

    ~VisualManager();

    protected:
    private:
    irr::IrrlichtDevice *_device;

};

#endif //OOP_INDIE_STUDIO_2019_VISUALMANAGER_HPP
