/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "visual/AMesh.hpp"

AMesh::AMesh(irr::scene::ISceneNode *node):
_node(node)
{
}

AMesh::~AMesh()
{
    _node->remove();
}

void AMesh::setPosition(float x, float y, float z) const
{
    _node->setPosition(irr::core::vector3df(x, y, z));
}

const irr::core::vector3df &AMesh::getPosition() const
{
    return (_node->getPosition());
}

void AMesh::move(float x, float y, float z) const
{
    irr::core::vector3df pos = _node->getPosition();

    pos += irr::core::vector3df(x, y, z);
    _node->setPosition(pos);
}

const irr::core::vector3df &AMesh::getRotation() const
{
    return (_node->getRotation());
}

void AMesh::setRotation(float x, float y, float z) const
{
    _node->setRotation(irr::core::vector3df(x, y, z));
}

void AMesh::rotate(float x, float y, float z) const
{
    irr::core::vector3df rot = _node->getRotation();

    rot += irr::core::vector3df(x, y, z);
    _node->setRotation(rot);
}

void AMesh::setScale(float x, float y, float z)
{
    _node->setScale({x, y, z});
}

irr::scene::ISceneNode *AMesh::getNode() const
{
    return _node;
}
