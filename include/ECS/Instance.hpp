/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_INSTANCE_HPP
#define OOP_ARCADE_2019_INSTANCE_HPP

#include <iostream>
#include <vector>

class ECSEntity;

class Instance {
    public:
    Instance();
    ~Instance();
    ECSEntity newEntity();
    std::vector<ECSEntity> _entityList;
    unsigned long long int generateId();
    protected:
    private:
    unsigned long long int _idCounter;
};

#endif //OOP_ARCADE_2019_INSTANCE_HPP
