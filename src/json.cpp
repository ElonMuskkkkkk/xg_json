#include "../inc/json.h"

void Json::load(const std::string& path)
{
    fs.open(path,std::ios::out | std::ios::in);
    if(!fs.is_open()){
        throw std::logic_error("error,open json file");
    }
    item.parse(std::string(iterator(fs), iterator()));
    fs.close();
}

void Json::format()
{
    std::cout << formatJson(item.str()) << std::endl;
}

std::string Json::formatJson(const std::string& json)
{
    std::string result = "";
	int level = 0;
	for (int index = 0; index < json.size(); index++)
	{
		char c = json[index];

		if (level > 0 && '\n' == json[json.size() - 1])
		{
			result += getLevelStr(level);
		}

		switch (c)
		{
		case '{':
		case '[':
			result = result + c + "\n";
			level++;
			result += getLevelStr(level);
			break;
		case ',':
			result = result + c + "\n";
			result += getLevelStr(level);
			break;
		case '}':
		case ']':
			result += "\n";
			level--;
			result += getLevelStr(level);
			result += c;
			break;
		default:
			result += c;
			break;
		}

	}
	return result;
}
std::string Json::getLevelStr(int level)
{
    std::string levelStr = "";
	for (int i = 0; i < level; i++)
	{
		levelStr += "\t"; 
	}
	return levelStr;
}