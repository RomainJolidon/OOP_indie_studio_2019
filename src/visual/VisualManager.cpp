/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/


#include "visual/VisualManager.hpp"

VisualManager::VisualManager(const std::string &title, int width, int height) :
_device(nullptr)
{
    _device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(width, height), 16,
        false, false, false);
    if (!_device) {
        std::cerr << "failed to load device" << std::endl;
        return;
    }
    _device->setWindowCaption(std::wstring(title.begin(), title.end()).c_str());
}

VisualManager::~VisualManager()
{
    _device->drop();
}

std::shared_ptr<IMesh> VisualManager::getNewAnimatedMesh(
    irr::scene::IAnimatedMeshSceneNode *idleNode,
    irr::scene::IAnimatedMeshSceneNode *runningNode,
    irr::video::ITexture *texture, const irr::core::vector3df &pos,
    const irr::core::vector3df &rot
) const
{

    if (idleNode) {
        idleNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        idleNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        idleNode->setMD2Animation(irr::scene::EMAT_STAND);
        idleNode->setMaterialTexture( 0, texture);
        idleNode->setPosition(pos);
        idleNode->setRotation(rot);
        idleNode->setName(IdGen::generateUUID(8).c_str());
        idleNode->setID(rand() % 2048);

        runningNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        runningNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        runningNode->setMD2Animation(irr::scene::EMAT_STAND);
        runningNode->setMaterialTexture( 0, texture);
        runningNode->setPosition(pos);
        runningNode->setRotation(rot);
        runningNode->setName(IdGen::generateUUID(8).c_str());
        runningNode->setID(rand() % 2048);
        return (std::shared_ptr<IMesh>(new AnimatedMesh(idleNode, runningNode)));
    }
    return (nullptr);
}

std::shared_ptr<IMesh> VisualManager::getNewMesh(
    irr::scene::IMeshSceneNode *node, irr::video::ITexture *texture,
    const irr::core::vector3df &pos, const irr::core::vector3df &rot
) const
{

    if (node) {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMaterialTexture( 0, texture);
        node->setPosition(pos);
        node->setRotation(rot);
        node->setName(IdGen::generateUUID(8).c_str());
        return (std::shared_ptr<IMesh>(new Mesh(node)));
    }
    return (nullptr);
}

bool VisualManager::isRunning() const
{
    return (_device->run());
}

irr::IrrlichtDevice &VisualManager::getDevice() const
{
    return (*_device);
}
