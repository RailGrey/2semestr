#include <iostream>

struct Node {
    int val;
    Node* next;
    Node* prev;
};

struct DoubleList {
    unsigned size;
    Node* head;
    Node* tail;
};

Node* get(DoubleList *list, int idx) {
    Node* tmp = list -> head;
    for (int i = 0; i < idx; i++) {
        tmp = tmp -> next;
    }
    return tmp;
}

unsigned length(DoubleList *List) {
    return List -> size;
}

void push_back(DoubleList *list, int value) {
    Node *new_Node = new Node;
    new_Node -> val = value;
    if (list -> size == 0) {
        list -> head = new_Node;
        list -> tail = new_Node;
        new_Node -> prev = nullptr;
    } else {
        list -> tail -> next = new_Node;
        new_Node -> prev = list -> tail;
        list -> tail = new_Node;
    }
    new_Node -> next = nullptr;
    list -> size = length(list) + 1;
}

void push_forward(DoubleList *list, int value) {
    Node *new_Node = new Node;
    new_Node -> val = value;
    if (list -> size == 0) {
        new_Node -> next = nullptr;
        list -> tail = new_Node;
    } else {
        new_Node -> next = list -> head;
        list -> head -> prev = new_Node;
    }
    new_Node -> prev = nullptr;
    list -> head = new_Node;
    list -> size = length(list) + 1;
}

void insert(DoubleList *list, int idx, int value) {
    Node *new_Node = new Node;
    new_Node -> val = value;
    if (list -> size == 0) {
        list -> head = new_Node;
        list -> tail = new_Node;
        new_Node -> next = nullptr;
        new_Node -> prev = nullptr;
    } else {
        Node* tmp = get(list, idx - 1);
        new_Node -> prev = tmp;
        new_Node -> next = tmp -> next;
        tmp -> next = new_Node;
    }
    list -> size = length(list) + 1;
}

void pop_back(DoubleList *list) {
    Node* tmp = get(list, length(list)-2);
    tmp -> next = nullptr;
    delete list -> tail;
    list -> tail = tmp;
    list -> size = length(list) - 1;
}

void pop_forward(DoubleList *list) {
    Node* tmp = list -> head;
    list -> head = tmp -> next;
    list -> head -> prev = nullptr;
    delete tmp;
    list -> size = length(list) - 1;
}

void remove(DoubleList *list, int idx) {
    Node* tmp = get(list,idx-1);
    Node* tmp1 = tmp -> next -> next;
    delete tmp -> next;
    tmp -> next = tmp1;
    tmp1 -> prev = tmp;
    list -> size = length(list) - 1;
}

void print(DoubleList *list) {
    Node* tmp = list -> head;
    for (int i = 0; i < length(list); i++) {
        std::cout << tmp -> val << " ";
        tmp = tmp -> next;
    }
    std::cout << "Finish" << '\n';
}

void printReverse(DoubleList *list) {
    Node* tmp = list -> tail;
    for (int i = 0; i < length(list); i++) {
        std::cout << tmp -> val << " ";
        tmp = tmp -> prev;
    }
    std::cout << "Finish" << std::endl;
}

void clear(DoubleList *list) {
    int size = length(list);
    for (int i = 0; i < size; i++) {
        pop_back(list);
    }
}

void fill(DoubleList *list, int data[], int size) {
    for (int i = 0; i < size; i++) {
        push_forward(list, data[i]);
    }
}

int main() {
    DoubleList list = {0, nullptr, nullptr};
    int a[3] = {1, 3, 5};
    fill(&list, a, 3);
    print(&list);
    push_back(&list, 2);
    print(&list);
    printReverse(&list);
    //std::cout << list.tail -> prev -> prev -> prev -> val;
    return 0;
}

