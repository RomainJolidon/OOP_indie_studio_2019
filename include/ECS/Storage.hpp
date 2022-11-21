/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by jfournier,
*/
#ifndef OOP_ARCADE_2019_STORAGE_HPP
#define OOP_ARCADE_2019_STORAGE_HPP

#include <vector>
#include <unordered_map>
#include "Components.hpp"

template <typename T>
class Storage {
    public:
    Storage();
    ~Storage();
    std::vector<T> componentVector;
    std::unordered_map<unsigned long long int, unsigned long long int> entityIdxToComponentIdxMap;
    template<typename ...Args>
    void addComponentForEntity(unsigned long long int entityID, Args & ... args);
    void removeComponentForEntity(unsigned long long int entityID);
    T &getComponentForEntity(unsigned long long int entityID);
    bool hasEntityComponent(unsigned long long int entityID) const;
    void refreshStoreMapIndex();
    protected:
    private:
};

template<typename T>
Storage<T>::Storage()
= default;


template<typename T>
Storage<T>::~Storage()
= default;


template<typename T>
template<typename ...Args>
void Storage<T>::addComponentForEntity(unsigned long long int entityID, Args & ... args)
{
    componentVector.emplace_back(args ...);
    componentVector.back().entityId = entityID;
    entityIdxToComponentIdxMap[entityID] = componentVector.size() - 1;
}

template<typename T>
void Storage<T>::removeComponentForEntity(unsigned long long int entityID)
{
    unsigned long long int oldPlaceIndex = 0;
    if (entityIdxToComponentIdxMap.find(entityID) == entityIdxToComponentIdxMap.end())
        return;
    oldPlaceIndex = entityIdxToComponentIdxMap[entityID];
    std::swap(componentVector[entityIdxToComponentIdxMap[entityID]], componentVector.back());
    entityIdxToComponentIdxMap[componentVector[oldPlaceIndex].entityId] = oldPlaceIndex;
    componentVector.pop_back();
    entityIdxToComponentIdxMap.erase(entityID);
}

template<typename T>
T &Storage<T>::getComponentForEntity(unsigned long long int entityID)
{
    return componentVector[entityIdxToComponentIdxMap[entityID]];
}

template<typename T>
bool Storage<T>::hasEntityComponent(unsigned long long int entityID) const
{
    return entityIdxToComponentIdxMap.find(entityID) != entityIdxToComponentIdxMap.end();
}

template<typename T>
void Storage<T>::refreshStoreMapIndex()
{
    unsigned long long int index = 0;

    for (T &it : componentVector) {
        entityIdxToComponentIdxMap[it.entityId] = index;
        index++;
    }
}

#endif //OOP_ARCADE_2019_STORAGE_HPP
