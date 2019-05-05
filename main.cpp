#include <iostream>
#include"stack.h"
#include"queue.h"
#include"calculator.h"
#include<cstring>
#include<cstdio>
using namespace std;

int main()
{
    Calculator calc;
    cout<<"Enter expression"<<endl;
    char* expr = new char;
    gets(expr);
    cout<<strlen(expr)<<endl;
    for(int i = 0;i < strlen(expr);i++){
        cout<<"expr["<< i <<"] = "<<expr[i]<<endl;
    }
    //cout<<"???"<<endl;
    cout<<expr<<endl;
    calc.getPostfix(expr);
    calc.getAST();
    std::cout<<calc.calculate(calc.get_tree_root())<<std::endl;
    std::cout<<"End"<<std::endl;
    return 0;

}
