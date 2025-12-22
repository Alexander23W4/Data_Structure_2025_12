#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

// 基于链表的特性, 我设计了这个task flow来练习
/**
 * ->现实需求分析: 首先根据task flow 注重task的前后关系, 而且需要经常变化前后task关系
 * 并且可能需要拆分等特性
 * ->抽象并且选择/设计数据结构: 分析应用特性抽象而选用链表
 * ->分析code层需求与功能/算法: task flow链表 需要具备 模块化, 在特定task的前面或者后面增加插入或删除, 
 * 需要能够拆分, 复制出来部分task flow + 一些链表基本功能
 * 根据上述需求判断选用 双向链表, 每一个task作为一个类
 * 多出来 拆分部分链表, 复制部分链表等 特殊共功能
 * ->综合软硬件分析: 
 * 硬件: 适合小ROM, 不适合高cache miss(总线低ROM访问效率)
 * 软件: 查找时间长, 修改时间短
 */

template<class T>
class Task{
protected:
    string task_name;
    T other_features;
    Task<T>* next_task;
public:
    Task(string task_name, T other_features, Task<T>* next_task){
        this->task_name = task_name;
        this->other_features = other_features;
        this->next_task = next_task;
    }
    ~Task(){
        Task<T>* p = next_task;
        Task<T>* q;
        while(p->next_task){
            q = p->next_task;
            delete p;
            p = q;
        }
        delete p;
        delete this;
    }
    void set_next_task(Task<T>* next_task){
        this->next_task = next_task;
    }
    Task<T>* get_next_task(){
        return this->next_task;
    }
    string get_task_name(){
        return this->task_name;
    }
    void InsertTask(string task_name, Task<T>* new_task){
        Task<T>* p = this;
        while(p->task_name != task_name && p->next_task){
            p = p->next_task;
        }
        Task<T>* q = p->next_task;
        p->next_task = new_task;
        new_task->next_task = q;
    }
    void DeleteTask(string task_name){
        Task<T>* p = this;
        Task<T>* q;
        while(p->next_task && p->next_task->task_name != task_name){
            p = p->next_task;
        }
        if(p->next_task && p->next_task->task_name == task_name){
            q = p->next_task;
            p->next_task = q->next_task;
            delete q;
        }
    }
}


// TestBench

int main(void){
    Task<int> start_task("start", 0, nullptr);
    Task<int> Set_propable_states("set_states", 1, nullptr);
    Task<int> Note_control_variables("note_variables", 1, nullptr);
    Task<int> Design_state_transition_machanism("design_SMT", 10, nullptr);
    Task<int> Implement_sequential_transfer("sequential_transfer", 5, nullptr);
    Task<int> Set_output("set_output", 2, nullptr);
    Task<int> Compile_testbench("compile_testbench", 10, nullptr);
    Task<int> Simulation("simulation", 1, nullptr);
    Task<int> Debug("debug", 10, nullptr);

    Set_propable_states.set_next_task(&Note_control_variables);
    Note_control_variables.set_next_task(&Design_state_transition_machanism);
    Design_state_transition_machanism.set_next_task(&Implement_sequential_transfer);
    Implement_sequential_transfer.set_next_task(&Set_output);
    Set_output.set_next_task(&Compile_testbench);
    Compile_testbench.set_next_task(&Simulation);
    Simulation.set_next_task(&Debug);
    
    start_task.DeleteTask("Compile_testbench");
    
}
