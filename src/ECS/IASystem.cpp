/*
** EPITECH PROJECT, 2023
** IABobSystem
** File description:
** IABobSystem by rjolidon,
*/

#include "ECS/IASystem.hpp"

IASystem::IASystem()
{}

IASystem::~IASystem()
{}

void IASystem::update(Storage<Velocity> &velocityStorage,
    Storage<Collider> &colliderStorage, Storage<Position> &positionStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage,
    Storage<Orientation> &orientationStorage,
    Storage<Explosive> &explosiveStorage, std::vector<std::string> &map,
    Storage<Destroyer> &destroyerStorage
)
{
    for (auto it : playableStorage.componentVector) {
        if (!it.isAI)
            continue;
        if (positionStorage.getComponentForEntity(it.entityId).spaceX == velocityStorage.getComponentForEntity(it.entityId).destX &&
        positionStorage.getComponentForEntity(it.entityId).spaceY == velocityStorage.getComponentForEntity(it.entityId).destY) {
            process(it.entityId, velocityStorage, colliderStorage,
                positionStorage, destroyableStorage, playableStorage,
                orientationStorage, explosiveStorage, map, destroyerStorage);
        }
    }
}

void IASystem::process(unsigned long long entityID,
    Storage<Velocity> &velocityStorage, Storage<Collider> &colliderStorage,
    Storage<Position> &positionStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage,
    Storage<Orientation> &orientationStorage,
    Storage<Explosive> &explosiveStorage, std::vector<std::string> &map,
    Storage<Destroyer> &destroyerStorage
)
{
    if (GetClosestDanger(entityID, positionStorage, explosiveStorage,
        playableStorage, destroyerStorage)) {
        MoveAwayFromBomb(entityID, positionStorage, destroyableStorage,
            playableStorage, velocityStorage, orientationStorage,
            map);
    } else {
        GetClosestTarget(entityID, velocityStorage, playableStorage);
        MoveToTarget(entityID, positionStorage, destroyableStorage,
            playableStorage, velocityStorage, orientationStorage,
            map);
    }
}

int IASystem::getDistance(
    float IaPosX, float IaPosY, float targetPosX, float targetPosY)
{
    return (std::sqrt(std::pow(targetPosX - IaPosX, 2) + std::pow(targetPosY - IaPosY, 2) * 1.0));
}

void IASystem::GetClosestTarget(unsigned long long entityID,
    Storage<Velocity> &velocityStorage, Storage<Playable> &playableStorage
)
{
    Velocity &IABobPos = velocityStorage.getComponentForEntity(entityID);
    IA &ia = playableStorage.getComponentForEntity(entityID).ai;
    Velocity *initialTargetPos;

    ia.targetX = 1000000;
    ia.targetY = 1000000;
    for (auto &it : playableStorage.componentVector) {
        if (entityID == it.entityId)
            continue;
        /*if (ia.targetX == 0 && ia.targetY == 0) {
            ia.targetX = velocityStorage.getComponentForEntity(it.entityId).destX;
            ia.targetY = velocityStorage.getComponentForEntity(it.entityId).destY;
            ia.targetId = it.entityId;
        }*/
        initialTargetPos = &velocityStorage.getComponentForEntity(it.entityId);
        if (getDistance(IABobPos.destX, IABobPos.destY, initialTargetPos->destX,
            initialTargetPos->destY) <
            getDistance(IABobPos.destX, IABobPos.destY, ia.targetX,
                ia.targetY)) {
            ia.targetX = initialTargetPos->destX;
            ia.targetY= initialTargetPos->destY;
            ia.targetId = it.entityId;
        }
    }
}

