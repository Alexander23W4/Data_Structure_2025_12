/*
应用背景（真实世界）
你在做一个 在线系统监控模块，比如：
Web server 实时统计 访问最频繁的 IP
API Gateway 统计 调用次数最高的 endpoint
日志系统统计 最常见 error code

特点
数据是 流式的（infinite stream）
不能全存
不能全排序
你随时要：
“给我当前最活跃的 K 个事件”
*/

// 应用流: 什么情况下用, 怎么快速抓到工具和情况的接口, 快速接入
/*
Heap Application 应用流: 最优体现形式, 作为heap的关键码
数据实时更新: 
部分更新: data[size]插入, shiftup
全部更新: 插一个, shiftup一次

取最优:
直接取, remove, 然后移动 + shiftdown

总结: Application Heap是一个特定形式排列的关键码数组, 每次操作后, 通过算法维持排列形式
维持排列形式的目的是, 方便下次排列 + 稳定取得头部最优

*/

template <class T, class Compare>
class MinHeap{
protected:
    T* data;
    int capacity;
    int size;
    Compare camp;
    void shiftUp(int index);
    void shiftDown(int index);
public:
    MinHeap(int capacity, Compare camp){
        this->capacity = capacity;
        this->size = 0;
        this->data = new T[capacity];
        this->camp = camp;
    }
    ~MinHeap();
    void insert(const T& value);  // ★
    const T& getMin() const;   // ★
    T removeMin(); // ★
    int getSize() const;
    void ChangeToHeap(const T* arr, int n);
}

MinHeap::shiftUp(int index){  // 从 index 向上调整堆
    while(index > 0){
        int parent = (index - 1) / 2;
        if(camp(data[index], data[parent])){
            swap(data[index], data[parent]);
            index = parent;
        }
        else{
            break;
        }
    }
}

MinHeap::shiftDown(int index){
    int left = index * 2 + 1;
    while(left < size){
        int minIndex = left;
        int right = left + 1;
        if(right < size && camp(data[right], data[left])){
            minIndex = right;
        }
        if(camp(data[minIndex], data[index])){
            swap(data[minIndex], data[index]);
            index = minIndex;
            left = index * 2 + 1;
        }
        else{
            break;
        }
    }
}

MinHeap::insert(const T& value){  // 插入新元素, 然后用 shiftup 调整堆
    assert(size < capacity);
    data[size] = value;
    shiftUp(size);
    size++;
}

MinHeap::removeMin(){  // 删除堆顶元素, 用最后一个元素替换堆顶, 然后 shiftDown 调整堆
    assert(size > 0);
    T ret = data[0];
    data[0] = data[size - 1];
    size--;
    shiftDown(0);
    return ret;
}

MinHeap::getMin() const{  // 获取堆顶元素
    assert(size > 0);
    return data[0];
}

MinHeap::ChangeToHeap(const T* arr, int n){
    size = 0;
    for (size_t i = 0; i < n; i++)
    {
        insert(arr[i]);
    }
    
}

void ApplicationRTInspectionTest(void){
    const int K = 5;
    MinHeap<int, Less<int>> minHeap(K, Less<int>());
    vector<int> stream = {10, 3, 5, 7, 2, 8, 6, 4, 9, 1};
    for(int value : stream){
        minHeap.insert(value);
    }
    // get top K elements
    vector<int> topK;
    for (size_t i = 0; i < K; i++)
    {
        topK.push_back(minHeap.removeMin());
    }
    
}