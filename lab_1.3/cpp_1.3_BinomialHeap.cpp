// РЕАЛИЗАЦИЯ БИНОМИНАЛЬНОЙ КУЧИ НА C++

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Узел биноминального дерева
struct Node {
    int key;
    int degree; // степень дерева (количество детей)
    Node* parent;
    Node* child;  // первый ребёнок
    Node* sibling; // следующий брат

    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

// Биноминальная куча
class BinomialHeap {
private:
    Node* head; // указатель на первый корень в списке корней

    // Слияние двух биноминальных деревьев одинаковой степени
    Node* mergeTrees(Node* h1, Node* h2) {
        if (h1->key > h2->key) {
            swap(h1, h2);
        }
        h2->parent = h1;
        h2->sibling = h1->child;
        h1->child = h2;
        h1->degree++;
        return h1;
    }

    // Объединение двух списков корней (используется при merge)
    Node* mergeRootLists(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        Node* head = nullptr;
        Node** last = &head;

        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *last = h1;
                h1 = h1->sibling;
            } else {
                *last = h2;
                h2 = h2->sibling;
            }
            last = &((*last)->sibling);
        }

        if (h1) *last = h1;
        if (h2) *last = h2;

        return head;
    }

    // Проход по списку корней и объединение деревьев одинаковой степени
    void consolidate() {
        if (!head) return;

        vector<Node*> trees;
        Node* curr = head;

        // Собираем все корни в вектор
        while (curr) {
            trees.push_back(curr);
            curr = curr->sibling;
        }

        // Очищаем список корней
        head = nullptr;

        // Сортируем по степени (по возрастанию)
        sort(trees.begin(), trees.end(), [](Node* a, Node* b) {
            return a->degree < b->degree;
        });

        for (Node* tree : trees) {
            tree->sibling = nullptr; // обнуляем sibling
            insertTree(tree);
        }
    }

    // Вставить дерево в кучу (с объединением при совпадении степеней)
    void insertTree(Node* tree) {
        tree->sibling = head;
        head = tree;

        Node* prev = nullptr;
        Node* curr = head;
        Node* next = curr->sibling;

        while (next) {
            if (curr->degree != next->degree ||
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
                next = next->sibling;
                continue;
            }

            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                next->sibling = curr->child;
                curr->child = next;
                curr->degree++;
            } else {
                if (prev) {
                    prev->sibling = next;
                } else {
                    head = next;
                }
                curr->sibling = next->child;
                next->child = curr;
                next->degree++;
                curr = next;
            }
            next = curr->sibling;
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    // Вставка ключа
    void insert(int key) {
        Node* newNode = new Node(key);
        BinomialHeap tempHeap;
        tempHeap.head = newNode;
        merge(tempHeap);
    }

    // Получить минимальный ключ (без удаления)
    int getMin() const {
        if (!head) {
            throw runtime_error("Heap is empty");
        }

        int minKey = head->key;
        Node* curr = head;
        while (curr) {
            if (curr->key < minKey) {
                minKey = curr->key;
            }
            curr = curr->sibling;
        }
        return minKey;
    }

    // Извлечь минимальный ключ
    int extractMin() {
        if (!head) {
            throw runtime_error("Heap is empty");
        }

        // Находим корень с минимальным ключом
        Node* minPrev = nullptr;
        Node* minNode = head;
        Node* curr = head;
        Node* prev = nullptr;

        while (curr) {
            if (curr->key < minNode->key) {
                minNode = curr;
                minPrev = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        // Удаляем minNode из списка корней
        if (minPrev) {
            minPrev->sibling = minNode->sibling;
        } else {
            head = minNode->sibling;
        }

        // Создаём новую кучу из детей minNode
        BinomialHeap childHeap;
        Node* child = minNode->child;
        while (child) {
            Node* next = child->sibling;
            child->sibling = nullptr;
            childHeap.insertTree(child);
            child = next;
        }

        // Сливаем оставшуюся кучу с кучей из детей
        merge(childHeap);

        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }

    // Слить другую кучу с текущей
    void merge(BinomialHeap& other) {
        head = mergeRootLists(head, other.head);
        other.head = nullptr;
        consolidate();
    }

    // Проверить, пуста ли куча
    bool isEmpty() const {
        return head == nullptr;
    }

    // Деструктор
    ~BinomialHeap() {
        clear();
    }

    // Очистить кучу
    void clear() {
        while (!isEmpty()) {
            extractMin();
        }
    }
};

// Пример использования
int main() {
    BinomialHeap heap;

    // Добавляем элементы
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    heap.insert(3);
    heap.insert(15);

    cout << "Minimum: " << heap.getMin() << endl; // 3

    cout << "Extracted: ";
    while (!heap.isEmpty()) {
        cout << heap.extractMin() << " ";
    }
    cout << endl;

    return 0;
}
