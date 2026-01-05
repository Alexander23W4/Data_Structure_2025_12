#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// 6.16
struct Node {
    int key;
    Node* prev;
    Node* next;
    Node(int k = 0) : key(k), prev(nullptr), next(nullptr) {}
};

// 有序双向链表指针搜索（finger search）
Node* search(Node* head, Node*& p, int key, int& steps) {
    steps = 0;
    if (!head) return nullptr;
    if (!p) p = head;

    Node* cur = p;

    // 向前或向后选择
    if (key >= cur->key) {
        while (cur && cur->key <= key) {
            steps++;
            if (cur->key == key) {
                p = cur;
                return cur;
            }
            cur = cur->next;
        }
    } else {
        while (cur && cur->key >= key) {
            steps++;
            if (cur->key == key) {
                p = cur;
                return cur;
            }
            cur = cur->prev;
        }
    }
    return nullptr;
}

// 构造有序双向链表
Node* build(const vector<int>& a) {
    if (a.empty()) return nullptr;
    Node* head = new Node(a[0]);
    Node* cur = head;
    for (size_t i = 1; i < a.size(); ++i) {
        Node* n = new Node(a[i]);
        cur->next = n;
        n->prev = cur;
        cur = n;
    }
    return head;
}

// 平均搜索长度（成功）
double avg_success(Node* head) {
    vector<Node*> nodes;
    for (Node* p = head; p; p = p->next) nodes.push_back(p);

    int n = nodes.size();
    double total = 0;

    for (int i = 0; i < n; ++i) {
        Node* finger = nodes[i];
        for (int j = 0; j < n; ++j) {
            int steps = 0;
            Node* p = finger;
            search(head, p, nodes[j]->key, steps);
            total += steps;
        }
    }
    return total / (n * n);
}

// 平均搜索长度（失败，假设失败位置均匀）
double avg_fail(Node* head) {
    vector<Node*> nodes;
    for (Node* p = head; p; p = p->next) nodes.push_back(p);

    int n = nodes.size();
    double total = 0;

    for (int i = 0; i < n; ++i) {
        Node* finger = nodes[i];
        for (int j = 0; j <= n; ++j) {
            int fakeKey;
            if (j == 0) fakeKey = nodes[0]->key - 1;
            else if (j == n) fakeKey = nodes[n - 1]->key + 1;
            else fakeKey = (nodes[j - 1]->key + nodes[j]->key) / 2;

            int steps = 0;
            Node* p = finger;
            search(head, p, fakeKey, steps);
            total += steps;
        }
    }
    return total / (n * (n + 1));
}

int main() {
    vector<int> data = {1, 3, 5, 7, 9, 11, 13};
    Node* head = build(data);
    Node* p = head;

    cout << avg_success(head) << endl;
    cout << avg_fail(head) << endl;
    return 0;
}

// 6.17
template<typename T>
class SkipList {
private:
    struct Node {
        T key;
        Node** forward;
        int level;
        Node(int lvl, const T& k) : key(k), level(lvl) {
            forward = new Node*[lvl + 1];
            for (int i = 0; i <= lvl; ++i) forward[i] = nullptr;
        }
        ~Node() { delete[] forward; }
    };

    Node* head;
    int maxLevel;
    Node* iter;   // 顺序访问指针

public:
    SkipList(int maxLvl = 16) : maxLevel(maxLvl) {
        head = new Node(maxLevel, T());
        iter = nullptr;
    }

    ~SkipList() {
        Node* p = head;
        while (p) {
            Node* next = p->forward[0];
            delete p;
            p = next;
        }
    }

    // 插入（简化版）
    void Insert(const T& key) {
        Node* update[64];
        Node* p = head;

        for (int i = maxLevel; i >= 0; --i) {
            while (p->forward[i] && p->forward[i]->key < key)
                p = p->forward[i];
            update[i] = p;
        }

        int lvl = rand() % (maxLevel + 1);
        Node* n = new Node(lvl, key);

        for (int i = 0; i <= lvl; ++i) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }

    // 顺序访问：Begin
    Node* Begin() {
        iter = head->forward[0];
        return iter;
    }

    // 顺序访问：Next
    Node* Next() {
        if (!iter) return nullptr;
        iter = iter->forward[0];
        return iter;
    }
};



// 7.25
int fibSearch(int a[], int n, int key) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm1 + fibMMm2;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm1 + fibMMm2;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        if (a[i] < key) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (a[i] > key) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && offset + 1 < n && a[offset + 1] == key)
        return offset + 1;

    return -1;
}


