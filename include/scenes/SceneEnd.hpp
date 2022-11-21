/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by Malo,
*/
#ifndef BOMBERMAN_SCENEEND_HPP
#define BOMBERMAN_SCENEEND_HPP

#include "scenes/AScene.hpp"

class SceneEnd : public AScene
{
    public:
    SceneEnd(VisualManager& visualManager);
    void initialize();
    ~SceneEnd();

    protected:
    private:
};

#endif //BOMBERMAN_SCENEEND_HPP
