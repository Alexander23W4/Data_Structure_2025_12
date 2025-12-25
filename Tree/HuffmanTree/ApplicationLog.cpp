#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

template <class T, class D>
class TreeNode{
public:
    T weight;
    D data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T val): data(val), left(NULL), right(NULL) {}
       
}
template <class T, class D>
class KV{
public:
    T key;
    D value;
    KV(T key, D value){
        this->key = key;
        this->value = value;
    }
}

void ApplicationLog(){
    // log数据:
    KV* log = new KV<string, int>[4];
    log[0] = KV("INFO", 30);
    log[1] = KV("ERROR", 2);
    log[2] = KV("WARNING", 6);
    log[3] = KV("DEBUG", 2);
    log[4] = KV("TIME", 40);

    // 构建Huffman Tree:
    TreeNode* nodes = new TreeNode<int, string>[4];
    for (size_t i = 0; i < 5; i++)
    {
        /* code */
        nodes[i].weight = log[i]value;
        nodes[i].data = log[i].key;

    }
    for (size_t i = 5; i >= 1; i--)
    {
        int temp1, temp2;
        temp1 = findmin1(log);
        temp2 = findmin2(log);
    }
    
    
}