7.27
struct Node {
    int key;
    int count;
    Node* left;
    Node* right;
    Node(int k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

void insert(Node*& root, int key) {
    if (!root) {
        root = new Node(key);
        return;
    }
    if (key == root->key) {
        root->count++;
    } else if (key < root->key) {
        insert(root->left, key);
    } else {
        insert(root->right, key);
    }
}


7.30
// 二叉搜索树节点定义
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// 插入节点
void insert(Node*& root, int key) {
    if (!root) {
        root = new Node(key);
        return;
    }
    if (key < root->key)
        insert(root->left, key);
    else
        insert(root->right, key);
}

// 中序遍历，将元素按序写入数组
void inorder(Node* root, int a[], int& index) {
    if (!root) return;
    inorder(root->left, a, index);
    a[index++] = root->key;
    inorder(root->right, a, index);
}

// 排序算法：BST排序
void bstSort(int a[], int n) {
    Node* root = nullptr;
    for (int i = 0; i < n; ++i)
        insert(root, a[i]);
    int idx = 0;
    inorder(root, a, idx);
}

// 删除BST中最大元素，返回最大元素值
int deleteMax(Node*& root) {
    if (!root) return -1;  // 空树
    Node* parent = nullptr;
    Node* cur = root;
    while (cur->right) {
        parent = cur;
        cur = cur->right;
    }
    int maxVal = cur->key;
    if (!parent) {
        // 最大元素就是根
        root = cur->left;
    } else {
        parent->right = cur->left;
    }
    delete cur;
    return maxVal;
}

// 测试
int main() {
    int a[] = {7, 3, 9, 1, 5, 8, 10};
    int n = sizeof(a)/sizeof(a[0]);

    bstSort(a, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;

    Node* root = nullptr;
    for (int i = 0; i < n; ++i)
        insert(root, a[i]);

    int maxVal = deleteMax(root);
    cout << "Deleted max: " << maxVal << endl;

    return 0;
}


8.19
// 图的邻接表表示
template<typename T>
struct Graph {
    int n;  // 顶点数
    vector<vector<int>> adj;
    vector<T> vertex;

    Graph(int size) : n(size), adj(size), vertex(size) {}
    void addEdge(int u, int v) { adj[u].push_back(v); }
};

// 生成树节点（左子女-右兄弟表示）
template<typename T>
struct TreeNode {
    T data;
    TreeNode* leftChild;   // 第一个子女
    TreeNode* rightSibling; // 右兄弟
    TreeNode(T d) : data(d), leftChild(nullptr), rightSibling(nullptr) {}
};

// DFS扩展：生成左子女-右兄弟树
template<typename T>
void DFS(Graph<T>& G, int v, bool visited[], TreeNode<T>*& t) {
    visited[v] = true;
    t = new TreeNode<T>(G.vertex[v]);
    TreeNode<T>* prevChild = nullptr;  // 前一个已经添加的子女

    for (int w : G.adj[v]) {
        if (!visited[w]) {
            TreeNode<T>* child = nullptr;
            DFS(G, w, visited, child);  // 递归生成子树

            if (!t->leftChild) {
                // 第一个子女
                t->leftChild = child;
            } else {
                // 作为右兄弟插入
                prevChild->rightSibling = child;
            }
            prevChild = child;
        }
    }
}

8.28
template<class T, class E>
struct Graph {
    int n;
    vector<vector<pair<int, E>>> adj; // (目标顶点, 权值)
    Graph(int size) : n(size), adj(size) {}
    void addEdge(int u, int v, E w) { adj[u].emplace_back(v, w); }
};

// 使用Dijkstra计算单源最短路径
template<class E>
vector<E> dijkstra(const Graph<int, E>& G, int s) {
    vector<E> dist(G.n, numeric_limits<E>::max());
    dist[s] = 0;
    using P = pair<E, int>; // (距离, 顶点)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : G.adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// 返回带权有向图的中心顶点编号及最小偏心距
template<class T, class E>
int centre(Graph<T, E>& G, E& biasdist) {
    biasdist = numeric_limits<E>::max();
    int center = -1;

    for (int v = 0; v < G.n; ++v) {
        vector<E> dist = dijkstra(G, v);
        E ecc = 0;
        for (int u = 0; u < G.n; ++u) {
            if (dist[u] == numeric_limits<E>::max()) continue; // 不可达
            if (dist[u] > ecc) ecc = dist[u];
        }
        if (ecc < biasdist) {
            biasdist = ecc;
            center = v;
        }
    }
    return center;
}





