#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

template <class T>
class Stack{
protected:
    T* data;
    int top;
    int capacity;
public:
    Stack(int cap): capacity(cap), top(-1){
        data = new T[capacity];
    }
    ~Stack(){
        delete[] data;
    }
    void push(const T& val){
        assert(top + 1 < capacity);
        data[++top] = val;
    }
    void pop(){
        assert(top != -1);
        --top;
    }
    T& peek(){
        assert(top != -1);
        return data[top];
    }
    bool isEmpty(){
        return top == -1;
    }
}

class TreeNode{
public:
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(NULL), right(NULL) {}
}

class Tree{
protected:
    TreeNode* root;
public:
    Tree(): root(NULL){}
    ~Tree(){
        // Destructor to free memory
        destroyTree(root);
    }
    //Ç°Ðò±éÀú
    void preOrder(TreeNode* node){
        if(node == NULL){
            return;
        }
        cout << node->value << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    void midOrder(TreeNode* node){
        if(!node){
            return;
        }
        midOrder(node->left);
        cout << node->value << " ";
        midOrder(node->right);
    }
    // ·ÇµÝ¹é:
    void Order(TreeNode* node){
        Stack temp = Stack(20);
        TreeNode* p = node
        while(p){
            if(p->right){
                temp.push(node->right);
            }
            if(p->left){
                cout << p->value << " ";
                p = p->left;
            }
            else{
                p = temp.pop();
            }
        }
    }
}

void preCopy(TreeNode* node, TreeNode* copy){
    if(!node){
        return;
    }
    copy->value = node->value;
    copy->left = new TreeNode;
    preCopy(node->left, copy->left);
    copy->right = new TreeNode;
    preCopy(node->right, copy->right);
}

