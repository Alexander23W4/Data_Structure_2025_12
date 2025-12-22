#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

/**
 * 栈适合匹配LIFO的机制
 * 生活中 嵌套性质的(括号匹配), 一来一回的(操作系统的函数返回机制), 成双操作的 机制或许能够用到栈
 * 不仅简化操作, 而且更为直观(数据结构的基本功能)
 * 
 * ->现实需求分析: 需要匹配括号, 括号类型是成双的且LIFO
 * ->选用栈
 * ->大致实现方案: 要实现提取括号结构, 和分离多层多项式并依次存储 两个specific的功能
 * 一个栈为一个对象, 栈选用最基本的栈类型, specific功能用额外的两个非类function实现
 * ->硬件方面: 指针一直指向栈顶, 且使用顺序栈, 无cache miss
 * 软件方面: 操作栈顶pop push速度快
 */
template<class T>
class BraceletStack{
protected:
    T* stackarray;
    int top;
    int maxsize;
private:
    void expand(int amount){
        T* newarray = new T[this->maxsize + amount];
        for(int i = 0; i < this->maxsize; i++){
            newarray[i] = this->stackarray[i];
        }
        delete[] this->stackarray;
        this->stackarray = newarray;
        this->maxsize += amount;
    }
public:
    BraceletStack(int maxsize){
        this->maxsize = maxsize;
        this->stackarray = new T[maxsize];
        this->top = -1;
    }
    ~BraceletStack(){
        delete[] stackarray;
    }
    BraceletStack(const BraceletStack<T>& S){
        this->maxsize = S->maxsize;
        T* newarray = new T[maxsize];
        for (size_t i = 0; i < maxsize; i++)
        {
            newarray[i] = S->stackarray[i];
        }
        this->top = S->top;
        delete []this->stackarray;
        this->stackarray = newarray;
    }
    T pop(){
        assert(this->top != -1);
        return this->stackarray[this->top--];
    }
    void push(T data){
        assert(this->top < this->maxsize -1);
        this->stackarray[++this->top] = data;
    }
    T pushMatch(T data){
        if(data = this->stackarray[top]){
            return pop();
        }
        else{
            assert(this->top < this->maxsize -1);
            this->stackarray[++this->top] = data;
            return 0;
        }
    }
    bool isEmpty(){
        return this->top == -1;
    }
    bool isFull(){
        return this->top == this->maxsize -1;
    }
    T checktop(){
        return this->stackarray[top];
    }
}

void Test(){
    BraceletStack<char> S(20);
    string str = "{2'b11[(a+b)*c]+d}";
    for(char ch : str){
        if(ch == '{' || ch == '[' || ch == '('){
            S.push(ch);
        }
        else{
            char temp = S.pushMatch(ch);
            assert(temp != 0);
            cout << "match at" << ch << " with " << temp << endl;
        }
    }
}

void Mega_Test(){
    string* polys = new string[10];
    int polys_index = 0;
    BraceletStack<char> S(20);
    string str = "{2'b11[(a+b)*c]+d}";
    for(char ch : str){
        if(ch == '}' || ch == ']' || ch == ')'){
            BraceletStack<char> temp(20);
            while(S.checktop != '(' && S.checktop != '{' && S.checktop != '['){
                temp.push(S.pop())
            }
            S.pop();
            S.push('X');
            while(!temp.isEmpty()){
                polys[polys_index] += temp.pop();
            }
            polys_index++;
        }
        else{
            S.push(ch);
        }
    }
}
