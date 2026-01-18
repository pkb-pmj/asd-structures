#include <iostream>

// #define DEBUG
#ifdef DEBUG
    #define LOG(x) x;
#else
    #define LOG(x)
#endif

struct Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    int bal = 0;

    Node(int val_) {
        val = val_;
    }
};

void print(Node* p, int i, int h) {
    if (!p) return;
    print(p->right, 2*i+1, h+1);
    for (int j = 0; j < h; j++) std::cout << "  ";
    std::cout << "(" << p->val << ")" << p->bal << std::endl;
    print(p->left, 2*i, h+1);
}

void print(Node* p) {
    print(p, 1, 0);
    std::cout << std::endl;
}

Node* L(Node* p) {
    LOG(std::cout << "L" << std::endl)
    LOG(print(p))
    Node* l = p->left;
    p->left = l->right;
    l->right = p;
    p->bal = (l->bal <= 0) ? (p->bal - 1) : (p->bal - l->bal - 1);
    l->bal = (p->bal >= 0) ? (l->bal - 1) : (l->bal + p->bal - 1);
    LOG(print(l))
    return l;
}

Node* R(Node* p) {
    LOG(std::cout << "R" << std::endl)
    LOG(print(p))
    Node* r = p->right;
    p->right = r->left;
    r->left = p;
    p->bal = (r->bal >= 0) ? (p->bal + 1) : (p->bal - r->bal + 1);
    r->bal = (p->bal <= 0) ? (r->bal + 1) : (r->bal + p->bal + 1);
    LOG(print(r))
    return r;
}

Node* LR(Node* p) {
    LOG(std::cout << "LR" << std::endl)
    LOG(print(p))
    p->left = R(p->left);
    p = L(p);
    LOG(print(p))
    return p;
}

Node* RL(Node* p) {
    LOG(std::cout << "RL" << std::endl)
    LOG(print(p))
    p->right = L(p->right);
    p = R(p);
    LOG(print(p))
    return p;
}

// can't return two values (Node*, bool h) in C++
// so return Node* like in other functions
// and pass h as a pointer argument
// so we can read the value written to it by the function
Node* insert(Node* p, int val, bool *h /* <- did the subtree's height increase */) {
    // std::cout << "insert" << std::endl;
    // print(p);
    if (!p) {
        *h = true;
        p = new Node(val);
    } else if (val == p->val) {
        *h = false;
    } else if (val < p->val) {
        // works like: p.left, h = insert(p.left, val)
        p->left = insert(p->left, val, h);
        if (*h) {
            if (p->bal <= 0) {
                // prepare h for "returning", instead of: return p, p.bal == 0
                *h = p->bal == 0;
                p->bal++;
            } else {
                p->bal = 2;
                if (p->left->bal >= 0) {
                    *h = p->left->bal == 0;
                    p = L(p);
                } else {
                    *h = false;
                    p = LR(p);
                }
            }
        }
    } else {
        p->right = insert(p->right, val, h);
        if (*h) {
            if (p->bal >= 0) {
                *h = p->bal == 0;
                p->bal--;
            } else {
                p->bal = -2;
                if (p->right->bal <= 0) {
                    *h = p->right->bal == 0;
                    p = R(p);
                } else {
                    *h = false;
                    p = RL(p);
                }
            }
        }
    }
    return p;
}

Node* insert(Node* p, int val) {
    bool h = false;
    return insert(p, val, &h);
}

int main() {
    Node* root = nullptr;
    for (int i = 11; i < 15; i++) {
        std::cout << "INSERTING " << i << std::endl;
        root = insert(root, i);
        print(root);
    }
    for (int i = 5; i >= 1; i--) {
        std::cout << "INSERTING " << i << std::endl;
        root = insert(root, i);
        print(root);
    }
    for (int i = 6; i < 10; i++) {
        std::cout << "INSERTING " << i << std::endl;
        root = insert(root, i);
        print(root);
    }
}
