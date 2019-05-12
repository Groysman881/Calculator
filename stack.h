#ifndef STACK_H
#define STACK_H

#include<iostream>

struct Node{
    Node();
    char* token;
    Node* past;
    int num_mas;
};
class Stack
{
public:
    Stack();
    ~Stack();
    void push(char* value);
    char* pop();
    char* get_top();
    int get_size();
    int get_top_num_mas();
    void set_top_num_mas(int num);
private:
    Node* top;
    int size = 0;

};

#endif // STACK_H
