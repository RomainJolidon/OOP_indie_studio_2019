/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#include "ECS/ECSEntity.hpp"
#include "ECS/Instance.hpp"


ECSEntity::ECSEntity(unsigned long long int uniqueId, Instance *parentInstance)
    : _id(uniqueId), _ownInstance(parentInstance)
{
}

ECSEntity::~ECSEntity() = default;

