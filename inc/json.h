#ifndef __XG_JSON_H_
#define __XG_JSON_H_

#include <fstream>
#include "json_item.h"

class Json
{
public:
    typedef std::istreambuf_iterator<char> iterator;
    Json() {}
    ~Json() { item.clear(); }

    void load(const std::string &path);
    void format();
    std::string formatJson(const std::string& json);
    std::string getLevelStr(int level);

private:
    JsonItem item;
    std::fstream fs;

};

#endif