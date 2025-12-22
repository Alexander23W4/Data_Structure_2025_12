#include <iostream>
#include <vector>
#include <string>
#include <vector>
using namespace std;

// 4-12
pair<int,int> findSaddlePoint(const vector<vector<int>>& A) {
    int m = A.size(), n = A[0].size();
    for(int i=0;i<m;i++){
        
        int minCol = 0;
        for(int j=1;j<n;j++) if(A[i][j]<A[i][minCol]) minCol=j;
        
        bool isSaddle=true;
        for(int k=0;k<m;k++) if(A[k][minCol]>A[i][minCol]) {isSaddle=false; break;}
        if(isSaddle) return {i, minCol};
    }
    return {-1,-1}; 
}
// 答: 时间复杂度: O(m*n)

// 4-13
bool isPalindrome(const string &s){
    int l=0, r=s.size()-1;
    while(l<r){
        if(s[l++] != s[r--]) return false;
    }
    return true;
}

// 时间复杂度: O(n)

// 4-14
string replaceAll(string s, const string &t, const string &v){
    size_t pos=0;
    while((pos=s.find(t,pos)) != string::npos){
        s.replace(pos, t.size(), v);
        pos += v.size(); // 防止死循环
    }
    return s;
}

// 时间复杂度: O(n*m)  

// 5-24

struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr){}
};

TreeNode* buildFromArray(const vector<int>& T, int i=0){
    if(i>=T.size()) return nullptr;
    TreeNode* node = new TreeNode(T[i]);
    node->left = buildFromArray(T, 2*i+1);
    node->right = buildFromArray(T, 2*i+2);
    return node;
}

// 5-30
void printBracket(TreeNode* root){
    if(!root) return;
    cout << root->val;
    if(root->left || root->right){
        cout << "(";
        printBracket(root->left);
        if(root->right) cout << ",";
        printBracket(root->right);
        cout << ")";
    }
}

// 5-37
struct LCNode{
    char val;
    LCNode* leftChild;   // 左子女
    LCNode* rightSib;    // 右兄弟
    LCNode(char v): val(v), leftChild(nullptr), rightSib(nullptr){}
};

void printIndented(LCNode* root, int level=0){
    if(!root) return;
    for(int i=0;i<level;i++) cout << "  "; // 缩格
    cout << root->val << endl;
    printIndented(root->leftChild, level+1);
    printIndented(root->rightSib, level);
}

