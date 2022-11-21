/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include "visual/Mesh.hpp"

Mesh::Mesh(irr::scene::IMeshSceneNode *node) :
AMesh(node)
{
}

Mesh::~Mesh()
{

}

void Mesh::activate()
{
        _node->setVisible(true);
}

void Mesh::desactivate()
{
        _node->setVisible(false);
}

void Mesh::setAnimation(Animation animation)
{
}
