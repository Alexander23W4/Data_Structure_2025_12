// AVL树
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

template <class T>
class AVLNode{
public:
    T data;
    AVLNode<T> *left;
    AVLNode<T> *right;
    AVLNode(T value){
        data = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
}

template <class T>
class AVLTree{
protected:
    AVLNode<T> *root;
    int blance_factor;
public:
    AVLTree(){
        root = NULL;
        blance_factor = 0;
    }
    AVLNode<T>* rightRotate(){
        AVLNode<T> *temp = root->left->right;
        AVLNode<T> *newRoot = root->left;
        root->left = temp;
        newRoot->right = root;
        root = newRoot;
        root->right->height = max(height(root->right->left), height(root->right->right)) + 1;
        root->height = max(height(root->left), height(root->right)) + 1
        return root;
    }
    AVLNode<T>* leftRotate(){
        AVLNode<T> *temp = root->right->left;
        AVLNode<T> *newRoot = root->right;
        root->right = temp;
        newRoot->left = root;
        root = newRoot;
        root->left->height = max(height(root->left->left), height(root->left->right)) + 1;
        root->height = max(height(root->left), height(root->right)) + 1
        return root;
    }
    void Insert(T value){
        // 先插入
        AVLNode<T> *newNode = new AVLNode<T>(value);
        AVLNode<T> *temp = root;
        while(temp){
            if(value < temp->data){
                if(temp->left == NULL){
                    temp->left = newNode;
                    break;
                }else{
                    temp = temp->left;
                }
            }
            else{
                if(temp->right == NULL){
                    temp->right = newNode;
                    break;
                }else{
                    temp = temp->right;
                }
            }
        }
        // 更新blance_factor
        if(value < root->data){
            blance_factor--;
        }
        else{
            blance_factor++;
        }
        // 进行旋转
        if(blance_factor > 2){
            leftRotate();
        }
        else if(blance_factor < -2){
            rightRotate();
        }
    }
}
