#include <iostream>
#include <vector>

class Heap {
public:
    std::vector<int> A = { INT_MAX };

    void print() {
        print(1, 0);
    }

    void print(int i, int h) {
        if (2*i+1 < A.size()) print(2*i+1, h+1);
        for (int j = 0; j < h; j++) std::cout << "  ";
        std::cout << A[i] << std::endl;
        if (2*i < A.size()) print(2*i, h+1);
    }

    void up(int i) {
        while (i > 1 && A[i] > A[i/2]) {
            std::swap(A[i], A[i/2]);
            i /= 2;
        }
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

    heap.up(7);
    heap.print();
}
