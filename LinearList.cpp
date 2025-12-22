// 线性表 顺序表  链表:单链表, 双向链表, 循环链表, 静态链表

#include <iostream>
#include <stdlib.h>
using namespace std;
#define DEAULTE_SIZE 100  // 默认顺序表的最大容量

template<class T>   // $ 模板类
class LinearList{
public:
    LinearList();    // 默认构造函数
    ~LinearList();   // 析构函数
    virtual int Size() const = 0;   // $ virtual + (=0), 父类不实现, 子类必须实现
    virtual int Length() const = 0;
    virtual int Search(const T& x) const = 0;
    virtual int Locate(int i) const = 0;
    virtual T* GetData(int i) const = 0;
    virtual bool SetData(int i, const T& x) = 0;
    virtual bool Insert(int i, const T& x) = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual void Sort() = 0;
    virtual void input() = 0;
    virtual void output() const = 0;
    virtual LinearList<T>& operator=(const LinearList<T>& L) = 0;  // 赋值运算符重载
}

template<class T>
class SeqList : public LinearList<T> {  // $ 顺序表类
protected:
    T* data;        // 存储空间
    int maxSize;    // 最大容量
    int length;     // 当前长度
    void Resize(int newSize); // 动态扩展顺序表

public:
    SeqList(int size = DEAULTE_SIZE); // 构造函数
    SeqList(SeqList<T>& L);  // 拷贝构造函数
    ~SeqList(){ delete[] data; }  // 析构函数;

    int Size() const { return maxSize;  } //$ const
    int Length() const { return length + 1; }
    int Search(const T& x) const;
    int Locate(int i) const;  // 返回第i个元素的索引
    T* GetData(int i) const{
        return (i >= 0 && i < length) ? data[i] : NULL;
    }
    void SetData(int i, T& x){
        assert (i >= 0 && i < length);
        data[i] = x;
    }
    bool Insert(int i, const T& x);
    bool IsEmpty() const { return length == 0; }
    bool Remove(int i, T& x);
    bool IsFull() const { return length == maxSize; }
    void input();
    void output() const;
    SeqList<T>& operator=(const SeqList<T>& L);  //$ 赋值运算符重载
    
};

template<class T>
class LinkedList{
protected:
    struct Node{
        T data;
        Node* next;
    }
    Node* head;
public:
    LinkedList();
    ~LinkedList();
    LinkedList(LinkedList<T>& List);

    int Size() const;
    bool IsEmpty() const;

}

LinkedList<T>::Size() const{
    int length = 0;
    Node* p = head->next;
    while(p != NULL){
        length++;
        p = p->next;
    }
}

LinkedList<T>::IsEmpty() const{
    return head->next == NULL;
}
