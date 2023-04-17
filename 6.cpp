#include <iostream>
#include <queue>
using namespace std;

// 还需把所有cin cout相关代码删除，否则会超时
bool debug = true;

struct Node {
    int value, maxLeft;
    Node *left, *right;
    Node(int v, Node *l = nullptr, Node *r = nullptr) { 
        value = v;
        left = l;
        right = r;
        maxLeft = -1;
    }
};

class BST {
public:
    Node *root;
    int succflag;         // 除了最右的右子树的叶子结点，其它结点都有中序后继，且它们的值都小于前者
    BST() { root = NULL; }
    BST(int preorder[], int n) {
        root = process(preorder, 0, n - 1);
        Node *p = root;
        while (p->right) { p = p->right; }
        succflag = p->value; // 实际上就是根结点的中序后继
    }

    // 通过前序遍历构建二叉树
    Node* process(int preorder[], int start, int end) {
        if (start > end) return nullptr;
        int mid = start, val = preorder[start];
        while (mid <= end && preorder[mid] <= val) { // 找到右结点
            mid++;
        }
        Node* left = process(preorder, start + 1, mid - 1);
        Node* right = process(preorder, mid, end);
        return new Node(val, left, right);
    }
};

int maxLeft(Node *root) { // 中序前继
    Node *max = root->left;
    while (max->right != nullptr) {
        max = max->right;
    }
    return max->value;
}

// 对数进行压缩，先序遍历
Node* compress(Node *root, int succFlag) {
    
    if (root->left != nullptr) {
        root->maxLeft = maxLeft(root);
    }
    if (!root->left && !root->right && root->value < succFlag) {
        delete root; // 没有用
        return nullptr;
    }

    if (root->left) {
        root->left = compress(root->left, succFlag);
    }
    if (root->right) {
        root->right = compress(root->right, succFlag);
    }
    return root;
}

// 打印先序遍历的结果
void printBST(Node* root) {
    if (root == nullptr) {
        return;
    }
    printf("%d ", root->value);
    if (root->maxLeft < 0) {
        printf("- ");
    } 
    else {
        printf("%d ", root->maxLeft);
    }
    printBST(root->left);   
    printBST(root->right);   
}

void levelOrderTraversal(Node* root) {
    if (!root) {
        return;
    }
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* node = q.front();
            q.pop();
            cout << node->value << "_";
            if (node->maxLeft != -1) {
                cout << node->maxLeft << " ";
            } else {
                cout << "- ";
            }
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        cout << endl;
    }
}


int main() {
    if (debug) {
        freopen("data.in", "r", stdin);
    }

    int n;
    scanf("%d", &n);
    int *preorder = new int[n];
    for (int i = 0; i< n; i++) {
        scanf("%d", &preorder[i]);
    }
    BST bst(preorder, n);
    delete[] preorder;  // 有用，不删会MLE

    if (debug) {
        levelOrderTraversal(bst.root);
        cout << endl;
    }

    compress(bst.root, bst.succflag);
    if (debug) {
        levelOrderTraversal(bst.root);
    } else {
        printBST(bst.root);
    }


    return 0;
}