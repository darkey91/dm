#include <iostream>

class Node {
private:
    int data;
    Node *next;

public:
    friend class List;

    Node(int data, Node *next = nullptr) {
        this->data = data;
        this->next = next;
    }

    int getData() {
        return this->data;
    }
};


class List {
public:
    List() {
        begin = end = nullptr;
        _size = 0;
    }

    void push_back(int data) {
        ++_size;
        Node *newNode = new Node(data);
        if (begin == nullptr) {
            begin = end = newNode;
        } else {
            end->next = newNode;
            end = newNode;
        }
    }

    void addAt(int data, int index) {
        Node *newNode = new Node(data);
        if (index == 0) {
            newNode->next = begin;
            begin = newNode;
        } else if (_size == index) {
            end->next = newNode;
            end = newNode;
        } else {
            Node *cur = begin;
            int i = 1;
            while (i != index) {
                cur = cur->next;
                ++i;
            }
            newNode->next = cur->next;
            cur->next = newNode;
        }
        ++_size;
    }

    int size() {
        return _size;
    }

    void print() {
        Node *cur = begin;
        while (cur != nullptr) {
            std::cout << cur->data << " ";
            cur = cur->next;
        }
    }

    Node *getPointer(int index) {
        int i = 0;
        Node *cur = begin;
        while (i != index) {
            ++i;
            cur = cur->next;
        }
        return cur;
    }

private:
    Node *begin;
    Node *end;
    int _size;
};

List list;
std::string str;


void binarySearch(int left, int right, int key) {

    while (left < right - 1) {
        int mid = (left + right) >> 1;

        Node *node = list.getPointer(mid);

        std::cout << 1 << " " << node->getData() << " " << key << " \n";
        std::cout.flush();
        std::cin >> str;

        if (str == "YES") {
            left = mid;
        } else {
            right = mid;
        }

    }

    list.addAt(key, right);
}


int main() {
    int n;
    std::cin >> n;
    list.push_back(1);

    for (int i = 2; i <= n; ++i) {
        int k = list.size();
        binarySearch(-1, k, i);


    }
    std::cout << 0 << " ";
    list.print();
    return 0;
}