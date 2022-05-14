#include <iostream>

struct ListNode {
    int key;
    int data ;
    unsigned height;
    ListNode* left ;
    ListNode* right ;
    ListNode* p;
};

struct AVLTree {
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

unsigned height(ListNode* root) {
    return root -> height;
}

int balance_factor(ListNode* root) {
    return height(root -> right) - height(root -> left);
}

void fix_height(ListNode* root) {
    unsigned hl = height(root -> left);
    unsigned hr = height(root -> right);
    if (hl > hr) {
        root -> height = hl + 1;
    } else {
        root -> height = hr + 1;
    }
}

ListNode* right_rotation(AVLTree* t, ListNode* p, ListNode* NIL) {
    ListNode* l = p -> left;
    ListNode* b = l -> right;
    l -> p = p -> p;
    if (l -> p == NIL) {
        t -> root = l;
    }
    p -> p = l;
    p -> left = b;
    b -> p = p;
    l -> right = p;
    fix_height(p);
    fix_height(l);
    return l;
}

ListNode* left_rotation(AVLTree* t, ListNode* p, ListNode* NIL) {
    ListNode* r = p -> right;
    ListNode* a = r -> left;
    r -> p = p -> p;
    if (r -> p == NIL) {
        t -> root = r;
    }
    p -> p = r;
    p -> right = a;
    a -> p = p;
    r -> left = p;
    fix_height(p);
    fix_height(r);
    return r;
}

ListNode* balance(AVLTree* t, ListNode* p, ListNode* NIL) {
    fix_height(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p -> right) < 0) {
            p -> right = right_rotation(t, p -> right, NIL);
        }
        return left_rotation(t, p, NIL);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p -> left) > 0) {
            p -> left = left_rotation(t, p -> left, NIL);
        }
        return right_rotation(t, p, NIL);
    }
    return p;
}

void insert(AVLTree *t, ListNode *z, ListNode *NIL) {
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
    while (z != NIL) {
        if (z -> key > z -> p -> key) {
            z -> p -> right = balance(t, z, NIL);
        } else {
            z -> p -> left = balance(t, z, NIL);
        }
        z = z -> p;
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

void transplant(AVLTree *t, ListNode* u, ListNode* v, ListNode* NIL) {
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

void remove(AVLTree *t, ListNode* z, ListNode* NIL) {
    if (z -> left == NIL) {
        transplant(t, z, z -> right, NIL);
    } else if (z -> right == NIL) {
        transplant(t, z, z -> left, NIL);
    } else {
        ListNode* y = find_minimum(z -> right, NIL);
        ListNode* tmp = y -> p;
        if (y -> p != z) {
            transplant(t, y, y -> right, NIL);
            y -> right = z -> right;
            y -> right -> p = y;
        }
        transplant(t, z, y, NIL);
        y -> left = z -> left;
        y -> left -> p = y;

        tmp = find_minimum(tmp, NIL);
        while (tmp != y) {
            if (tmp -> key > tmp -> p -> key) {
                tmp -> p -> right = balance(t, tmp, NIL);
            } else {
                tmp -> p -> left = balance(t, tmp, NIL);
            }
            tmp = tmp -> p;
        }
    }
}

void print(AVLTree *t, Queue *q, ListNode *NIL) {
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

void print_height(AVLTree *t, Queue *q, ListNode *NIL) {
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
            std::cout << tmp -> height << " ";
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

void fill(AVLTree* t, int *keys, int *data, int l, ListNode* NIL) {
    ListNode ** array = new ListNode*[l];
    ListNode tmp;
    for (int i = 0; i < l; i++) {
        array[i] = new ListNode{keys[i], data[i], 0, NIL, NIL, NIL};
        insert(t, array[i], NIL);
    }
}

int main() {
    Queue queue = {0, nullptr, nullptr};
    ListNode NIL = {0, 0, 0, nullptr, nullptr, nullptr};
    AVLTree tree = {&NIL};
    int keys[20] = {44,12,123,32,1,45,23,33,25,15,4,90,167,0,-12, 18, 2, 3, 5, 6};
    int data[20] = {0};
    fill(&tree, keys, data, 20, &NIL);
    print(&tree, &queue, &NIL);
    print_height(&tree, &queue, &NIL);
    remove(&tree, search(tree.root, 23, &NIL), &NIL);
    print(&tree, &queue, &NIL);
    std::cout << find_minimum(tree.root, &NIL) -> key << " " << find_maximum(tree.root, &NIL) -> key << '\n';
    return 0;
}
