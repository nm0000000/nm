// АЛГОРИТМ ДЕЙКСТРЫ C++

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

// Структура для представления узла в очереди с приоритетом
struct Node {
    int vertex;     // номер вершины
    int distance;   // расстояние до вершины
};

// Определим оператор сравнения для приоритетной очереди
bool operator<(const Node& a, const Node& b) {
    return a.distance > b.distance; // меньшие расстояния имеют больший приоритет
}

void dijkstra(const unordered_map<int, vector<pair<int, int>>>& graph, int source) {
    // Массив для хранения расстояний до каждой вершины
    unordered_map<int, int> distances;
    
    // Заполняем расстояния бесконечностью, кроме начальной вершины
    for (auto it : graph) {
        distances[it.first] = INT_MAX;
    }
    distances[source] = 0;

    // Приоритетная очередь для обработки вершин
    priority_queue<Node> pq;
    pq.push({source, 0});

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        int u = current.vertex;
        int d = current.distance;

        // Пропускаем вершины, которые были обновлены позже
        if (d > distances[u]) continue;

        // Перебираем соседей текущей вершины
        for (auto neighbour : graph.at(u)) {
            int v = neighbour.first;      // соседняя вершина
            int w = neighbour.second;     // вес ребра
            int alt = distances[u] + w;   // альтернативное расстояние

            // Если найдено лучшее расстояние, обновляем и добавляем в очередь
            if (alt < distances[v]) {
                distances[v] = alt;
                pq.push({v, alt});
            }
        }
    }

    // Печать кратчайших расстояний
    cout << "Кратчайшие расстояния от вершины " << source << ":" << endl;
    for (auto pair : distances) {
        cout << "Вершина " << pair.first << ": Расстояние = " << pair.second << endl;
    }
}

int main() {
    // Пример графа в виде списка смежности
    unordered_map<int, vector<pair<int, int>>> graph = {
        {1, {{2, 1}, {3, 4}}},
        {2, {{1, 1}, {3, 2}, {4, 5}}},
        {3, {{1, 4}, {2, 2}, {4, 1}}},
        {4, {{2, 5}, {3, 1}}}
    };

    int startVertex = 1;
    dijkstra(graph, startVertex);

    return 0;
}









// ПОИСК ПУТИ ГРАФА
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Класс для представления графа
class Graph {
private:
    int V;                   // Количество вершин
    vector<vector<int>> adj;  // Список смежности

public:
    // Конструктор
    Graph(int vertices) : V(vertices), adj(V) {}

    // Добавление ребра в граф
    void addEdge(int src, int dest) {
        adj[src].push_back(dest);  // Поскольку граф ненаправленный, добавляем ребро дважды
        adj[dest].push_back(src);
    }

    // Найти кратчайший путь от src до dest
    bool bfsPath(int src, int dest, vector<int>& parent) {
        // Булевый массив для отметки посещённых вершин
        vector<bool> visited(V, false);

        // Очередь для поиска в ширину
        queue<int> q;
        q.push(src);
        visited[src] = true;
        parent[src] = -1;  // Источник не имеет родителя

        while (!q.empty()) {
            int u = q.front();  // Текущая вершина
            q.pop();

            // Просматриваем соседей текущей вершины
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;  // Устанавливаем родителем текущей вершины
                    q.push(v);
                    
                    // Если достигнута цель, прекращаем поиск
                    if (v == dest) {
                        return true;
                    }
                }
            }
        }
        return false;  // Путь не найден
    }

    // Вывод пути от src до dest
    void printPath(vector<int>& parent, int dest) {
        if (parent[dest] != -1) {
            printPath(parent, parent[dest]);
        }
        cout << dest << " ";
    }

    // Основной метод для поиска пути
    void findShortestPath(int src, int dest) {
        vector<int> parent(V, -1);  // Хранит родителей вершин
        if (bfsPath(src, dest, parent)) {
            cout << "Кратчайший путь от " << src << " до " << dest << ": ";
            printPath(parent, dest);
            cout << "\\n";
        } else {
            cout << "Нет пути от " << src << " до " << dest << ".";
        }
    }
};

int main() {
    // Пример графа с 8 вершинами
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 7);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(5, 6);
    g.addEdge(6, 7);

    int src = 0;  // Начало пути
    int dest = 7; // Цель пути

    g.findShortestPath(src, dest);

    return 0;
}
