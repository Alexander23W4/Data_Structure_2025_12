// 使用Queue 实现 Pascal's Triangle
#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

// 顺序表形式:
template<class T>
class Queue{
protected:
    T* queuearray;
    int front, rear;
    int maxsize;
private:
    void expand(int amount){
        T* newarray = new T[this->maxsize + amount];
        for(int i = front%this->maxsize; i < this->maxsize; i++){
            newarray[i - front%this->maxsize] = this->queuearray[i];
        }
        for(int i = 0; i < rear%this->maxsize; i++){
            newarray[i + this->maxsize - front%this->maxsize] = this->queuearray[i];
        }
        delate{} this->queuearray;
        this->queuearray = newarray;
        this->rear = (this->rear - this->front + this->maxsize) % this->maxsize;
        this->front = 0;
        this->maxsize += amount;
    }
public:
    Queue(int maxsize = 20){
        this->maxsize = maxsize;
        this->queuearray = new T[maxsize];
        this->front = 0;
        this->rear = 0;
    }
    ~Queue(){
        delete[] this->queuearray;
    }
    Queue(const Queue<T>& q){
        this->maxsize = q.maxsize;
        this->front = q.front;
        this->rear = q.rear;
        this->queuearray = new T[this->maxsize];
        for(int i = 0; i < this->maxsize; i++){
            this->queuearray[i] = q.queuearray[i];
        }
    }
    bool isEmpty(){
        return this->front == this->rear;
    }
    bool isFull(){
        return this->rear%this->maxsize == this->front%this->maxsize -1;
    }
    T getFront(){
        assert(!isEmpty());
        return this->queuearray[this->front%this->maxsize];
    }
    void enQueue(T data){
        assert(!isFull());
        this->queuearray[this->rear%this->maxsize];
        this->rear++;
    }
    T deQueue(){
        assert(!isEmpty());
        T temp = this->queuearray[this->front%this->maxsize];
        this->front++;
        return temp;
    }
    int getSize(){
        return (this->rear - this->front + this->maxsize) % this->maxsize;
    }

}
// 辅助用的链表:
template<class T>
class LinkNode{
protected:
    T data;
    LinkNode<T>* next;
public:
    LinkNode(T data, LinkNode<T>* next = nullptr){
        this->data = data;
        this->next = next;
    }
    ~LinkNode(){
        delete this->next;
    }
    T getData(){
        return this->data;
    }
    void setData(T data){
        this->data = data;
    }
    LinkNode<T>* getNext(){
        return this->next;
    }
    void setNext(LinkNode<T>* next){
        this->next = next;
    }
}

// TestBench
#define PASCAL_ROW 100

void Psacal_Test(){
    Queue<int> q(PASCAL_ROW+10);
    Queue<int> temp(PASCAL_ROW+10);
    LinkNode<int>* head = new LinkNode<int>(1);
    LinkNode<int>* p = head;
    LinkNode<int>* newp = new LinkNode<int>(1);
    p->next = newp;
    p = newp;
    q.enQueue(1);
    q.enQueue(1);
    for(i=3; i <= PASCAL_ROW; i++){
        for (size_t j = 0; j < i; j++)
        {
            if(j == 0){
                q.enQueue(1);
                LinkNode<int>* temp = new LinkNode<int>(1);
                p->next = temp;
                p = temp;
            }
            else if(j == i - 1){
                q.enQueue(1);
                LinkNode<int>* temp = new LinkNode<int>(q.deQueue());
                p->next = temp;
                p = temp;
            }
            else{
                int num = q.deQueue();
                q.enQueue(num + q.getFront());
                LinkNode<int>* temp = new LinkNode<int>(num + q.getFront());
                p->next = temp;
                p = temp;
            }
        }
        
    }
}