bool IASystem::GetClosestDanger(unsigned long long entityID,
    Storage<Position> &positionStorage, Storage<Explosive> &explosiveStorage,
    Storage<Playable> &playableStorage, Storage<Destroyer> &destroyerStorage
)
{
    Position &IABobPos = positionStorage.getComponentForEntity(entityID);
    IA &ia = playableStorage.getComponentForEntity(entityID).ai;
    Position *initialDangerPos;
    bool closeFromDanger = false;

    ia.targetX = 0;
    ia.targetY = 0;
    for (auto &it : explosiveStorage.componentVector) {
        if (entityID == it.entityId)
            continue;
        initialDangerPos = &positionStorage.getComponentForEntity(it.entityId);
        if (getDistance(IABobPos.spaceX, IABobPos.spaceY, initialDangerPos->spaceX,
            initialDangerPos->spaceY) < (playableStorage.getComponentForEntity(entityID).stats.range + 2) * 100 &&
            getDistance(IABobPos.spaceX, IABobPos.spaceY, initialDangerPos->spaceX,
            initialDangerPos->spaceY) < getDistance(IABobPos.spaceX, IABobPos.spaceY, ia.targetX, ia.targetY)) {
            ia.targetX = initialDangerPos->spaceX;
            ia.targetY= initialDangerPos->spaceY;
            ia.targetId = it.entityId;
            closeFromDanger = true;
        }
    }
    for (auto &it : destroyerStorage.componentVector) {
        if (entityID == it.entityId)
            continue;
        initialDangerPos = &positionStorage.getComponentForEntity(it.entityId);
        if (getDistance(IABobPos.spaceX, IABobPos.spaceY, initialDangerPos->spaceX,
            initialDangerPos->spaceY) < 200 &&
            getDistance(IABobPos.spaceX, IABobPos.spaceY, initialDangerPos->spaceX,
            initialDangerPos->spaceY) < getDistance(IABobPos.spaceX, IABobPos.spaceY, ia.targetX, ia.targetY)) {
            ia.targetX = initialDangerPos->spaceX;
            ia.targetY= initialDangerPos->spaceY;
            ia.targetId = it.entityId;
            closeFromDanger = true;
        }
    }
    return (closeFromDanger);
}


void IASystem::MoveToTarget(unsigned long long int entityID,
    Storage<Position> &positionStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage, Storage<Velocity> &velocityStorage,
    Storage<Orientation> &orientationStorage, std::vector<std::string> &map
)
{
    Velocity &iaVelocity = velocityStorage.getComponentForEntity(entityID);
    IA &targetVelocity = playableStorage.getComponentForEntity(entityID).ai;
    Orientation &entityOrientation = orientationStorage.getComponentForEntity(entityID);
    float distX = 0;
    float distY = 0;
    int breakStatus = -1;
    std::vector<Dir> pref;

    if (iaVelocity.destX > targetVelocity.targetX) {
        distX = iaVelocity.destX - targetVelocity.targetX;
    } else {
        distX = targetVelocity.targetX - iaVelocity.destX;
    }

    if (iaVelocity.destY > targetVelocity.targetY) {
        distY = iaVelocity.destY - targetVelocity.targetY;
    } else {
        distY = targetVelocity.targetY - iaVelocity.destY;
    }

    if (distX > distY) {
        if (iaVelocity.destX > targetVelocity.targetX) {
            pref = {LEFT, UP, DOWN};
        } else {
            pref = {RIGHT, UP, DOWN};
        }
    } else {
        if (iaVelocity.destY > targetVelocity.targetY) {
            pref = {UP, LEFT, RIGHT};
        } else {
            pref = {DOWN, LEFT, RIGHT};
        }
    }

    for (auto &mpref: pref) {
        switch (mpref) {
        case LEFT:
            breakStatus = isBreakable(-1, 0, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 0) {
                playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                return;
            } else if (breakStatus == 1) {
                if (distX < 200)
                    playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                else {
                    targetVelocity.targetX--;
                    MoveToTargetX(targetVelocity, iaVelocity, entityOrientation,
                        map);
                }
                return;
            }
            break;
        case RIGHT:
            breakStatus = isBreakable(1, 0, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 0) {
                playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                return;
            } else if (breakStatus == 1) {
                if (distX < 200)
                    playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                else {
                    targetVelocity.targetX++;
                    MoveToTargetX(targetVelocity, iaVelocity, entityOrientation,
                        map);
                }
                return;
            }
            break;
        case UP:
            breakStatus = isBreakable(0, -1, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 0) {
                playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                return;
            } else if (breakStatus == 1) {
                if (distY < 200)
                    playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                else {
                    MoveToTargetY(targetVelocity, iaVelocity, entityOrientation,
                        map);
                }
                return;
            }
            break;
        case DOWN:
            breakStatus = isBreakable(0, 1, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 0) {
                playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                return;
            } else if (breakStatus == 1) {
                if (distY < 200)
                    playableStorage.getComponentForEntity(entityID).action = PUT_BOMB;
                else {
                    MoveToTargetY(targetVelocity, iaVelocity, entityOrientation,
                        map);
                }
                return;
            }
            break;
        default:
            break;
        }
    }
}

