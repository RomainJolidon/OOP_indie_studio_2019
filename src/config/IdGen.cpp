/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by rjolidon,
*/

#include "config/IdGen.hpp"

unsigned int IdGen::randomChar()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 255);

    return (distribution(gen));
}

std::string IdGen::generateUUID(int len)
{
    std::stringstream stream;
    std::stringstream hexStream;
    std::string converted;
    unsigned int randomChar;

    for (int i = 0; i < len; i++) {
        randomChar = IdGen::randomChar();
        hexStream << std::hex << randomChar;
        converted = hexStream.str();
        stream << (converted.length() < 2 ? '0' + converted : converted);
        converted.clear();
        hexStream.clear();
    }
    return (stream.str());
}

int IdGen::getNewId()
{
    static int id = 0;

    return (id++);
}