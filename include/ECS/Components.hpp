/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_COMPONENTS_HPP
#define OOP_ARCADE_2019_COMPONENTS_HPP

#include <memory>
#include "visual/IMesh.hpp"

enum Effect {
    NO_EFFECT,
    BOMB_UP,
    FIRE_UP,
    WALL_PASS,
    SPEED_UP
};

enum Action {
    NO_ACTION,
    PUT_BOMB
};

enum Player {
    PLAYER_ONE = 1,
    PLAYER_TWO = 2,
    PLAYER_THREE = 3,
    PLAYER_FOUR = 4
};

struct Stats {
    int nbBombs;
    int range;
    bool wallPass;
};

struct Model {
    unsigned long long int entityId;
    std::shared_ptr<IMesh> mesh;
};

struct Position {
    unsigned long long int entityId;
    int x;
    int y;
    float spaceX;
    float spaceY;
};

struct Orientation {
    unsigned long long int entityId;
    int angle;
};

struct Velocity {
    unsigned long long int entityId;
    float destX;
    float destY;
    float speedX;
    float speedY;
};

struct Collider {
    unsigned long long int entityId;
    int height;
    int width;
};

struct Destroyer {
    unsigned long long int entityId;
    bool destroyer;
};

struct Destroyable {
    unsigned long long int entityId;
    bool destroyable;
};

struct IA {
    unsigned long long int targetId;
    float targetX;
    float targetY;
};

struct Playable {
    unsigned long long int entityId;
    Player playerId;
    Action action;
    irr::EKEY_CODE up;
    irr::EKEY_CODE down;
    irr::EKEY_CODE left;
    irr::EKEY_CODE right;
    irr::EKEY_CODE bomb;
    Effect effect;
    struct Stats stats;
    bool is_alive;
    bool isAI;
    struct IA ai;
};

struct Timer {
    unsigned long long int entityId;
    unsigned long long int treshold;
    int offset;
};

struct Explosive {
    unsigned long long int entityId;
    unsigned long long int parentId;
    int range;
    struct Timer timer;
};

struct Clock {
    unsigned long long int entityId;
    unsigned long long int treshold;
    int offset;
};

struct Collectible {
    unsigned long long int entityId;
    Effect effect;
};

#endif //OOP_ARCADE_2019_COMPONENTS_HPP
