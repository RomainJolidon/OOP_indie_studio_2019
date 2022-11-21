/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/

#ifndef OOP_ARCADE_2019_ECSENTITY_HPP
#define OOP_ARCADE_2019_ECSENTITY_HPP

class Instance;

class ECSEntity {
    public:
    ECSEntity(unsigned long long int uniqueId, Instance * parentInstance);
    ~ECSEntity();
    unsigned long long int _id;
    Instance * _ownInstance{};
    private:
    protected:
};

#endif //OOP_ARCADE_2019_ECSENTITY_HPP