void IASystem::MoveToTargetX(IA &targetVelocity, Velocity &iaVelocity,
    Orientation &entityOrientation, std::vector<std::string> &map
)
{
    if (iaVelocity.destX < targetVelocity.targetX) { // need to move to right
        iaVelocity.destX += 100;
        iaVelocity.speedX =  iaVelocity.speedX < 0 ? -iaVelocity.speedX : iaVelocity.speedX;
        entityOrientation.angle = 90;
    } else if (iaVelocity.destX > targetVelocity.targetX) { // need to move left
        iaVelocity.destX -= 100;
        iaVelocity.speedX =  iaVelocity.speedX > 0 ? -iaVelocity.speedX : iaVelocity.speedX;
        entityOrientation.angle = 270;
    }
}

void IASystem::MoveToTargetY(IA &targetVelocity, Velocity &iaVelocity,
    Orientation &entityOrientation, std::vector<std::string> &map
)
{
    if (iaVelocity.destY < targetVelocity.targetY) { // need to move to up
        iaVelocity.destY += 100;
        iaVelocity.speedY =  iaVelocity.speedY < 0 ? -iaVelocity.speedY : iaVelocity.speedY;
        entityOrientation.angle = 180;
    } else if (iaVelocity.destY > targetVelocity.targetY) { // need to move down
        iaVelocity.destY -= 100;
        iaVelocity.speedY =  iaVelocity.speedY > 0 ? -iaVelocity.speedY : iaVelocity.speedY;
        entityOrientation.angle = 360;
    }
}

void IASystem::MoveAwayFromBomb(unsigned long long int entityID,
    Storage<Position> &positionStorage,
    Storage<Destroyable> &destroyableStorage,
    Storage<Playable> &playableStorage, Storage<Velocity> &velocityStorage,
    Storage<Orientation> &orientationStorage, std::vector<std::string> &map
)
{
    Velocity &iaVelocity = velocityStorage.getComponentForEntity(entityID);
    IA &targetVelocity = playableStorage.getComponentForEntity(entityID).ai;
    Orientation &entityOrientation = orientationStorage.getComponentForEntity(entityID);

    float distX = 0;
    float distY = 0;
    int breakStatus = -1;
    std::vector<Dir> pref;

    if (iaVelocity.destX > targetVelocity.targetX) {
        distX = iaVelocity.destX - targetVelocity.targetX;
    } else {
        distX = targetVelocity.targetX - iaVelocity.destX;
    }

    if (iaVelocity.destY > targetVelocity.targetY) {
        distY = iaVelocity.destY - targetVelocity.targetY;
    } else {
        distY = targetVelocity.targetY - iaVelocity.destY;
    }

    if (distX > distY) {
        if (iaVelocity.destX > targetVelocity.targetX) {
            pref = {RIGHT, UP, DOWN, LEFT};
        } else {
            pref = {LEFT, UP, DOWN, RIGHT};
        }
    } else {
        if (iaVelocity.destY > targetVelocity.targetY) {
            pref = {UP, LEFT, RIGHT, DOWN};
        } else {
            pref = {DOWN, LEFT, RIGHT, UP};
        }
    }

    for (auto &mpref: pref) {
        switch (mpref) {
        case LEFT:
            breakStatus = isBreakable(-1, 0, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 1) {
                targetVelocity.targetX++;
                MoveAwayFromBombX(targetVelocity, iaVelocity, entityOrientation);
                return;
            }
            break;
        case RIGHT:
            breakStatus = isBreakable(1, 0, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 1) {
                targetVelocity.targetX--;
                MoveAwayFromBombX(targetVelocity, iaVelocity, entityOrientation);
                return;
            }
            break;
        case UP:
            breakStatus = isBreakable(0, 1, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 1) {
                targetVelocity.targetY--;
                MoveAwayFromBombY(targetVelocity, iaVelocity, entityOrientation);
                return;
            }
            break;
        case DOWN:
            breakStatus = isBreakable(0, -1, map, entityID, positionStorage,
                playableStorage.getComponentForEntity(entityID).stats.wallPass);
            if (breakStatus == 1) {
                targetVelocity.targetY++;
                MoveAwayFromBombY(targetVelocity, iaVelocity, entityOrientation);
                return;
            }
            break;
        default:
            break;
        }
    }
}

