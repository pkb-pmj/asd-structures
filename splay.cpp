#include <iostream>

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int val_) {
        val = val_;
    }
};

void print(Node* p, int i, int h) {
    if (!p) return;
    print(p->right, 2*i+1, h+1);
    for (int j = 0; j < h; j++) std::cout << "  ";
    std::cout << p->val << std::endl;
    print(p->left, 2*i, h+1);
}

void print(Node* p) {
    print(p, 1, 0);
    std::cout << std::endl;
}

Node* L(Node* p) {
    Node* l = p->left;
    p->left = l->right;
    l->right = p;
    return l;
}

Node* R(Node* p) {
    Node* r = p->right;
    p->right = r->left;
    r->left = p;
    return r;
}

Node* LR(Node* p) {
    Node* l = p->left;
    Node* lr = l->right;
    l->right = lr->left;
    p->left = lr->right;
    lr->left = l;
    lr->right = p;
    return lr;
}

Node* RL(Node* p) {
    Node* r = p->right;
    Node* rl = r->left;
    r->left = rl->right;
    p->right = rl->left;
    rl->right = r;
    rl->left = p;
    return rl;
}

Node* splay(Node* p, int val) {
    if (!p) return nullptr;
    if (val == p->val) return p;
    if (val < p->val) {
        if (!p->left) return p;
        if (val == p->left->val) return L(p);
        if (val < p->left->val) {
            if (!p->left->left) {
                return L(p);
            } else {
                p->left->left = splay(p->left->left, val);
                return L(L(p));
            }
        } else {
            if (!p->left->right) {
                return L(p);
            } else {
                p->left->right = splay(p->left->right, val);
                return LR(p);
            }
        }
    } else {
        if (!p->right) return p;
        if (val == p->right->val) return R(p);
        if (val > p->right->val) {
            if (!p->right->right) {
                return R(p);
            } else {
                p->right->right = splay(p->right->right, val);
                return R(R(p));
            }
        } else {
            if (!p->right->left) {
                return R(p);
            } else {
                p->right->left = splay(p->right->left, val);
                return RL(p);
            }
        }
    }
}

Node* insert(Node* p, int val) {
    Node* pp = new Node(val);
    if (!p) return pp;
    p = splay(p, val);
    if (val == p->val) return p;
    if (val < p->val) {
        pp->left = p->left;
        pp->right = p;
        p->left = nullptr;
    } else {
        pp->right = p->right;
        pp->left = p;
        p->right = nullptr;
    }
    return pp;
}

Node* remove(Node* p, int val) {
    static bool left = true;

    if (!p) return nullptr;
    if (!p->left && !p->right) return p;
    p = splay(p, val);
    if (p->val != val) return p;
    Node* pp;
    if (p->left && !p->right) {
        pp = splay(p->left, val);
        pp->right = p->right;
    } else if (!p->left && p->right) {
        pp = splay(p->right, val);
        pp->left = p->left;
    } else {
        if (left) {
            pp = splay(p->left, val);
            pp->right = p->right;
        } else {
            pp = splay(p->right, val);
            pp->left = p->left;
        }
        left = !left;
    }
    delete p;
    return pp;
}

int main() {
    Node* root = nullptr;
    for (int i = 1; i < 10; i++) {
        root = insert(root, i);
        print(root);
    }
    for (int i = 1; i < 10; i++) {
        root = splay(root, i);
        print(root);
    }
    for (int i = 1; i < 10; i++) {
        root = remove(root, i);
        print(root);
    }
}
