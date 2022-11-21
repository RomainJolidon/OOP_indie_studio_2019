/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "ECS/Instance.hpp"
#include "ECS/ECSEntity.hpp"


Instance::Instance()
    : _idCounter(0)
{
}

Instance::~Instance() = default;

ECSEntity Instance::newEntity()
{
    _entityList.emplace_back(generateId(), this);
    return _entityList.back();
}

unsigned long long int Instance::generateId()
{
    _idCounter++;
    return (_idCounter - 1);
}
