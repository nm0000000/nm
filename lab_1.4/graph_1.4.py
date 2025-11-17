# АЛГОРИТМ ДЕЙКСТРЫ НА PYTHON

import heapq

def dijkstra(graph, start):
    # Начальные условия: все расстояния считаем бесконечно большими,
    # кроме стартового узла, расстояние которого равно 0
    distances = {vertex: float('inf') for vertex in graph}
    distances[start] = 0
    
    # Очередь с приоритетом для хранения узлов с минимальным расстоянием
    priority_queue = [(0, start)]  # очередь хранит пары (расстояние, узел)
    
    while priority_queue:
        # Извлекаем узел с наименьшим известным расстоянием
        current_distance, current_vertex = heapq.heappop(priority_queue)
        
        # Если текущее расстояние больше ранее сохраненного значения, пропускаем узел
        if current_distance > distances[current_vertex]:
            continue
        
        # Проходим по всем соседям текущего узла
        for neighbor, weight in graph[current_vertex].items():
            new_distance = current_distance + weight
            
            # Если новый путь короче старого, обновляем расстояние
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                heapq.heappush(priority_queue, (new_distance, neighbor))  # помещаем новую пару в очередь
                
    return distances

# Пример графа, представлен в виде словаря смежности с весом рёбер
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}

start_vertex = 'A'
shortest_distances = dijkstra(graph, start_vertex)

print(f"Кратчайшие расстояния от вершины '{start_vertex}' до всех остальных:")
for vertex, dist in shortest_distances.items():
    print(f"{vertex}: {dist}")







# НАХОЖДЕНИЕ КРАТЧАЙШЕГО ПУТИ ГРАФА НА PYTHON
from collections import deque

def bfs_shortest_path(graph, start, goal):
    # Словарь для восстановления пути (каждая вершина помечается своим предком)
    parent = {start: None}
    # Очередь для поиска в ширину
    queue = deque([start])
    
    while queue:
        node = queue.popleft()  # Берём первую вершину из очереди
        
        # Если дошли до искомой вершины, останавливаемся
        if node == goal:
            break
        
        # Обрабатываем каждую соседнюю вершину
        for next_node in graph[node]:
            if next_node not in parent:
                parent[next_node] = node  # Сохраняем предыдущего узла
                queue.append(next_node)   # Добавляем в очередь следующую вершину
    
    # Восстанавливаем путь
    path = []
    current = goal
    while current is not None:
        path.insert(0, current)  # вставляем сначала последнюю вершину
        current = parent.get(current, None)
    
    return path if len(path) > 0 else None

# Пример графа (список смежности)
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

# Нахождение кратчайшего пути
path = bfs_shortest_path(graph, 'A', 'F')
if path:
    print("Кратчайший путь:", " -> ".join(path))
else:
    print("Путь не найден.")

