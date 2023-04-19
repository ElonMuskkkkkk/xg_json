#include "../inc/json_item.h"
#include <iostream>


void test1()
{
    JsonItem j1("hello world");
    JsonItem j2(12.3);
    double n1 = j2;
    std::string s = j1;
    std::cout << n1 << "  " << s << std::endl;
}

void test2()
{
    JsonItem j1;
    j1[0] = 1;
    j1[1] = true;
    j1[2] = "hello world";
    j1.add("%%%%");
    std::cout << j1.str() << std::endl;
}

void test3()
{
    JsonItem j1;
    JsonItem j2;
    JsonItem j3;
    j2[0] = 134;
    j2[1] = "hello";
    j2[2] = false;
    j3["name"] = "Bob";
    j3["sex"] = true;
    j3["age"] = 12;
    j2[3] = j3;
    j1["name"] = "Bob";
    j1["sex"] = true;
    j1["age"] = 12;
    j1["arr"] = j2;
    j1["dict"] = j3;
    j1["apple"] = j3;
    std::cout << j1.str() << std::endl;
}

void test4()
{
    JsonItem js1;
    JsonItem js2;
    JsonItem js3;
    JsonItem js4;
    JsonItem js5;
    js1.parse("-123.1");
    js2.parse("true");
    js3.parse("null");
    js4.parse("[1,true,\"hello\",null]");
    js5.parse("{\"name\":\"mmm\",\"sex\":true,\"age\":12,\"ddd\":null}");
    std::cout << js1.str() << std::endl;
    std::cout << js2.str() << std::endl;
    std::cout << js3.str() << std::endl;
    std::cout << js4.str() << std::endl;
    std::cout << js5.str() << std::endl;
}

int main()
{
    //test2();
    //test3();
    test4();
}