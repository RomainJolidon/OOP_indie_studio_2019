/*
** EPITECH PROJECT, 2023
** CCP_plazza_2019
** File description:
** Created by rjolidon,
*/

#ifndef CCP_PLAZZA_2019_IDGEN_HPP
#define CCP_PLAZZA_2019_IDGEN_HPP

#include <sstream>
#include <random>
#include <string>

class IdGen {
    public:
    IdGen() = default;
    ~IdGen() = default;
    static std::string generateUUID(int len);
    static int getNewId();

    protected:
    private:
    static unsigned int randomChar();
};

#endif //CCP_PLAZZA_2019_IDGEN_HPP
