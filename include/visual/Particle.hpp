/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Particle
*/

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "AMesh.hpp"

class Particle: public AMesh {
    public:
    Particle(irr::scene::IParticleSystemSceneNode *node);
    Particle(const Particle& part) = default;
    Particle &operator=(const Particle& part) = default;
    ~Particle();
    void setAnimation(Animation animation) override;
    void activate() override ;
    void desactivate() override ;

    protected:
    private:
};

#endif /* !PARTICLE_HPP_ */