#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;


void ASSERT_EQ(int result, int test){
    if(result == test) { printf("Test successful!\n");}
    else printf("Test unsuccessful!\n");
}

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = node->right = node->parent = NULL;
    return node;
}

void updateHeight(Node* node) {
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int getBalanceFactor(Node* node) {
    return (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->parent = y->parent;
    y->parent = x;
    if (T2) T2->parent = y;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->parent = x->parent;
    x->parent = y;
    if (T2) T2->parent = x;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    } else if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }
    return node;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return createNode(key);
    if (key < node->key) {
        node->left = insert(node->left, key);
        node->left->parent = node;
    } else if (key > node->key) {
        node->right = insert(node->right, key);
        node->right->parent = node;
    } else {
        return node; 
    }
    updateHeight(node);
    return balance(node);
}

Node* findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root) return root;
    updateHeight(root);
    return balance(root);
}

void printTree(Node* root, int level) {
    if (root) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) printf("   ");
        printf("%d\n", root->key);
        printTree(root->left, level + 1);
    }
}

void TestdeleteNodeResult3(){
    printf("TestdeleteNodeResult3 ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    root = deleteNode(root, 20);
    ASSERT_EQ(root->height, 3);
}

void TestdeleteNodeResult2(){
    printf("TestdeleteNodeResult2 ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = deleteNode(root, 20);
    ASSERT_EQ(root->height, 2);
}


void TestdeleteNodeResult5(){
    printf("TestdeleteNodeResult5 ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 100);
    root = insert(root, 110);
    root = insert(root, 120);
    root = insert(root, 130);
    root = insert(root, 140);
    root = insert(root, 150);
    root = insert(root, 160);
    root = deleteNode(root, 20);
    ASSERT_EQ(root->height, 5);
}



void TestaddNodeResult4(){
    printf("TestaddNodeResult4: ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    root = insert(root, 55);
    root = insert(root, 60);
    ASSERT_EQ(root->height,4);
}
void TestaddNodeResult5(){
    printf("TestaddNodeResult5_1: ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 100);
    root = insert(root, 110);
    root = insert(root, 120);
    root = insert(root, 130);
    root = insert(root, 140);
    root = insert(root, 150);
    root = insert(root, 160);
    ASSERT_EQ(root->height,5);
}
void TestaddNodeResult5_2(){
    printf("TestaddNodeResult5_2: ");
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 100);
    root = insert(root, 110);
    root = insert(root, 120);
    root = insert(root, 130);
    root = insert(root, 140);
    root = insert(root, 150);
    root = insert(root, 160);
    root = insert(root, 170);
    root = insert(root, 180);
    root = insert(root, 190);
    root = insert(root, 200);
    root = insert(root, 210);
    root = insert(root, 220);
    root = insert(root, 230);
    root = insert(root, 240);
    root = insert(root, 250);
    root = insert(root, 260);
    root = insert(root, 270);
    root = insert(root, 280);
    root = insert(root, 290);
    root = insert(root, 300);
    ASSERT_EQ(root->height,5);
}


int main() {
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Original Tree:\n");
    printTree(root, 0);

    root = deleteNode(root, 20);

    printf("\nAfter deleting 20:\n");
    printTree(root, 0);
    TestdeleteNodeResult3();
    TestdeleteNodeResult2();
    TestdeleteNodeResult5();
    TestaddNodeResult4();
    TestaddNodeResult5();
    TestaddNodeResult5_2();
}