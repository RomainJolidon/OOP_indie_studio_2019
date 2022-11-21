/*
** EPITECH PROJECT, 2023
** bomberman
** File description:
** Created by rjolidon,
*/

#include <iostream>
#include <utility>
#include "config/JsonData.hpp"

JsonData::JsonData(data_t *data, std::string filepath, bool needDelete):
_data(data), _subData(nullptr), _filepath(std::move(filepath)), _delete(needDelete)
{
    _subData = _data;
}

JsonData::~JsonData()
{
    if (_delete) {
        //delete_json_object(_data.get());
    }
}

void JsonData::writeData()
{
    write_json_object(_data.get(), _filepath.c_str());
}


std::string JsonData::getAttributeOfKey(const std::string &key) const
{
    return std::string(get_attribute_of_key(_subData.get(), key.c_str()));
}

data_t * JsonData::getObjectWithAttribute(const std::string &key, const std::string &value) const
{
    data_t *result = get_object_with_attribute(_subData.get(), key.c_str(), value.c_str());

    if (!result)
        return nullptr;
    return result;
}

data_t * JsonData::getListOfKey(const std::string &key) const
{
    data_t *result = get_list_of_key(_data.get(), key.c_str());

    if (!result)
        return (nullptr);
    return result;
}

void JsonData::addObject(const std::string &key, int nbArgs, ...)
{
    data_t *obj = getNewData(OBJECT, key, init_list());
    va_list va;

    if (!obj)
        return;
    va_start(va, nbArgs);
    for (int i = 0; i < nbArgs; i++) {
        add_elem(static_cast<list_t *>(obj->value), va_arg(va, void *));
    }

    va_end(va);
    add_elem(static_cast<list_t *>(_subData->value), obj);
}

void JsonData::addList(const std::string &key, int nbArgs, ...)
{
    data_t *obj = create_data(TAB, key.c_str(), init_list());
    va_list va;

    if (!obj)
        return;
    va_start(va, nbArgs);
    for (int i = 0; i < nbArgs; i++)
        add_elem(static_cast<list_t *>(obj->value), va_arg(va, void *));
    va_end(va);
    add_elem(static_cast<list_t *>(_subData->value), obj);
}

data_t * JsonData::getNewData(data_type type,
    const std::string &key, void *value)
{
    return (create_data(type, key.c_str(), value));
}

data_t * JsonData::getNewData(data_type type,
    const std::string &key, const std::string &value
)
{
    char *newValue = strdup(value.c_str());
    return (create_data(type, key.c_str(), newValue));
}

void JsonData::addListofString(const std::string &key,
    std::vector<std::string> &strList
)
{
    data_t *obj = create_data(TAB, key.c_str(), init_list());

    if (!obj)
        return;
    for (auto &it: strList) {
        add_elem(static_cast<list_t *>(obj->value), getNewData(STRING, "", strdup(it.c_str())));
    }
    add_elem(static_cast<list_t *>(_subData->value), obj);
}

void JsonData::addString(const std::string &key, const std::string &value)
{
    char *newValue = strdup(value.c_str());
    add_elem(static_cast<list_t *>(_subData->value), getNewData(STRING, key, newValue));
}

data_t *JsonData::getNewListofString(const std::string &key,
    std::vector<std::string> &strList)
{
    data_t *obj = create_data(TAB, key.c_str(), init_list());

    if (!obj)
        return nullptr;
    for (auto &it: strList) {
        add_elem(static_cast<list_t *>(obj->value), getNewData(STRING, "", strdup(it.c_str())));
    }
    return (obj);
}

void JsonData::removeAttributeOfName(const std::string &key)
{
    for (int i = 0; i < static_cast<list_t *>(_subData->value)->size; i++) {
        if (static_cast<data_t *>(get_data_at_pos(static_cast<list_t *>(_subData->value), i))->key == key) {
            delete_elem_at_pos(static_cast<list_t *>(_subData->value), i);
            break;
        }
    }
}

void JsonData::goToObjectWithAttribute(const std::string &key,
    const std::string &value
)
{
    data_t *result = get_object_with_attribute(_data.get(), key.c_str(), value.c_str());

    if (!result)
        return;
    _subData = std::shared_ptr<data_t>(result);
}

void JsonData::goToRootData()
{
    _subData = _data;
}

void JsonData::removeObjectWithAttribute(const std::string &key,
    const std::string &value
)
{
    for (int i = 0; i < static_cast<list_t *>(_subData->value)->size; i++) {
        if (get_attribute_of_key(static_cast<data_t *>(get_data_at_pos(
            static_cast<list_t *>(_subData->value), i)), key.c_str()) == value) {
            delete_elem_at_pos(static_cast<list_t *>(_subData->value), i);
            break;
        }
    }
}

std::shared_ptr<data_t> JsonData::getData() const
{
    return _subData;
}

JsonData &JsonData::operator<<(JsonData &data)
{
    add_elem(static_cast<list_t *>(_subData->value), data._data.get());
    return *this;
}

