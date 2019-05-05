#ifndef TREE_H
#define TREE_H

struct tNode{
    tNode();
    bool isNumber();
    char* token;
    tNode* parent;
    tNode* left;
    tNode* right;
};
class Tree
{
public:
    Tree();
    void set_root(tNode* node);
    tNode* get_root();
private:
    tNode* root;
};

#endif // TREE_H
