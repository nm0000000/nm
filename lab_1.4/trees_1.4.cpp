// РЕАЛИЗАЦИЯ ДЕРЕВЬЕВ НА C++

// 1.Класс вершины дерева
class TNode {
public:
    TNode(int key):
          Key(key),
          Left(nullptr),     // Используйте nullptr вместо 0
          Right(nullptr) {}  // Это улучшает читаемость и безопасность

    int Key;
    TNode* Left;
    TNode* Right;
}



// 2. Класс дерева
class TTree {
public:
    TTree()
        : Root(nullptr) { }  // Лучше использовать nullptr вместо 0

    ~TTree() {
        DestroyNode(Root);   // Деструктор вызывает очистку дерева
    }

private:
    // Вспомогательная функция для удаления всех узлов начиная с указанного
    static void DestroyNode(TNode* node) {
        if (node != nullptr) {
            DestroyNode(node->Left);      // Уничтожаем левое поддерево
            DestroyNode(node->Right);     // Уничтожаем правое поддерево
            delete node;                  // Освобождаем память текущего узла
        }
    }

private:
    TNode* Root;                          // Корень дерева
}



// 3. Добавление ключа в дерево. Нерекурсивная реализация
void TTree::Insert(int x) {
    TNode** cur = &Root;       // Устанавливаем указатель на корень дерева
    while (*cur) {             // Цикл продолжается пока текущий узел не является NULL
        TNode& node = **cur;   // Получаем доступ к текущему узлу
        
        if (x < node.Key) {    // Если новый ключ меньше текущего, двигаемся влево
            cur = &node.Left;
        } else if (x > node.Key) { // Если новый ключ больше текущего, двигаемся вправо
            cur = &node.Right;
        } else {                // Если ключ уже существует, прекращаем вставку
            return;
        }
    }
    *cur = new TNode(x);       // Когда найдена свободная позиция, создаем новый узел
}
