#include <iostream>

struct Node {
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* up = nullptr;
    int npl = 1;

    Node(int val): val(val) {};
};

struct LeftistHeap {
    Node* root = nullptr;

    void print() {
        print(root, 0);
        std::cout << std::endl;
    }

    void print(Node* node, int h) {
        if (!node) return;
        print(node->right, h+1);
        for (int i = 0; i < h; i++) std::cout << "  ";
        std::cout << node->val << std::endl;
        print(node->left, h+1);
    }

    void insert(int val) {
        root = merge(root, new Node(val));
    }

    Node* deleteMax() {
        Node* node = root;
        root = merge(root->left, root->right);
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->val < b->val) std::swap(a, b);
        a->right = merge(a->right, b);
        if (!a->left) {
            std::swap(a->left, a->right);
            a->npl = 1;
        } else {
            if (a->left->npl < a->right->npl) std::swap(a->left, a->right);
            a->npl = a->left->npl + 1;
        }
        return a;
    }
};

int main() {
    LeftistHeap heap;
    heap.insert(8);
    heap.insert(6);
    heap.insert(5);
    heap.insert(1);
    heap.insert(4);
    heap.insert(2);
    heap.insert(9);
    heap.print();

    heap.deleteMax();
    heap.print();
    heap.deleteMax();
    heap.print();
}
