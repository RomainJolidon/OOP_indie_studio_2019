/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_IMESH_HPP
#define BOMBERMAN_IMESH_HPP

#include <irrlicht.h>
#include <memory>

enum Animation{IDLE, RUN};

class IMesh {
    public:
    IMesh() = default;
    virtual const irr::core::vector3df& getPosition() const = 0;
    virtual void setPosition(float x, float y, float z) const = 0;
    virtual void move(float x, float y, float z) const = 0;
    virtual const irr::core::vector3df& getRotation() const = 0;
    virtual void setRotation(float x, float y, float z) const = 0;
    virtual void rotate(float x, float y, float z) const = 0;
    virtual void setScale(float x, float y, float z) = 0;
    virtual irr::scene::ISceneNode *getNode() const = 0;
    virtual void setAnimation(Animation animation) = 0;
    virtual void activate() = 0;
    virtual void desactivate() = 0;

    protected:
    private:
};

#endif //BOMBERMAN_IMESH_HPP
