#ifndef QUEUE_H
#define QUEUE_H


struct qNode{
    qNode();
    char* token;
    qNode* next;
};
class Queue
{
public:
    Queue();
    char* pop();
    void push(char* value);
    char* get_head();
    int get_size();
private:
    qNode* head;
    qNode* tail;
    int size;
};

#endif // QUEUE_H
