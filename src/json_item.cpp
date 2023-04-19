#include "../inc/json_item.h"

JsonItem::JsonItem():m_type(NONE) {}

JsonItem::JsonItem(double num) : m_type(NUMBER) { m_value.num = num; }

JsonItem::JsonItem(int num) : m_type(NUMBER) { m_value.num = static_cast<double>(num); }

JsonItem::JsonItem(const std::string &str) : m_type(STRING) { m_value.str = new std::string(str); }

JsonItem::JsonItem(const char *str) : m_type(STRING) { m_value.str = new std::string(str); }

JsonItem::JsonItem(bool tof) : m_type(BOOL) { m_value.tof = tof; }

JsonItem::JsonItem(JsonArray *arr) : m_type(ARRAY) { m_value.arr = arr; }

JsonItem::JsonItem(JsonObject *obj) : m_type(OBJECT) { m_value.obj = obj; }

JsonItem::JsonItem(const JsonItem &json) : m_type(json.m_type)
{
    switch (m_type)
    {
    case NUMBER:
        m_value.num = json.m_value.num;
        break;
    case STRING:
        m_value.str = json.m_value.str;
        break;
    case BOOL:
        m_value.tof = json.m_value.tof;
        break;
    case OBJECT:
        m_value.obj = json.m_value.obj;
        break;
    case ARRAY:
        m_value.arr = json.m_value.arr;
        break;
    default:
        break;
    }
}

JsonItem::JsonItem(JsonType type) : m_type(type)
{
    switch (type)
    {
    case STRING:
        m_value.str = new std::string();
        break;
    case ARRAY:
        m_value.arr = new JsonArray;
        break;
    case OBJECT:
        m_value.obj = new JsonObject;
        break;
    default:
        break;
    }
}

JsonItem::~JsonItem(){}

void JsonItem::clear()
{
    switch (m_type)
    {
    case STRING:
        delete m_value.str;
        break;
    case ARRAY:
        for (auto it = m_value.arr->begin(); it != m_value.arr->end(); it++)
        {
            it->clear();
        }
        delete m_value.arr;
        break;
    case OBJECT:
        for (auto it = m_value.obj->begin(); it != m_value.obj->end(); it++)
        {
            it->second.clear();
        }
        delete m_value.obj;
        break;

    default:
        break;
    }
}

JsonItem::operator double()
{
    if(m_type != NUMBER){
        throw std::logic_error("type error, not double");
    }
    return m_value.num;
}
JsonItem::operator std::string()
{
    if(m_type != STRING){
        throw std::logic_error("type error, not string");
    }
    return *(m_value.str);
}
JsonItem::operator JsonObject()
{
    if(m_type != OBJECT){
        throw std::logic_error("type error, not object");
    }
    return *(m_value.obj);
}
JsonItem::operator JsonArray()
{
    if(m_type != ARRAY){
        throw std::logic_error("type error, not array");
    }
    return *(m_value.arr);
}
JsonItem::operator bool()
{
    if(m_type != BOOL){
        throw std::logic_error("type error, not bool");
    }
    return m_value.tof;
}


JsonItem& JsonItem::operator[](int index)
{
    if (index < 0)
    {
        throw std::logic_error("error, index < 0");
    }
    if(m_type != ARRAY){
        m_type = ARRAY;
        m_value.arr = new JsonArray();
    }
    int size = (m_value.arr)->size();
    if(index >= size){
        do{
            (m_value.arr)->push_back(JsonItem());
        } while ((m_value.arr)->size() <= index);
    }
    return (m_value.arr)->at(index);
}

JsonItem& JsonItem::operator[](const char* key)
{
    return (*this)[std::string(key)];
}
JsonItem& JsonItem::operator[](const std::string& key)
{
    if(m_type != OBJECT){
        m_type = OBJECT;
        m_value.obj = new JsonObject();
    }
    if((m_value.obj)->find(key) == (m_value.obj)->end())
    {
        (*m_value.obj)[key] = JsonItem();
    }
    return (*m_value.obj)[key];
}

void JsonItem::add(const JsonItem &json)
{
    if(m_type != ARRAY){
        m_type = ARRAY;
        m_value.arr = new JsonArray();
    }
    (m_value.arr)->push_back(json);
}

std::string JsonItem::str() const
{
    std::stringstream ss;
    switch (m_type)
    {
    case NUMBER:
        ss << m_value.num;
        break;
    case STRING:
        ss << '\"' << *(m_value.str) << '\"';
        break;
    case BOOL:
        if(m_value.tof)
            ss << "true";
        else
            ss << "false";
        break;
    case NONE:
        ss << "null";
        break;
    case ARRAY:
    {
        ss << "[";
        for (auto it = (m_value.arr)->begin(); it != (m_value.arr)->end(); it++){
            if(it != (m_value.arr)->begin()){
                ss << ",";
            }
            ss << it->str();
        }
        ss << "]";
        break;
    }
    case OBJECT:
    {
        ss << "{";
        for (auto it = (m_value.obj)->begin(); it != (m_value.obj)->end(); it++){
            if(it != (m_value.obj)->begin()){
                ss << ",";
            }
            ss << '\"' << it->first << '\"' << ":" << it->second.str();
        }
        ss << "}";
        break;
    }
    default:
        break;
    }
    return ss.str();
}

// std::ostream & operator<< (std::ostream &os,const JsonItem& json)
// {
//     switch (json.m_type)
//     {
//     case JsonItem::JsonType::NUMBER:
//         os << json.m_value.num;
//         break;
//     case JsonItem::JsonType::STRING:
//         os << json.m_value.str;
//         break;
//     case JsonItem::JsonType::BOOL:
//         os << json.m_value.tof;
//         break;
//     case JsonItem::JsonType::ARRAY:
//         os << static_cast<JsonItem::JsonArray>(JsonItem(json));
//         break;
//     case JsonItem::JsonType::OBJECT:
//         os << static_cast<JsonItem::JsonArray>(JsonItem(json));
//         break;
//     }
// }


void JsonItem::operator=(int num)
{
    this->m_type = NUMBER;
    this->m_value.num = static_cast<double>(num);
}
void JsonItem::operator=(double num)
{
    this->m_type = NUMBER;
    this->m_value.num = num;
}
void JsonItem::operator=(bool tof)
{
    this->m_type = BOOL;
    this->m_value.tof = tof;
}
void JsonItem::operator=(const char* str)
{
    this->m_type = STRING;
    this->m_value.str = new std::string(str);
}
void JsonItem::operator=(const std::string& str)
{
    this->m_type = STRING;
    this->m_value.str = new std::string(str);
}
void JsonItem::operator=(const JsonArray& arr)
{
    this->m_type = ARRAY;
    this->m_value.arr = new JsonArray(arr);
}
void JsonItem::operator=(const JsonObject& obj)
{
    this->m_type = OBJECT;
    this->m_value.obj = new JsonObject(obj);

}

void JsonItem::parse(const std::string &str)
{
    JsonParser jp;
    jp.load(str);
    *this = jp.parse();
}