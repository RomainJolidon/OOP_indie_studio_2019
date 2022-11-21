/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_CAMERA_HPP
#define BOMBERMAN_CAMERA_HPP

#include <irrlicht.h>

class Camera {
    public:
    Camera(irr::scene::ISceneManager &sceneManager);
    ~Camera();
    void load();
    void unload();
    const irr::core::vector3df& getPosition() const;
    void setPosition(float x, float y, float z) const ;
    void move(float x, float y, float z) const ;
    const irr::core::vector3df& getRotation() const ;
    void setRotation(float x, float y, float z) const;
    void rotate(float x, float y, float z) const ;
    void lookAt(float x, float y, float z) const ;
    void addParent(irr::scene::ISceneNode *parent) const;
    irr::scene::ICameraSceneNode *getCamera() const;

    protected:
    private:
    irr::scene::ICameraSceneNode *_cam;
};

#endif //BOMBERMAN_CAMERA_HPP
