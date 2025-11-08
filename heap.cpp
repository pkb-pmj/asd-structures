#include <iostream>
#include <vector>

class Heap {
public:
    std::vector<int> A = { INT_MAX };

    int n() {
        return A.size() - 1;
    }

    void print() {
        print(1, 0);
        std::cout << std::endl;
    }

    void print(int i, int h) {
        if (i > n()) return;
        print(2*i+1, h+1);
        for (int j = 0; j < h; j++) std::cout << "  ";
        std::cout << A[i] << std::endl;
        print(2*i, h+1);
    }

    void swim(int i) {
        while (i > 1 && A[i] > A[i/2]) {
            std::swap(A[i], A[i/2]);
            i /= 2;
        }
    }

    void sink(int i) {
        while (true) {
            int j = i*2;
            if (j > n()) return; // no children
            if (j+1 <= n() && A[j+1] > A[j]) j++; // set j to larger/only child
            if (A[i] < A[j]) std::swap(A[i], A[j]); // sink if smaller
            else return;
            i = j;
        }
    }

    void insert(int v) {
        A.push_back(v);
        swim(n());
    }

    int deleteMax() {
        int v = A[1];
        A[1] = A[n()];
        A.pop_back();
        sink(1);
        return v;
    }
};

int main() {
    Heap heap;
    heap.A.push_back(8);
    heap.A.push_back(6);
    heap.A.push_back(5);
    heap.A.push_back(1);
    heap.A.push_back(4);
    heap.A.push_back(2);
    heap.A.push_back(9);
    heap.print();

    heap.swim(7);
    heap.print();

    heap.A[1] = 2;
    heap.print();
    heap.sink(1);
    heap.print();

    heap = Heap();
    heap.print();

    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    heap.insert(4);
    heap.insert(5);
    heap.insert(6);
    heap.insert(7);
    heap.print();

    heap.deleteMax();
    heap.print();
    heap.deleteMax();
    heap.print();
    heap.deleteMax();
    heap.print();
}
