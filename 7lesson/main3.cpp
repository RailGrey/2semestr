#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct Stack {
    unsigned size;
    Node* head;
    Node* tail;
};

Node* top(Stack *list) {
    Node* tmp = list -> tail;
    return tmp;
}

unsigned length(Stack *list) {
    return list -> size;
}

void push(Stack *list, int value) {
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

void pop(Stack *list) {
    Node* tmp = list -> head;
    int size = length(list);
    if (size > 2) {
        for (int i = 0; i < size - 2; i++) {
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        delete list->tail;
        list->tail = tmp;
        list -> size = length(list) - 1;
    } else if (size == 2) {
        delete list -> head -> next;
        list -> head -> next = nullptr;
        list -> tail = list -> head;
        list -> size = length(list) - 1;
    } else if (size == 1) {
        delete list -> head;
        list -> head = nullptr;
        list -> tail = nullptr;
        list -> size = length(list) - 1;
    }
}

bool empty(Stack *list) {
    if (list -> head == nullptr) {
        return true;
    } else {
        return false;
    }
}

void print(Stack *list) {
    Node* tmp = list -> head;
    for (int i = 0; i < length(list); i++) {
        std::cout << tmp -> val << " ";
        tmp = tmp -> next;
    }
    std::cout << "Finish" << '\n';
}

void clear(Stack *list) {
    int size = length(list);
    for (int i = 0; i < size; i++) {
        pop(list);
    }
}

void fill(Stack *list, int data[], int size) {
    for (int i = 0; i < size; i++) {
        push(list, data[i]);
    }
}

int main() {
    Stack list = {0, nullptr, nullptr};
    int a[4] = {1, 3, 5, 7};
    fill(&list, a, 4);
    print(&list);
    //clear(&list);
    pop(&list);
    pop(&list);
    pop(&list);
    std::cout << list.head -> val;
    print(&list);
    return 0;
}

