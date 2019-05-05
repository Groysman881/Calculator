#include<iostream>
#include "queue.h"
#include<cstring>

qNode::qNode(){
    token = new char;
}
Queue::Queue()
{
    std::cout<<"Queue"<<std::endl;
    size = 0;
    tail = new qNode;
    head = new qNode;
}
void Queue::push(char *value){
    std::cout<<"Push1"<<std::endl;
    qNode* new_node = new qNode;
    new_node->next = NULL;
    std::cout<<"okes"<<std::endl;
    strcat(new_node->token, value);
    if(size == 0){
        tail = new_node;
        head = new_node;
    }
    else{
        tail->next = new_node;
        tail = new_node;
    }
    size++;
    std::cout<<"Exit push"<<std::endl;

}
char* Queue::pop(){


    char* buf = new char;
    if(size > 0){
        strcat(buf,head->token);
        head = head->next;
        size--;
    }
    else{
        std::cout<<"Error"<<std::endl;
        exit;
    }

    return(buf);
}
char* Queue::get_head(){
    return head->token;
}
int Queue::get_size(){
    return size;
}
