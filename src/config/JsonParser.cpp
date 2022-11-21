/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include "config/JsonParser.hpp"

JsonData JsonParser::parseJson(const std::string &filepath, bool deletionNeeded)
{
    return JsonData(parse_json(filepath.c_str()), filepath, deletionNeeded);
}
