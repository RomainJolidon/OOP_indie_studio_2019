/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#ifndef BOMBERMAN_JSONDATA_HPP
#define BOMBERMAN_JSONDATA_HPP

#include <memory>
#include <string>
#include <cstdarg>
#include <vector>

extern "C" {
    #include "json_parser.h"
};

class JsonData {
    public:
    JsonData(data_t *data, std::string filepath = "", bool needDelete = true);
    std::string getAttributeOfKey(const std::string &key) const;
    data_t * getObjectWithAttribute(const std::string &key, const std::string &value) const;
    void goToObjectWithAttribute(const std::string &key, const std::string &value);
    void writeData();
    void goToRootData();
    data_t * getListOfKey(const std::string &key) const;
    void addObject(const std::string &key, int nbArgs, ...);
    void addList(const std::string &key, int nbArgs, ...);
    void addListofString(const std::string &key, std::vector<std::string> &strList);
    void addString(const std::string &key, const std::string &value);
    void removeAttributeOfName(const std::string &key);
    void removeObjectWithAttribute(const std::string &key, const std::string &value);
    std::shared_ptr<data_t> getData() const;
    ~JsonData();
    JsonData &operator <<(JsonData &data);

    static data_t * getNewData(data_type type, const std::string &key, const std::string &value);
    static data_t * getNewData(data_type type, const std::string &key, void *value);
    static data_t *getNewListofString(const std::string &key, std::vector<std::string> &strList);

    protected:
    private:
    std::shared_ptr<data_t> _data;
    std::shared_ptr<data_t> _subData;
    std::string _filepath;
    bool _delete;
};

#endif //BOMBERMAN_JSONDATA_HPP
