#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct Queue {
    unsigned size;
    Node* head;
    Node* tail;
};

int front(Queue *list) {
    return list -> head -> val;
}

int rear(Queue *list) {
    return list -> tail -> val;
}

unsigned length(Queue *list) {
    return list -> size;
}

void enQueue(Queue *list, int value) {
    Node *new_Node = new Node;
    new_Node -> val = value;
    if (list -> size == 0) {
        list -> head = new_Node;
        list -> tail = new_Node;
    } else {
        list -> tail -> next = new_Node;
        list -> tail = new_Node;
    }
    new_Node -> next = nullptr;
    list -> size = length(list) + 1;
}


int deQueue(Queue *list) {
    if (list -> head == nullptr) {
        return 0;
    }
    Node* tmp = list -> head;
    int tmp1 = tmp -> val;
    list -> head = tmp -> next;
    delete tmp;
    list -> size = length(list) - 1;
    return tmp1;
}


void print(Queue *list) {
    Node* tmp = list -> head;
    for (int i = 0; i < length(list); i++) {
        std::cout << tmp -> val << " ";
        tmp = tmp -> next;
    }
    std::cout << "Finish" << '\n';
}

void clear(Queue *list) {
    int size = length(list);
    for (int i = 0; i < size; i++) {
        deQueue(list);
    }
}

void fill(Queue *list, int data[], int size) {
    for (int i = 0; i < size; i++) {
        enQueue(list, data[i]);
    }
}




int main() {
    Queue list = {0, nullptr, nullptr};
    print(&list);
    deQueue(&list);
    int a[5] = {1, 2,3, 4,5};
    fill(&list, a, 5);
    enQueue(&list, 5);
    print(&list);
    deQueue(&list);
    print(&list);
    return 0;
}
