#include "../inc/json.h"
#include <iostream>

//测试方法：./test ../.vscode/tasks.json

int main(int argc,char** argvs)
{
    if(argc == 1 || argc > 2){
        std::cout << "error" << std::endl;
        return 0;
    }
    Json js;
    js.load(argvs[1]);
    js.format();
}

