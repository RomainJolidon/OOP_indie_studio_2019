/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include "visual/Particle.hpp"

Particle::Particle(irr::scene::IParticleSystemSceneNode *node) :
AMesh(node)
{
}

Particle::~Particle()
{

}

void Particle::activate()
{
        _node->setVisible(true);
}

void Particle::desactivate()
{
        _node->setVisible(false);
}

void Particle::setAnimation(Animation animation)
{
}
