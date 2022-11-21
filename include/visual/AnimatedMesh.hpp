/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_ANIMATEDMESH_HPP
#define BOMBERMAN_ANIMATEDMESH_HPP

#include "AMesh.hpp"

class AnimatedMesh: public AMesh {
    public:
    AnimatedMesh(irr::scene::IAnimatedMeshSceneNode *idleNode,
        irr::scene::IAnimatedMeshSceneNode *runningNode
    );
    AnimatedMesh(const AnimatedMesh& mesh) = default;
    AnimatedMesh &operator=(const AnimatedMesh& mesh) = default;
    const irr::core::vector3df& getPosition() const override ;
    void setPosition(float x, float y, float z) const override ;
    void move(float x, float y, float z) const override ;
    const irr::core::vector3df& getRotation() const override ;
    void setRotation(float x, float y, float z) const override;
    void rotate(float x, float y, float z) const override ;
    void setScale(float x, float y, float z) override ;
    irr::scene::ISceneNode *getNode() const override ;
    void setAnimation(Animation animation) override ;
    void activate() override ;
    void desactivate() override ;
    ~AnimatedMesh();

    protected:
    private:
    irr::scene::IAnimatedMeshSceneNode *_runningNode;
    Animation _curAnimation;

};

#endif //BOMBERMAN_ANIMATEDMESH_HPP
