# РЕАЛИЗАЦИЯ БИНАРНОЙ КУЧИ НА C++
  
#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap;
    
    // Вспомогательная функция: поднимает элемент вверх по дереву, пока не восстановится свойство кучи
    void siftUp(int idx) {
        while (idx > 0 && heap[(idx - 1)/2] > heap[idx]) {   // Проверяем условие минимальной кучи
            swap(heap[(idx - 1)/2], heap[idx]);
            idx = (idx - 1)/2;
        }
    }

    // Вспомогательная функция: опускает элемент вниз по дереву, восстанавливая структуру кучи
    void siftDown(int idx) {
        int size = heap.size();
        while ((2 * idx + 1) < size) {      // Пока существует левый потомок
            int leftChildIdx = 2*idx+1;
            int rightChildIdx = 2*idx+2;
            
            int smallest = leftChildIdx;
            if (rightChildIdx < size && heap[rightChildIdx] < heap[leftChildIdx])
                smallest = rightChildIdx;
                
            if (heap[idx] <= heap[smallest])
                break;
                
            swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }
public:
    // Добавление нового элемента в кучу
    void push(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);           // Поднимаем новый элемент вверх
    }

    // Извлечение минимального элемента
    int pop() {
        if (empty()) throw runtime_error("Heap is empty");
        
        int minValue = heap.front();       // Получаем минимальный элемент
        heap.front() = heap.back();        // Перемещаем последний элемент на вершину
        heap.pop_back();                   // Удаляем последний элемент
        siftDown(0);                      // Восстанавливаем порядок в куче
        return minValue;
    }

    // Возвращение наименьшего элемента без удаления
    int top() const {
        if (!empty())
            return heap.front();
        else
            throw runtime_error("Heap is empty");
    }

    bool empty() const {
        return heap.empty();
    }
};

// Тестирование реализации
int main() {
    BinaryHeap bh;
    
    // Заполняем кучу элементами
    bh.push(10);
    bh.push(5);
    bh.push(8);
    bh.push(3);
    bh.push(12);
    bh.push(7);
    
    cout << "Минимальное значение: " << bh.top() << endl; // Должно вывести 3

    // Извлекаем элементы
    while(!bh.empty()) {
        cout << bh.pop() << " ";
    }
    // Результат вывода: 3 5 7 8 10 12

    return 0;
}
