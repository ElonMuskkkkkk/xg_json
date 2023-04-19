#ifndef __JSON_PARSER_H_
#define __JSON_PARSER_H_
#include "json_item.h"
class JsonItem;
class JsonParser
{
public:
    JsonParser() : m_idx(0){}
    void load(const std::string &str);
    JsonItem parse();

private:
    void skip_space();
    char getNextToken();
    JsonItem parse_number();
    JsonItem parse_null();
    JsonItem parse_bool();
    std::string parse_string();
    JsonItem parse_array();
    JsonItem parse_object();
    bool isEnd() const { return m_idx >= m_str.size(); }

private:
    std::string m_str;
    int m_idx;
};

#endif