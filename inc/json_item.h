#ifndef __XG_JSON_ITEM_H_
#define __XG_JSON_ITEM_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <exception>
#include "json_parser.h"

class JsonItem
{
public:
    typedef std::vector<JsonItem> JsonArray;
    typedef std::map<std::string,JsonItem> JsonObject;
    enum JsonType
    {
        NUMBER,
        BOOL,
        STRING,
        NONE,
        ARRAY,
        OBJECT
    };
    union JsonValue
    {
        float num;
        bool tof;
        const std::string* str;
        JsonArray *arr;
        JsonObject *obj;
    };
public:
    JsonItem();
    /// @brief 根据输入，构造类型与值
    JsonItem(double num);
    JsonItem(int num);
    JsonItem(const std::string& str);
    JsonItem(const char* str);
    JsonItem(bool tof);
    JsonItem(JsonArray* arr);
    JsonItem(JsonObject* obj);
    
    JsonItem(const JsonItem& json);
    /// @brief 构造类型 
    JsonItem(JsonType type);

    ~JsonItem();
public:
    /// @brief 获取json对象内容 
    std::string str() const;

    /// @brief 释放内存
    void clear();
    /// friend std::iostream &operator<<(std::iostream &os, const JsonItem &json);
    ///  @brief 重载赋值运算符
    void operator=(int num);
    void operator=(double num);
    void operator=(bool tof);
    void operator=(const std::string& num);
    void operator=(const JsonArray& arr);
    void operator=(const JsonObject& obj);
    void operator=(const char *str);
    /// @brief 数组相关的操作
    JsonItem& operator[](int index);
    JsonItem& operator[](const char* key);
    JsonItem& operator[](const std::string& key);
    void add(const JsonItem &json);

    /// @brief 解析
    void parse(const std::string &str);
    //void load(const std::)

public:
    /// @brief 类型转换
    // operator int();
    operator double();
    operator std::string();
    operator JsonObject();
    operator JsonArray();
    operator bool();

private:
    JsonType m_type;
    JsonValue m_value;
};
#endif