/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_JSONPARSER_HPP
#define BOMBERMAN_JSONPARSER_HPP

#include <string>
#include "JsonData.hpp"

class JsonParser {
    public:
    static JsonData parseJson(const std::string &filepath, bool deletionNeeded = true);
    protected:
    private:
};

#endif //BOMBERMAN_JSONPARSER_HPP
