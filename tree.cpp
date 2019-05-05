#include "tree.h"
#include<cstring>

Tree::Tree()
{
    root = new tNode;
}
bool tNode::isNumber(){
    if(left == NULL && right == NULL){
        return true;
    }
    else{
        return false;
    }
}
tNode::tNode(){
    token = new char;
    left = NULL;
    right = NULL;
    parent = NULL;
}
void Tree::set_root(tNode *node){
    root = node;

}
tNode* Tree::get_root(){
    return root;
}