void IASystem::MoveAwayFromBombX(IA &targetVelocity, Velocity &iaVelocity,
    Orientation &entityOrientation
)
{
    if (iaVelocity.destX < targetVelocity.targetX) { // need to move to left
        iaVelocity.destX -= 100;
        iaVelocity.speedX =  iaVelocity.speedX > 0 ? -iaVelocity.speedX : iaVelocity.speedX;
        entityOrientation.angle = 270;
    } else if (iaVelocity.destX >= targetVelocity.targetX) { // need to move right
        iaVelocity.destX += 100;
        iaVelocity.speedX =  iaVelocity.speedX < 0 ? -iaVelocity.speedX : iaVelocity.speedX;
        entityOrientation.angle = 90;
    }
}

void IASystem::MoveAwayFromBombY(IA &targetVelocity, Velocity &iaVelocity,
    Orientation &entityOrientation
)
{
    if (iaVelocity.destY <= targetVelocity.targetY) { // need to move to down
        iaVelocity.destY -= 100;
        iaVelocity.speedY =  iaVelocity.speedY > 0 ? -iaVelocity.speedY : iaVelocity.speedY;
        entityOrientation.angle = 260;
    } else if (iaVelocity.destY > targetVelocity.targetY) { // need to move up
        iaVelocity.destY += 100;
        iaVelocity.speedY =  iaVelocity.speedY < 0 ? -iaVelocity.speedY : iaVelocity.speedY;
        entityOrientation.angle = 180;
    }
}

int IASystem::isBreakable(int vectorX, int vectorY,
    std::vector<std::string> &map, unsigned long long int entityId,
    Storage<Position> &positionStorage, bool wallPass
) const
{
    Position &entityPos = positionStorage.getComponentForEntity(entityId);

    if (vectorX != 0) {
        if (vectorX < 0) {
            if (map[entityPos.y][entityPos.x - 1] == 'p')
                return (0);
            if (map[entityPos.y][entityPos.x - 1] == 'x') {
                if (wallPass)
                    return (1);
                return (0);
            }
            if (map[entityPos.y][entityPos.x - 1] == ' ')
                return (1);
            return (-1);
        } else if (vectorX > 0) {
            if (map[entityPos.y][entityPos.x + 1] == 'p')
                return (0);
            if (map[entityPos.y][entityPos.x + 1] == 'x') {
                if (wallPass)
                    return (1);
                return (0);
            }
            if (map[entityPos.y][entityPos.x + 1] == ' ')
                return (1);
            return (-1);
        }
    }
    if (vectorY != 0) {
        if (vectorY < 0) {
            if (map[entityPos.y - 1][entityPos.x] == 'p') {
                return (0);
            }
            if (map[entityPos.y - 1][entityPos.x] == 'x') {
                if (wallPass)
                    return (1);
                return (0);
            }
            if (map[entityPos.y - 1][entityPos.x] == ' ')
                return (1);
            return (-1);
        } else if (vectorY > 0) {
            if (map[entityPos.y + 1][entityPos.x] == 'p') {
                return (0);
            }
            if (map[entityPos.y + 1][entityPos.x] == 'x') {
                if (wallPass)
                    return (1);
                return (0);
            }
            if (map[entityPos.y + 1][entityPos.x] == ' ')
                return (1);
            return (-1);
        }
    }
    return (1);
}