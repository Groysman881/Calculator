#include<iostream>
#include<cstring>
#include "calculator.h"
#include"tree.h"
#include<cmath>

Calculator::Calculator()
{
    std::cout<<"Constructor"<<std::endl;
    _stack = new Stack;
    _queue = new Queue;
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
            //std::cout<<"2"<<std::endl;
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
    //std::cout<<"Check"<<std::endl;
    int i = 0;
    bool prev_token = false;
    bool minus = false;
    while(expr[i] != '\0'){
        //std::cout<<"Check1"<<std::endl;
        char* op = new char;

        sprintf(op,"%c",expr[i]);

        //std::cout<<op<<std::endl;

        if(isOperator(op)){
            switch(getPriority(op)){
            case 0:
                 _stack->push(op);
                 prev_token = false;
                 break;
            case 1:
                while(strcmp(_stack->get_top(),"(") != 0){
                    char* token = new char;
                    std::cout<<_stack->get_top()<<std::endl;
                    strcat(token,_stack->pop());
                    _queue->push(token);
                }
                _stack->pop();
                prev_token = true;
                break;
            case 2:

               // prev_token = false;
               // break;
                //std::cout<<"Check case 2"<<std::endl;
                if(strcmp(op,"-") == 0 && !prev_token){
                   // std::cout<<"Case"<<std::endl;
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
                //prev_token = false;


               /* if(getPriority(_stack->get_top()) <= 2 ){
                    _stack->push(op);
                }
                else{
                    _queue->push(op);
                }*/

            case 3:

                //std::cout<<_stack->get_top()<<std::endl;
                if(_stack->get_size() == 0){
                    _stack->push(op);
                }
                else if(getPriority(_stack->get_top()) < 3){
                    _stack->push(op);
                }
               // else if(getPriority(_stack->get_top()) >= 3)
                else{
                   // std::cout<<"AAAAAAAAAAA"<<std::endl;
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
            //std::cout<<"Last token = "<< expr[i]<<std::endl;
        }
        else if(strcmp(op," ") != 0){
            //std::cout<<"Check2"<<std::endl;
            //std::cout<<expr[i]<<std::endl;
            prev_token = true;
            char* token = new char;
            token[0] = '\0';
            char* buf = new char;
            buf[0] = '\0';
            sprintf(buf,"%c",expr[i]);
            //std::cout<<buf<<std::endl;

            while( !isOperator(buf) && strcmp(buf," ") != 0 && expr[i] != '\0'){
                //std::cout<<"Check3"<<std::endl;
                strcat(token,buf);
                //std::cout<<token<<std::endl;
                i++;
                //std::cout<<expr[i]<<std::endl;
                sprintf(buf,"%c",expr[i]);
                //std::cout<<buf<<std::endl;
            }
            //std::cout<<"Exit"<<std::endl;
            _queue->push(token);
            if(minus){
                _queue->push("-");
                minus = true;
            }
            //std::cout<<"Push"<<std::endl;
            //std::cout<<_queue->get_head()<<std::endl;
        }
        else {
            i++;
        }


       // std::cout<< "expr[i] = "<< expr[i] <<std::endl;

    }
    //std::cout<<_stack->get_size()<<std::endl;
    //std::cout<<_stack->get_top()<<std::endl;
    while(_stack->get_size() > 0){
        //std::cout<<"!!!"<<std::endl;
        _queue->push(_stack->pop());
    }
    /*char** mas = new char*;
    std::cout<<"!?!"<<std::endl;
    int size = _queue->get_size();
    for(int i = 0;i < size;i++){

        mas[i] = _queue->get_head();
        std::cout<<mas[i];
        _queue->pop();

    }*/
}
void Calculator::getAST(){
    Stack* stack_num = new Stack;
    Stack* stack_op = new Stack;
    tNode** mas_Node = new tNode*[_queue->get_size()];
    for(int i = 0;i < _queue->get_size();i++){
        mas_Node[i] = new tNode;
    }
    //std::cout<<"End"<<std::endl;
    int size = 0;
    int root_num;
    int q_size = _queue->get_size();
   // std::cout<<q_size<<std::endl;


    while(size < q_size){
        if(_queue->get_size() > 0){
            if(!isOperator(_queue->get_head())){
              //  std::cout<<"Check1"<<std::endl;
                stack_num->push(_queue->get_head());
                //_queue->pop();
            }
            else{
               // std::cout<<"Check2"<<std::endl;
                stack_op->push(_queue->get_head());
            }
            _queue->pop();
        }
        if(stack_num->get_size() >= 2 && stack_op->get_size() >= 1){
          //  std::cout<<"Check3"<<std::endl;
            strcat(mas_Node[size]->token,stack_op->get_top());
            stack_op->set_top_num_mas(size);
            bool prev = false;
            for(int i = 0;i < 2;i++){
               // std::cout<<"Check4"<<std::endl;
                if(stack_op->get_size() == 1 && _queue->get_size() == 0){
                  //  std::cout<<"Set root"<<std::endl;
                    root_num = stack_op->get_top_num_mas();
                  //  std::cout<<root_num<<std::endl;
                }
                if(!isOperator(stack_num->get_top())){
                 //   std::cout<<"!isOperator"<<std::endl;
                    size++;
                    if(i == 0){
                 //   std::cout<<"size = "<<size<<std::endl;
                    mas_Node[size - 1]->right = mas_Node[size];
                    strcat(mas_Node[size]->token,stack_num->get_top());
                    mas_Node[size]->parent = mas_Node[size - 1];
                    }
                    else if(!prev){

                  //      std::cout<<"size = "<<size<<std::endl;
                        mas_Node[size - 1]->left = mas_Node[size];
                        strcat(mas_Node[size]->token,stack_num->get_top());
                        mas_Node[size]->parent = mas_Node[size - 1];
                    }
                    else{
                   //     std::cout<<"size = "<<size<<std::endl;
                        mas_Node[size - 2]->left = mas_Node[size];
                        strcat(mas_Node[size]->token,stack_num->get_top());
                        mas_Node[size]->parent = mas_Node[size - 2];
                    }
                    prev = true;
                }
                else{
                 //   std::cout<<"isOperator"<<std::endl;
                    if(i == 0){
                        mas_Node[size]->right = mas_Node[stack_num->get_top_num_mas()];
                        mas_Node[stack_num->get_top_num_mas()]->parent = mas_Node[size];

                    }
                    else if(prev){
                        mas_Node[size - 1]->left = mas_Node[stack_num->get_top_num_mas()];

                   //     std::cout<<stack_num->get_top()<<std::endl;
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
           // std::cout<<"Num in mas of Nodes ="<<stack_num->get_top_num_mas()<<std::endl;
            size++;
           // std::cout<<"Check bounds"<<std::endl;
        }
    }
  //  std::cout<<"Exit"<<std::endl;
    _tree->set_root(mas_Node[root_num]);
   // std::cout<<_tree->get_root()->token<<std::endl;

}

int Calculator::calculate(tNode* root){
   // std::cout<<"Calculate"<<std::endl;
    //if(root->isNumber()){
     //   std::cout<<"Check123"<<std::endl;
      //  return toInt(root->token);
   // }
   // std::cout<<"!!!"<<std::endl;
   // std::cout<<root->token<<std::endl;
    if(root->isNumber()){
        return toInt(root->token);
    }
    if(root->left->isNumber() && root->right->isNumber()){
     //   std::cout<<"Check"<<std::endl;
        char* value = new char;
        if(strcmp(root->token,"+") == 0){
      //      std::cout<<"Check1"<<std::endl;
            int k = toInt(root->left->token) + toInt(root->right->token);
     //       std::cout<<toInt(root->left->token)<<std::endl;

       //     std::cout<<k<<std::endl;
            sprintf(value,"%d",k);
            strcpy(root->token,value);
        //    std::cout<<toInt(root->token)<<std::endl;
            root->left = NULL;
            root->right = NULL;
           // std::cout<<root->token<<std::endl;
        }
        else if(strcmp(root->token,"-") == 0){
         //   std::cout<<"Check1"<<std::endl;
            int k = toInt(root->left->token) - toInt(root->right->token);
        //    std::cout<<toInt(root->left->token)<<std::endl;
        //    std::cout<<k<<std::endl;
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
           // std::cout<<root->token<<std::endl;
        }

        else if(strcmp(root->token,"*") == 0){
        //    std::cout<<"Check1"<<std::endl;
            int k = toInt(root->left->token) * toInt(root->right->token);
       //     std::cout<<toInt(root->left->token)<<std::endl;
      //      std::cout<<k<<std::endl;
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
           // std::cout<<root->token<<std::endl;
        }
        else if(strcmp(root->token,"/") == 0){
       //     std::cout<<"Check1"<<std::endl;
            int k = toInt(root->left->token) / toInt(root->right->token);
       //     std::cout<<toInt(root->left->token)<<std::endl;
       //     std::cout<<k<<std::endl;
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
           // std::cout<<root->token<<std::endl;
        }
        else if(strcmp(root->token,"^") == 0){
       //     std::cout<<"Check1"<<std::endl;
            int k = pow(toInt(root->left->token),toInt(root->right->token));
      //      std::cout<<toInt(root->left->token)<<std::endl;
      //      std::cout<<k<<std::endl;
            sprintf(value,"%d",k);
            strcpy(root->token,value);
            root->left = NULL;
            root->right = NULL;
           // std::cout<<root->token<<std::endl;
        }
        if(root->parent == NULL){
            calculate(root);
        }
        else{
            calculate(root->parent);
        }
    }
    else if(!root->left->isNumber()){
      //  std::cout<<"Check1"<<std::endl;
        calculate(root->left);
    }
    else if(!root->right->isNumber()){
      //  std::cout<<"Check2"<<std::endl;
        calculate(root->right);
    }
}
tNode* Calculator::get_tree_root(){
    return _tree->get_root();
}
