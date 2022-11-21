/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_AMESH_HPP
#define BOMBERMAN_AMESH_HPP

#include "IMesh.hpp"

class AMesh: public IMesh {
    public:
    AMesh(irr::scene::ISceneNode *node);
    ~AMesh();
    const irr::core::vector3df& getPosition() const override ;
     virtual void setPosition(float x, float y, float z) const override ;
    virtual void move(float x, float y, float z) const override ;
    virtual const irr::core::vector3df& getRotation() const override ;
    virtual void setRotation(float x, float y, float z) const override;
    virtual void rotate(float x, float y, float z) const override ;
    virtual void setScale(float x, float y, float z) override ;
    virtual irr::scene::ISceneNode *getNode() const override ;
    void setAnimation(Animation animation) override = 0;
    void activate() override = 0;
    void desactivate() override = 0;
    protected:
    irr::scene::ISceneNode *_node;
    private:

};

#endif //BOMBERMAN_AMESH_HPP
