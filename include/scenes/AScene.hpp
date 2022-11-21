/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_SCENE_HPP
#define BOMBERMAN_SCENE_HPP

#include <vector>
#include "IScene.hpp"
#include "visual/VisualManager.hpp"
#include "events/EventManager.hpp"
#include "visual/Gui.hpp"
#include "config/Config.hpp"
#include "visual/Camera.hpp"
#include "config/GameConfig.hpp"

#define PLAYER1_IDLE    "../assets/bomberguy/idle.b3d"
#define PLAYER1_RUNNING "../assets/bomberguy/running.b3d"
#define PLAYER1_TEXTURE "../assets/bomberguy/Texture.png"

#define PLAYER2_IDLE    "../assets/sans/idle.b3d"
#define PLAYER2_RUNNING "../assets/sans/running.b3d"
#define PLAYER2_TEXTURE "../assets/sans/Texture.png"

#define PLAYER3_IDLE    "../assets/polnareff/idle.b3d"
#define PLAYER3_RUNNING "../assets/polnareff/running.b3d"
#define PLAYER3_TEXTURE "../assets/polnareff/Texture.png"

#define PLAYER4_IDLE    "../assets/shrek/idle.b3d"
#define PLAYER4_RUNNING "../assets/shrek/running.b3d"
#define PLAYER4_TEXTURE "../assets/shrek/Texture.png"

class AScene: public IScene {
    public:
    AScene(VisualManager &visualManager, Config &config, GameConfig &gameConfig
    );
    void display() const override;
    virtual void oneCycleLoop() = 0;
    irr::scene::IMeshSceneNode *addMesh(const std::string &meshPath) override;
    irr::scene::IAnimatedMeshSceneNode *addAnimatedMesh(
        const std::string &meshPath
    ) override;
    const irr::scene::ISceneManager& getScene() const override ;
    bool isSceneLoaded() const override ;
    void load() = 0 ;
    void unload() = 0 ;
    void addButton(const irr::core::recti &rectInSpace, irr::video::ITexture *image, const std::string &content, const ButtonInitializer&) override ;
    void addText(const irr::core::recti &rectInSpace, const std::string &content, bool bordered) override ;
    void addImage(const irr::core::recti &rectInSpace, const std::string &path) override;
    VisualManager &getVisualManager() const override ;
    irr::scene::ISceneManager &getSceneManager() const override ;
    irr::video::IVideoDriver &getVideoDriver() const override ;
    ~AScene();

    Config &_config;
    protected:
    std::shared_ptr<IEventManager> _eventManager;
    VisualManager &_visualManager;
    GameConfig &_gameConfig;
    irr::video::IVideoDriver *_driver;
    irr::scene::ISceneManager *_sceneManager;
    std::unique_ptr<IGUI> _GUIEnv;
    std::unique_ptr<Camera> _camera;
    std::vector<std::pair<irr::video::ITexture *, irr::core::recti>> _images;
    bool _loaded;
    bool _initialized;
    private:
};

#endif //BOMBERMAN_SCENE_HPP
