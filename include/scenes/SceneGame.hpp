/*
** EPITECH PROJECT, 2023
** SceneGame
** File description:
** Created by rjolidon,
*/

#ifndef SCENEOPTION_HPP
#define SCENEOPTION_HPP

#include "scenes/AScene.hpp"
#include <cstdlib>
#include <codecvt>
#include <locale>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "ECS/Components.hpp"
#include "ECS/Storage.hpp"
#include "ECS/Instance.hpp"
#include "ECS/InputSystem.hpp"
#include "ECS/MovementSystem.hpp"
#include "ECS/CollisionSystem.hpp"
#include "ECS/ActionSystem.hpp"
#include "ECS/IASystem.hpp"
#include "ECS/MapSystem.hpp"
#include "ECS/ExplosiveSystem.hpp"
#include "ECS/TimerSystem.hpp"
#include "ECS/EffectSystem.hpp"
#include "ECS/CollectibleSystem.hpp"
#include "ECS/EndGameSystem.hpp"
#include "visual/Particle.hpp"

class SceneGame : public AScene
{
    public:
    SceneGame(VisualManager &visualManager, Config &config,
        GameConfig &gameConfig
    );
    ~SceneGame();
    void createAllEntities();
    void displayScore();
    void oneCycleLoop() override ;
    void load() override ;
    void unload() override ;
    void emptyAllEntities();
    void resetGame();
    bool CheckIfSpawn(int x, int y, int size, int length);
    bool CheckIfBorder(int x, int y, int size, int length);
    void CreateBlock(int x, int y, const char *texturePath, bool destroyable);
    void CreateBonus(int x, int y, Effect effect);
    void CreateFire(int x, int y);
    void createBomb(int x, int y, unsigned long long int parentId, int range
    );
    void initMapSize(bool newGame = true);
    void saveMap(const std::string &filepath);
    void loadMap();
    void generateNewMap();
    void createCustomCharacter(int characterId, float posX, float posY,
        bool isAi, int bombs = 1, int range = 2, bool wallPass = false, int speed = 10
    );
    void CreateCharacter(unsigned long long id, int pos, float posX, float posY,
        int speed
    );

    protected:
    private:
    Instance _instance;
    Storage<Model> _modelStorage;
    Storage<Velocity> _velocityStorage;
    Storage<Position> _positionStorage;
    Storage<Collider> _colliderStorage;
    Storage<Playable> _playableStorage;
    Storage<Orientation> _orientationStorage;
    Storage<Explosive> _explosiveStorage;
    Storage<Destroyable> _destroyableStorage;
    Storage<Collectible> _collectibleStorage;
    Storage<Destroyer> _destroyerStorage;
    Storage<Timer> _timerStorage;
    Storage<Clock> _clockStorage;
    InputSystem _inputSystem;
    MovementSystem _movementSystem;
    CollisionSystem _collisionSystem;
    ActionSystem _actionSystem;
    MapSystem _mapSystem;
    EffectSystem _effectSystem;
    EndGameSystem _endgameSystem;
    CollectibleSystem _collectibleSystem;
    ExplosiveSystem _explosiveSystem;
    TimerSystem _timerSystem;
    IASystem _iaSystem;

    int _score;
    std::vector<std::string> _map;
    std::string _mapName;
    std::chrono::time_point<std::chrono::steady_clock> _clock;
    unsigned long long int _elapsedTime;
    std::vector<PlayerType> charsTypes;
    std::vector<int> _scoresIds;
    bool _isGameEnded;
};

#endif //SCENEOPTION_HPP
