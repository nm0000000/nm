// РЕАЛИЗАЦИЯ КУЧИ ФИБОНАЧЧИ НА C++

#include <iostream>
#include <climits>
#include <unordered_map>

using namespace std;

struct FibNode {
    int key;           // ключ вершины
    int degree;        // степень вершины (количество детей)
    bool mark;         // пометка удаления ребра (для каскадного обрезания)
    FibNode* p;        // указатель на родителя
    FibNode* child;    // указатель на первого ребёнка
    FibNode* left;     // левый сосед в кольце
    FibNode* right;    // правый сосед в кольце

    FibNode(int val) : key(val), degree(0), mark(false), p(nullptr), child(nullptr), left(this), right(this) {}
};

class FibonacciHeap {
private:
    FibNode* minNode;          // указатель на минимальное дерево
    size_t numNodes;           // количество элементов в куче

    // Вспомогательные методы

    void addToRoot(FibNode* n) {
        // добавляем вершину в кольцо корней
        if (minNode == nullptr) {
            minNode = n;
        } else {
            n->right = minNode->right;
            n->left = minNode;
            minNode->right->left = n;
            minNode->right = n;
        }
    }

    void removeFromRoot(FibNode* n) {
        // удаляем вершину из кольца корней
        if (n->left == n) {   // единственная вершина?
            minNode = nullptr;
        } else {
            n->left->right = n->right;
            n->right->left = n->left;
            if (minNode == n) {
                minNode = n->right;
            }
        }
    }

    void cut(FibNode* x, FibNode* y) {
        // отсоединяем x от y и перемещаем x в корни
        if (x == y->child) {
            y->child = x->right;
        }
        x->right->left = x->left;
        x->left->right = x->right;
        x->p = nullptr;
        x->mark = false;
        addToRoot(x);
    }

    void cascadeCut(FibNode* y) {
        // рекурсивно поднимаемся вверх и выполняем отсечение
        FibNode* z = y->p;
        if (z != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadeCut(z); // поднимаясь дальше, повторяем процедуру
            }
        }
    }

    void consolidate() {
        // уплотняем корни одинаковой степени
        unordered_map<size_t, FibNode*> degrees;
        auto curr = minNode;
        do {
            FibNode* temp = curr;
            curr = curr->right;
            while (degrees.count(temp->degree)) {
                FibNode* sameDegNode = degrees[temp->degree]; // находим равностепенный узел
                if (temp->key < sameDegNode->key) {
                    link(sameDegNode, temp); // меньший становится родителем большего
                    degrees.erase(temp->degree);
                } else {
                    link(temp, sameDegNode); // больший становится родителем меньшего
                    break;
                }
            }
            degrees[temp->degree] = temp;
        } while (curr != minNode);
        
        minNode = nullptr;
        for (auto& kv : degrees) {
            addToRoot(kv.second);
            if ((minNode == nullptr) || (kv.second->key < minNode->key)) {
                minNode = kv.second;
            }
        }
    }

    void link(FibNode* y, FibNode* x) {
        // соединяем два узла, делая y ребёнком x
        removeFromRoot(y);
        y->p = x;
        y->mark = false;
        if (x->child == nullptr) {
            x->child = y;
        } else {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree += 1;
    }

public:
    FibonacciHeap() : minNode(nullptr), numNodes(0) {}

    ~FibonacciHeap() {
        clear(); // очистка памяти
    }

    void insert(int key) {
        // создание нового узла и добавление его в корни
        FibNode* newNode = new FibNode(key);
        addToRoot(newNode);
        if ((minNode == nullptr) || (newNode->key < minNode->key)) {
            minNode = newNode;
        }
        numNodes++;
    }

    int extractMin() {
        // извлечение минимума и обновление структуры
        if (minNode == nullptr) return INT_MAX;
        FibNode* z = minNode;
        FibNode* child = z->child;
        if (child != nullptr) {
            while (true) {
                FibNode* nextChild = child->right;
                addToRoot(child); // перенос всех детей корня в корневую зону
                child->p = nullptr;
                if (nextChild == child) break;
                child = nextChild;
            }
        }
        removeFromRoot(z);
        if (numNodes > 1) {
            consolidate(); // сжатие структур после удаления
        }
        numNodes--;
        int result = z->key;
        delete z;
        return result;
    }

    void decreaseKey(FibNode* x, int newKey) {
        // уменьшение ключа и необходимые перестановки
        if (newKey >= x->key) return; // проверка условия
        x->key = newKey;
        FibNode* y = x->p;
        if ((y != nullptr) && (x->key < y->key)) {
            cut(x, y);       // отсекаем ребро
            cascadeCut(y);   // запускаем процесс срезания
        }
        if (x->key < minNode->key) {
            minNode = x;
        }
    }

    void clear() {
        // полная очистка кучи
        while (minNode != nullptr) {
            extractMin();
        }
    }

    bool empty() {
        return numNodes == 0;
    }

    int findMin() {
        return minNode ? minNode->key : INT_MAX;
    }
};

int main() {
    FibonacciHeap fibHeap;

    fibHeap.insert(8);
    fibHeap.insert(10);
    fibHeap.insert(12);
    fibHeap.insert(6);
    fibHeap.insert(4);

    cout << "Минимальное значение: " << fibHeap.findMin() << endl;

    fibHeap.decreaseKey(fibHeap.minNode, 2); // уменьшаем минимальный ключ
    cout << "Новое минимальное значение: " << fibHeap.findMin() << endl;

    cout << "Удалено минимум: " << fibHeap.extractMin() << endl;

    return 0;
}
