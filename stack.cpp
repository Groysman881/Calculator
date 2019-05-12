#include<iostream>
#include "stack.h"
#include<cstring>

Node::Node(){
    token = new char;
}
Stack::Stack()
{
    size = 0;
    top = new Node;
}
Stack::~Stack(){
    delete(top);
}
void Stack::push(char *value){
    Node* new_node = new Node;
    new_node->token[0] = '\0';
    strcat(new_node->token,value);
    new_node->past = top;
    top = new_node;
    size++;
}
char* Stack::pop(){
    char* buf = new char;
    Node* buf_node = top;
    strcat(buf,top->token);
    top = top->past;
    size--;
    delete(buf_node);
    return(buf);
}
char* Stack::get_top(){
    return top->token;
}
int Stack::get_size(){
    return size;
}
int Stack::get_top_num_mas(){
    return top->num_mas;
}
void Stack::set_top_num_mas(int num){
    top->num_mas = num;
}
