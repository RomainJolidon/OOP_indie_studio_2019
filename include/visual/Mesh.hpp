/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_MESH_HPP
#define BOMBERMAN_MESH_HPP

#include "AMesh.hpp"

class Mesh: public AMesh {
    public:
    Mesh(irr::scene::IMeshSceneNode *node);
    Mesh(const Mesh& mesh) = default;
    Mesh &operator=(const Mesh& mesh) = default;
    ~Mesh();
    void setAnimation(Animation animation) override;
    void activate() override ;
    void desactivate() override ;

    protected:
    private:
};

#endif //BOMBERMAN_MESH_HPP
