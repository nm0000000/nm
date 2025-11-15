// СОЗДАНИЕ МУЛЬТИСПИСКА НА ЯЗЫКЕ C++
#include <iostream>

// Узел двусвязного списка
struct Node {
    int data;
    Node *prev;
    Node *next;
    
    // Простой конструктор
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

int main() {
    // Создание двух узлов
    Node *first = new Node(1); // Первый узел
    Node *second = new Node(2); // Второй узел

    // Настройка связи между ними
    first->next = second;       // Первый узел ссылается на следующий (второй)
    second->prev = first;       // Второй узел ссылается на предыдущий (первый)

    // Вывод данных второго узла через первый
    std::cout << "Значение следующего узла: " << first->next->data << std::endl;

    // Очистка памяти перед выходом
    delete first;
    delete second;

    return 0;
}




// СОЗДАНИЕ ОЧЕРЕДИ НА ЯЗЫКЕ C++
#include <iostream>
#include <queue>
#include <string>

int main() {
    std::queue<std::string> Queue; // Создание пустой очереди
    Queue.push("Анна"); // Добавление элементов в очередь
    Queue.push("Мария");
    Queue.push("Александр");

    std::cout << "Первый элемент: " << Queue.front() << std::endl; // Получение первого элемента
    std::cout << "Последний элемент: " << Queue.back() << std::endl; // Получение последнего элемента

    return 0;
}




// СОЗДАНИЕ ОЧЕРЕДИ НА ЯЗЫКЕ C++
#include <deque>
#include <iostream>
int main() {
    std::deque<int> d = {5, 10, 15};
    d.push_front(0);
    d.push_back(20);
    for (int num : d) { std::cout << num << " "; }
// Вывод: 0 5 10 15 20 
    return 0;}




// СОЗДАНИЕ ПРИОРИТЕТНОЙ ОЧЕРЕДИ НА ЯЗЫКЕ C++
#include <iostream>
#include <queue>
int main() {
    std::priority_queue<int> pq;
    pq.push(100);
    pq.push(150);
    pq.push(200);
    std::cout << "The highest priority element is: " << pq.top() << std::endl;
    pq.pop();
    std::cout << "After popping, the highest priority element is: " << pq.top() << std::endl;
    return 0;
}
