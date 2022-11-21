/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "visual/AnimatedMesh.hpp"

AnimatedMesh::AnimatedMesh(irr::scene::IAnimatedMeshSceneNode *idleNode,
    irr::scene::IAnimatedMeshSceneNode *runningNode
) :
AMesh(idleNode), _runningNode(runningNode), _curAnimation(RUN)
{
    setAnimation(IDLE);
}

AnimatedMesh::~AnimatedMesh()
{
    _runningNode->remove();
}

const irr::core::vector3df& AnimatedMesh::getPosition() const
{
    return (_node->getPosition());
}

void AnimatedMesh::setPosition(float x, float y, float z) const
{
    _node->setPosition(irr::core::vector3df(x, y, z));
    _runningNode->setPosition(irr::core::vector3df(x, y, z));
}

void AnimatedMesh::move(float x, float y, float z) const
{
    irr::core::vector3df pos = _node->getPosition();

    pos += irr::core::vector3df(x, y, z);
    _node->setPosition(pos);
    _runningNode->setPosition(pos);
}

const irr::core::vector3df &AnimatedMesh::getRotation() const
{
    return (_node->getRotation());
}

void AnimatedMesh::setRotation(float x, float y, float z) const
{
    _node->setRotation(irr::core::vector3df(x, y, z));
    _runningNode->setRotation(irr::core::vector3df(x, y, z));
}

void AnimatedMesh::rotate(float x, float y, float z) const
{
    irr::core::vector3df rot = _node->getRotation();

    rot += irr::core::vector3df(x, y, z);
    _node->setRotation(rot);
    _runningNode->setRotation(rot);
}

void AnimatedMesh::setScale(float x, float y, float z)
{
    _node->setScale({x, y, z});
    _runningNode->setScale({x, y, z});
}

void AnimatedMesh::activate()
{
    if (_curAnimation == IDLE) {
        _node->setVisible(true);
    } else {
        _runningNode->setVisible(true);
    }
}

void AnimatedMesh::desactivate()
{
    if (_curAnimation == IDLE) {
        _node->setVisible(false);
    } else {
        _runningNode->setVisible(false);
    }
}

irr::scene::ISceneNode *AnimatedMesh::getNode() const
{
    if (_curAnimation == IDLE)
        return _node;
    else
        return (_runningNode);
}

void AnimatedMesh::setAnimation(Animation animation)
{
    desactivate();
    _curAnimation = animation;
    activate();
}
