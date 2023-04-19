#include "../inc/json_parser.h"

void JsonParser::load(const std::string &str)
{
    m_str = str;
}

void JsonParser::skip_space()
{
    while(m_str[m_idx] == ' ' 
            || m_str[m_idx] == '\r'
            || m_str[m_idx] == '\n'
            || m_str[m_idx] == '\t')
    {
        m_idx++;
    }
}

char JsonParser::getNextToken()
{
    skip_space();
    return m_str[m_idx++];
}

JsonItem JsonParser::parse()
{
    char ch = getNextToken();
    switch(ch){
    case 'n':
        return parse_null();
    case 't':
    case 'f':
        return parse_bool();
    case '{':
        return parse_object();
    case '[':
        return parse_array();
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return parse_number();
    case '\"':
        return parse_string();
    default :
        break;
    }
    throw std::logic_error("error json str");
}

JsonItem JsonParser::parse_number()
{
    int pos = m_idx-1;
    while(!isEnd() && m_str[m_idx] >= '0' && m_str[m_idx] <= '9')
    {
        m_idx++;
    }
    if(m_str[m_idx] == '.')
    {
        m_idx++;
    }
    while(!isEnd() && m_str[m_idx] >= '0' && m_str[m_idx] <= '9')
    {
        m_idx++;
    }

    return std::atof(m_str.substr(pos, m_idx - pos).c_str());
    //throw std::logic_error("error number");
}

JsonItem JsonParser::parse_null()
{
    if(m_str.compare(m_idx,3,"ull") == 0)
    {
        m_idx += 3;
        return JsonItem();
    }
    throw std::logic_error("parse error, null");
}

JsonItem JsonParser::parse_bool()
{
    if(m_str.compare(m_idx,3,"rue") == 0)
    {
        m_idx += 3;
        return JsonItem(true);
    }
    if(m_str.compare(m_idx,4,"alse") == 0)
    {
        m_idx += 4;
        return JsonItem(true);
    }
    throw std::logic_error("parse error, bool");
}

std::string JsonParser::parse_string()
{
    int pos = m_idx - 1;
    std::string out;
    while (!isEnd() && m_str[m_idx] != '\"')
    {
        if(m_str[m_idx] == '\\'){
            m_idx++;
            switch (m_str[m_idx])
            {
            case '\\':
                out += "\\\\";
                break;
            case 't':
                out += '\t';
                break;
            case 'n':
                out += '\n';
                break;
            case 'f':
                out += 'f';
                break;
            case 'u':
                for (int i = 0; i < 4; i++)
                {
                    out += m_str[m_idx++];
                }
            default:
                break;
            }
        }
        else 
            out += m_str[m_idx];
        m_idx++;
    }
    m_idx++;
    return out;
    //throw std::logic_error("error, json string");
}

JsonItem JsonParser::parse_array()
{
    JsonItem arr(JsonItem::JsonType::ARRAY);
    char ch = getNextToken();
    if (ch == ']')
        return arr;
    while(true){
        m_idx--;
        arr.add(parse());
        ch = getNextToken();
        if(ch == ']')
            break;
        if(ch != ',')
            throw std::logic_error("error, json array");
    }
    return arr;
}

JsonItem JsonParser::parse_object()
{
    JsonItem obj(JsonItem::JsonType::OBJECT);
    char ch = getNextToken();
    std::string key;
    std::string value;
    if (ch == '}')
        return obj;
    while(true){
        if(ch != '\"'){
            throw std::logic_error("error, json obj");
        }
        key = parse_string();
        ch = getNextToken();
        if(ch != ':')
            throw std::logic_error("error, json obj");
        obj[key] = parse();
        ch = getNextToken();
        if(ch == '}')
            break;
        if(ch != ',')
            throw std::logic_error("error, json obj");
        ch = getNextToken();
    }
    return obj;
}
