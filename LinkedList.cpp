// 单链表 循环链表  双向链表

// 单链表:
// 实现功能: 增: 前插入 中间插入和 后插入
//         删: 删除指定节点
//         查: 查找指定节点
//         改: 修改指定节点的值
//         遍历: 从头到尾遍历链表

#include <iostream>
#include <stdlib.h>
using namespace std;

// 单链表node
template<class T>
class Node{
public:
    T data;
    Node<T>* next;
}

template<class T>
class singlyLinkedList{
protected:
    Node<T>* head;
public:
    singlyLinkedList(){
        head->next = nullptr;
    }
    singlyLinkedList(const singlyLinkedList<T>& L); // 拷贝构造函数
    ~singlyLinkedList(){
        Node<T>* p;
        Node<T>* q;
        p = head;
        while(p->next){
            q = p->next;
            delete p;
            p = q;
        }
        delete p;
    }
    void add_head_node(T data){
        Node<T>* p = new Node<T>;
        p->data = data;
        p->next = head;
        head = p;
    }
    void add_rear_node(T data){
        Node<T>* p = new Node<T>;
        Node<T>* i = head;
        p->data = data;
        while(i->next){
            i = i->next
        }
        i->next = p;
    }
    T delete_node(T data){
        Node<T>* i = head;
        T temp;
        while(i->data == data){
            i = i->next;
        }
        T = i->data;
        delete i;
        return T;
    }
    void scan(){
        Node<T>* i = head;
        while(i->next){
            cout << i->data << " ";
        }
    }

}

template<class T>
class circularLinkedList{
protected:
    Node<T>* head;
public:
    circularLinkedList(){
        head = new Node<T>;
        head->next = head;
    }
    ~circularLinkedList(){
        Node<T>* p = head->next;
        Node<T>* q;
        while(p->next != head){
            q = p->next;
            delete p;
            p = q;
        }
        delete p->next;
    }
    circularLinkedList(const circularLinkedList<T>& L);

    void add_rear_node(T data){
        Node<T>* p = head->next;
        Node<T>* q = new Node<T>;
        while(p->next != head){
            p = p->next;
        }
        q->data = data;
        p->next = head;
        p->next = q;
    }
}

template<class T>
class biNode{
public:
    T data;
    biNode* next;
    biNode* past;

}

template<class T>    // attention to the additional "class" key word
class bidirectionalLinkedList{
protected:
    biNode<T>* head;
public:
    bidirectionalLinkedList(){
        head = new biNode<T>;
        head->next = nullptr;
        head->past = nullptr;
    }
    add_node(T data){
        biNode<T>* p = new biNode<T>;
        biNode<T>* i;
        i = head->past;
        p->data = data;
        p->next = head;
        p->past = i;
        head->past = p;
        i->next = p;
    }
    
}