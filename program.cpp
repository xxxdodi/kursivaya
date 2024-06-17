#include <iostream>
using namespace std;

// Базовый класс узла дерева
class TreeNode {
public:
    int item;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value, TreeNode* par = nullptr) 
        : item(value), parent(par), left(nullptr), right(nullptr) {}
};

// Класс для бинарного дерева
class BinaryTree {
private:
    TreeNode* root;

    // Вспомогательный метод для рекурсивного поиска
    TreeNode* searchTree(TreeNode* node, int x) const {
        if (node == nullptr || node->item == x) {
            return node;
        }
        if (x < node->item) {
            return searchTree(node->left, x);
        } else {
            return searchTree(node->right, x);
        }
    }

    // Вспомогательный метод для рекурсивной вставки
    void insertTree(TreeNode*& node, int x, TreeNode* parent) {
        if (node == nullptr) {
            node = new TreeNode(x, parent);
        } else if (x < node->item) {
            insertTree(node->left, x, node);
        } else {
            insertTree(node->right, x, node);
        }
    }

    // Вспомогательный метод для удаления узла
    void deleteNode(TreeNode*& node, int x) {
        if (node == nullptr) {
            return;
        }
        if (x < node->item) {
            deleteNode(node->left, x);
        } else if (x > node->item) {
            deleteNode(node->right, x);
        } else {
            if (node->left == nullptr) {
                TreeNode* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node;
                node = node->left;
                delete temp;
            } else {
                TreeNode* temp = findMinimum(node->right);
                node->item = temp->item;
                deleteNode(node->right, temp->item);
            }
        }
    }

    // Вспомогательный метод для поиска минимального узла
    TreeNode* findMinimum(TreeNode* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Вспомогательный метод для симметричного обхода
    void traverseTree(TreeNode* node) const {
        if (node != nullptr) {
            traverseTree(node->left);
            cout << node->item << " ";
            traverseTree(node->right);
        }
    }

public:
    // Конструктор
    BinaryTree() : root(nullptr) {}

    // Метод для поиска элемента
    TreeNode* search(int x) const {
        return searchTree(root, x);
    }

    // Метод для вставки элемента
    void insert(int x) {
        insertTree(root, x, nullptr);
    }

    // Метод для удаления элемента
    void remove(int x) {
        deleteNode(root, x);
    }

    // Метод для симметричного обхода
    void inOrderTraversal() const {
        traverseTree(root);
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL,"ru");
    // Создание массива элементов для вставки в дерево
    int elements[] = {10, 5, 15, 3, 7, 13, 17};
    int n = sizeof(elements) / sizeof(elements[0]);

    BinaryTree tree;

    // Вставка элементов в дерево
    for (int i = 0; i < n; ++i) {
        tree.insert(elements[i]);
    }

    // Симметричный обход дерева
    cout << "Симметричный обход: ";
    tree.inOrderTraversal();

    // Поиск элемента
    int searchItem = 7;
    TreeNode* foundNode = tree.search(searchItem);
    if (foundNode != nullptr) {
        cout << "Элемент " << searchItem << " найден в дереве" << endl;
    } else {
        cout << "Элемент " << searchItem << " не найден в дереве" << endl;
    }

    // Удаление элемента
    int deleteItem = 10;
    tree.remove(deleteItem);
    cout << "Симметричный обход после удаления " << deleteItem << ": ";
    tree.inOrderTraversal();

    return 0;
}
