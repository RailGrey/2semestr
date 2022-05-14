#include <iostream>

struct ListNode {
    int key; // key to access the data and compare ListNodes
    int data ; // raw data
    ListNode* left ; // pointer to left ListNode
    ListNode* right ; // pointer to right ListNode
    ListNode* p; // parent pointer
};

struct SimpleTree {
    ListNode *root;
};

struct Node {
    ListNode* val;
    Node* next;
};

struct Queue {
    unsigned size;
    Node* head;
    Node* tail;
};

ListNode* front(Queue *list) {
    return list -> head -> val;
}

ListNode* rear(Queue *list) {
    return list -> tail -> val;
}

unsigned length(Queue *list) {
    return list -> size;
}

void enQueue(Queue *list, ListNode* value) {
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

ListNode* deQueue(Queue *list) {
    if (list -> head == nullptr) {
        return 0;
    }
    Node* tmp = list -> head;
    ListNode* tmp1 = tmp -> val;
    list -> head = tmp -> next;
    delete tmp;
    list -> size = length(list) - 1;
    return tmp1;
}

bool empty(Queue *list) {
    if ( length(list) == 0) {
        return true;
    } else {
        return false;
    }
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


void insert(SimpleTree *t, ListNode *z, ListNode *NIL) {
    ListNode *y = NIL;
    ListNode *x = t -> root;
    while (x != NIL) {
        y = x;
        if (z -> key < x -> key) {
            x = x -> left;
        } else {
            x = x -> right;
        }
    }
    z -> p = y;
    if (y == NIL) {
        t -> root = z;
    } else if (z -> key < y -> key) {
        y -> left = z;
    } else {
        y -> right = z;
    }
}

ListNode* search(ListNode* root, int key, ListNode *NIL) {
    if ((root == NIL) || (key == root -> key)) {
        return root;
    }
    if (key < root -> key) {
        return search(root -> left, key, NIL);
    } else {
        return search(root -> right, key, NIL);
    }
}

ListNode* find_minimum(ListNode* root, ListNode* NIL) {
    while (root -> left != NIL) {
        root = root -> left;
    }
    return root;
}

ListNode* find_maximum(ListNode* root, ListNode* NIL) {
    while (root -> right != NIL) {
        root = root -> right;
    }
    return root;
}

void transplant(SimpleTree *t, ListNode* u, ListNode* v, ListNode* NIL) {
    if (u -> p == NIL) {
        t -> root = v;
    }
    else if (u == u -> p -> left) {
        u -> p -> left = v;
    } else {
        u -> p -> right = v;
    }
    if (v != NIL) {
        v -> p = u -> p;
    }
}

void remove(SimpleTree *t, ListNode* z, ListNode* NIL) {
    if (z -> left == NIL) {
        transplant(t, z, z -> right, NIL);
    } else if (z -> right == NIL) {
        transplant(t, z, z -> left, NIL);
    } else {
        ListNode* y = find_minimum(z -> right, NIL);
        if (y -> p != z) {
            transplant(t, y, y -> right, NIL);
            y -> right = z -> right;
            y -> right -> p = y;
        }
        transplant(t, z, y, NIL);
        y -> left = z -> left;
        y -> left -> p = y;
    }
}

void print(SimpleTree *t, Queue *q, ListNode *NIL) {
    if (t -> root == NIL) {
        return;
    }
    enQueue(q, t -> root);
    unsigned int l;
    ListNode* tmp;
    while (!empty(q)) {
        l = length(q);
        for (int i = 0; i < l; i++) {
            tmp = front(q);
            std::cout << tmp -> key << " ";
            if (tmp -> left != NIL) {
                enQueue(q, tmp -> left);
            }
            if (tmp -> right != NIL) {
                enQueue(q, tmp -> right);
            }
            deQueue(q);
        }
        std::cout << std::endl;
    }
}



int main() {
    Queue queue = {0, nullptr, nullptr};
    ListNode NIL = {0, 0, nullptr, nullptr, nullptr};
    SimpleTree tree = {&NIL};
    ListNode z1 = {10, 1, &NIL, &NIL , &NIL};
    ListNode z2 = {8, 1, &NIL, &NIL, &NIL};
    ListNode z3 = {12, 1, &NIL, &NIL, &NIL};
    ListNode z4 = {7, 1, &NIL, &NIL, &NIL};
    ListNode z5 = {9, 1, &NIL, &NIL, &NIL};
    ListNode z6 = {14, 1, &NIL, &NIL, &NIL};
    ListNode z7 = {13, 1, &NIL, &NIL, &NIL};
    ListNode z8 = {18, 1, &NIL, &NIL, &NIL};
    insert(&tree, &z1, &NIL);
    insert(&tree, &z2, &NIL);
    insert(&tree, &z3, &NIL);
    insert(&tree, &z4, &NIL);
    insert(&tree, &z5, &NIL);
    insert(&tree, &z6, &NIL);
    insert(&tree, &z7, &NIL);
    remove(&tree, &z6, &NIL);
    insert(&tree, &z8, &NIL);
    remove(&tree, &z1, &NIL);
    print(&tree, &queue, &NIL);
    std::cout << find_minimum(tree.root, &NIL) -> key << " " << find_maximum(tree.root, &NIL) -> key;
    return 0;
}
