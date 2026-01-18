#include <iostream>

#define M 10

// #define DEBUG
#ifdef DEBUG
    #define LOG(x) x;
#else
    #define LOG(x)
#endif

struct Node {
    int key;
    Node* next = nullptr;
    char val;

    Node(int key_, char val_) {
        key = key_;
        val = val_;
    }
};

void print(Node* p) {
    while (p) {
        std::cout << p->key << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

void printBuckets(Node* start[]) {
    std::cout << std::endl;
    for (int i = 0; i < M; i++) {
        std::cout << "Bucket " << i << ": ";
        print(start[i]);
    }
    std::cout << std::endl;
}

Node* arrayToLinkedList(int keys[], char vals[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(keys[0], vals[0]);
    Node* p = head;
    for (int i = 1; i < n; i++) {
        p->next = new Node(keys[i], vals[i]);
        p = p->next;
    }
    return head;
}

Node* bucketSort(Node* p) {
    Node* start[M] = { nullptr };
    Node* end[M] = { nullptr };

    LOG(printBuckets(start))

    while (p) {
        int i = p->key;
        if (!start[i])
            start[i] = p;
        else
            end[i]->next = p;
        end[i] = p;
        p = p->next;
        end[i]->next = nullptr;

        LOG(printBuckets(start))
    }

    p = nullptr;
    Node* last = nullptr;
    for (int i = 0; i < M; i++) {
        if (!start[i]) continue;
        if (!p)
            p = start[i];
        else
            last->next = start[i];
        last = end[i];
        start[i] = nullptr;
        end[i] = nullptr;

        LOG(printBuckets(start))
        LOG(print(p))
    }
    if (last) last->next = nullptr;

    return p;
}

int main() {
    int keys[] = {3, 6, 4, 1, 9, 0, 2, 5, 8, 7, 4, 6, 2, 1, 9, 0, 3, 5, 8, 7, 2, 4, 6, 1, 0, 9, 8, 7, 5, 3, 2, 4};
    int n = sizeof(keys)/sizeof(keys[0]);
    char vals[n];
    int cnt[M] = {0};
    for (int i = 0; i < n; i++) {
        vals[i] = 'a' + cnt[keys[i]]++;
    }
    Node* list = arrayToLinkedList(keys, vals, n);
    std::cout << "Original list:" << std::endl;
    print(list);

    list = bucketSort(list);
    std::cout << "Sorted list:" << std::endl;
    print(list);

    return 0;
}
