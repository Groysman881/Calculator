#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<iostream>
#include"stack.h"
#include"queue.h"
#include"tree.h"

class Calculator
{
public:
    Calculator();
    void getPostfix(char* expr);
    void getAST();
    int calculate(tNode* root);
    tNode* get_tree_root();
private:
    int getPriority(char* _operator);
    bool isOperator(char* token);
    int toInt(char* token);
    Stack* _stack;
    Queue* _queue;
    Tree* _tree;

};

#endif // CALCULATOR_H
