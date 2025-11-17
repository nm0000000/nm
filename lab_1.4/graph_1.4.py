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
