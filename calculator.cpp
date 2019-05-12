#include<iostream>
#include<cstring>
#include "calculator.h"
#include"tree.h"
#include<cmath>

Calculator::Calculator()
{
    _stack = new Stack;
    _queue = new Queue;
    _tree = new Tree;
}
bool Calculator::isOperator(char *token){
    char* op_arr[7] = {"+" , "-" , "/" , "*" , "^" , "(" , ")"};
    for(int i = 0;i < 7;i++){
        if(strcmp(token,op_arr[i]) == 0){
            return true;
        }
    }
    return false;
}
int Calculator::getPriority(char* _operator){
    if(strcmp(_operator,"(") == 0){
        return 0;
    }
    if(strcmp(_operator,")") == 0){
        return 1;
    }
    if(strcmp(_operator,"/") == 0 || strcmp(_operator,"*") == 0){
        return 3;
    }
    if(strcmp(_operator,"^") == 0){
        return 4;
    }
    if(strcmp(_operator , "+") == 0  || strcmp(_operator, "-") == 0){
        return 2;
    }
}
int Calculator::toInt(char *token){
    int i_token = 0;
    for(int i = 0;i < strlen(token);i++){
        if(token[i] == '0'){
            i_token += 0;
        }
        else if(token[i] == '1'){
            i_token += 1 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '2'){
            i_token += 2 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '3'){
            i_token += 3 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '4'){
            i_token += 4 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '5'){
            i_token += 5 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '6'){
            i_token += 6 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '7'){
            i_token += 7 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '8'){
            i_token += 8 * pow(10,strlen(token) - 1 - i);
        }
        else if(token[i] == '9'){
            i_token += 9 * pow(10,strlen(token) - 1 - i);
        }
    }
    if(token[0] == '-'){
        i_token *= -1;
    }
    return i_token;
}
void Calculator::getPostfix(char *expr){
    int i = 0;
    bool prev_token = false;
    bool minus = false;
    while(expr[i] != '\0'){
        char* op = new char;
        sprintf(op,"%c",expr[i]);
        if(isOperator(op)){
            switch(getPriority(op)){
            case 0:
                 _stack->push(op);
                 prev_token = false;
                 break;
            case 1:
                while(strcmp(_stack->get_top(),"(") != 0){
                    char* token = new char;
                    strcat(token,_stack->pop());
                    _queue->push(token);
                }
                _stack->pop();
                prev_token = true;
                break;
            case 2:            
                if(strcmp(op,"-") == 0 && !prev_token){
                    _queue->push("0");
                    prev_token = true;
                    minus = true;
                }
                else if(getPriority(_stack->get_top()) <= 2){
                    _stack->push(op);
                }
                else{
                    _queue->push(_stack->pop());
                    _stack->push(op);
                }
                prev_token = false;
                break;
            case 3:
                if(_stack->get_size() == 0){
                    _stack->push(op);
                }
                else if(getPriority(_stack->get_top()) < 3){
                    _stack->push(op);
                }
                else{
                    _queue->push(_stack->pop());
                    _stack->push(op);
                }
                prev_token = false;
                break;
            case 4:
                _stack->push(op);
                prev_token = false;
                break;
            }
            i++;
        }
        else if(strcmp(op," ") != 0){
            prev_token = true;
            char* token = new char;
            token[0] = '\0';
            char* buf = new char;
            buf[0] = '\0';
            sprintf(buf,"%c",expr[i]);
            while( !isOperator(buf) && strcmp(buf," ") != 0 && expr[i] != '\0'){
                strcat(token,buf);
                i++;
                sprintf(buf,"%c",expr[i]);
            }
            for(int i = 0;i < strlen(token);i++){
                if((int)token[i] < 48 || (int)token[i] > 57){
                    std::cout<<"Incorrect enter of expression!"<<std::endl;
                    exit(0);
                }
            }
            _queue->push(token);
            if(minus){
                _queue->push("-");
                minus = true;
            }
        }
        else {
            i++;
        }
    }
    while(_stack->get_size() > 0){      
        _queue->push(_stack->pop());
    }
}
void Calculator::getAST(){
    Stack* stack_num = new Stack;
    Stack* stack_op = new Stack;
    tNode** mas_Node = new tNode*[_queue->get_size()];
    for(int i = 0;i < _queue->get_size();i++){
        mas_Node[i] = new tNode;
    }
    int size = 0;
    int root_num;
    int q_size = _queue->get_size();
    while(size < q_size){
        if(_queue->get_size() > 0){
            if(!isOperator(_queue->get_head())){
                stack_num->push(_queue->get_head());
            }
            else{
                stack_op->push(_queue->get_head());
            }
            _queue->pop();
        }
        if(stack_num->get_size() >= 2 && stack_op->get_size() >= 1){
            strcat(mas_Node[size]->token,stack_op->get_top());
            stack_op->set_top_num_mas(size);
            bool prev = false;
            for(int i = 0;i < 2;i++){
                if(stack_op->get_size() == 1 && _queue->get_size() == 0){
                    root_num = stack_op->get_top_num_mas();
                }
                if(!isOperator(stack_num->get_top())){
                    size++;
                    if(i == 0){
                    mas_Node[size - 1]->right = mas_Node[size];
                    strcat(mas_Node[size]->token,stack_num->get_top());
                    mas_Node[size]->parent = mas_Node[size - 1];
                    }
                    else if(!prev){
                        mas_Node[size - 1]->left = mas_Node[size];
                        strcat(mas_Node[size]->token,stack_num->get_top());
                        mas_Node[size]->parent = mas_Node[size - 1];
                    }
                    else{
                        mas_Node[size - 2]->left = mas_Node[size];
                        strcat(mas_Node[size]->token,stack_num->get_top());
                        mas_Node[size]->parent = mas_Node[size - 2];
                    }
                    prev = true;
                }
                else{
                    if(i == 0){
                        mas_Node[size]->right = mas_Node[stack_num->get_top_num_mas()];
                        mas_Node[stack_num->get_top_num_mas()]->parent = mas_Node[size];

                    }
                    else if(prev){
                        mas_Node[size - 1]->left = mas_Node[stack_num->get_top_num_mas()];
                        mas_Node[stack_num->get_top_num_mas()]->parent = mas_Node[size - 1];
                    }
                    else{
                        mas_Node[size]->left = mas_Node[stack_num->get_top_num_mas()];
                        mas_Node[stack_num->get_top_num_mas()]->parent = mas_Node[size];
                    }
                    prev = false;
                }
                stack_num->pop();
            }
            stack_num->push(stack_op->get_top());
            stack_num->set_top_num_mas(stack_op->get_top_num_mas());
            stack_op->pop();
            size++;
        }
    }
    _tree->set_root(mas_Node[root_num]);
    delete(stack_op);
    delete(stack_num);
}

int Calculator::calculate(tNode* root){

    if(root->isNumber()){
        int result = toInt(root->token);
        root = NULL;
        return result;
    }
    if(root->left->isNumber() && root->right->isNumber()){
        char* value = new char;
        if(strcmp(root->token,"+") == 0){
            int k = toInt(root->left->token) + toInt(root->right->token);
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
        }
        else if(strcmp(root->token,"-") == 0){
            int k = toInt(root->left->token) - toInt(root->right->token);
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
        }
        else if(strcmp(root->token,"*") == 0){
            int k = toInt(root->left->token) * toInt(root->right->token);
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
        }
        else if(strcmp(root->token,"/") == 0){
            int k = toInt(root->left->token) / toInt(root->right->token);
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
        }
        else if(strcmp(root->token,"^") == 0){     
            int k = pow(toInt(root->left->token),toInt(root->right->token));
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;          
        }
        if(root->parent == NULL){
            calculate(root);
        }
        else{
            calculate(root->parent);
        }
    }
    else if(!root->left->isNumber()){
        calculate(root->left);
    }
    else if(!root->right->isNumber()){
        calculate(root->right);
    }
}
tNode* Calculator::get_tree_root(){
    return _tree->get_root();
}
