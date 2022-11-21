/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "visual/Camera.hpp"

Camera::Camera(irr::scene::ISceneManager &sceneManager):
_cam(sceneManager.addCameraSceneNode(nullptr, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0)))
{
}

Camera::~Camera()
{
}

void Camera::load()
{
    _cam->setVisible(true);
}

void Camera::unload()
{
    _cam->setVisible(false);
}

const irr::core::vector3df &Camera::getPosition() const
{
    return _cam->getPosition();
}

void Camera::setPosition(float x, float y, float z) const
{
    _cam->setPosition(irr::core::vector3df(x, y, z));
}

void Camera::move(float x, float y, float z) const
{
    irr::core::vector3df pos = _cam->getPosition();

    pos += irr::core::vector3df(x, y, z);
    _cam->setPosition(pos);
}

const irr::core::vector3df &Camera::getRotation() const
{
    return _cam->getRotation();
}

void Camera::rotate(float x, float y, float z) const
{
    irr::core::vector3df rot = _cam->getRotation();

    rot.X += x;
    rot.Y += y;
    rot.Z += z;
    _cam->setRotation(rot);
}

void Camera::setRotation(float x, float y, float z) const
{
    _cam->setRotation(irr::core::vector3df(x, y, z));
}

void Camera::lookAt(float x, float y, float z) const
{
    _cam->setTarget(irr::core::vector3df(x, y, z));
}

void Camera::addParent(irr::scene::ISceneNode *parent) const
{
    _cam->setParent(parent);
}

irr::scene::ICameraSceneNode *Camera::getCamera() const
{
    return (_cam);
}
