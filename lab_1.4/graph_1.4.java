// АЛГОРИТМ ДЕЙКСТРЫ НА JAVA

import java.util.*;

class Edge {
    int to;           // Вершина назначения
    double cost;      // Вес ребра
    public Edge(int to, double cost) {
        this.to = to;
        this.cost = cost;
    }
}

class Vertex implements Comparable<Vertex> {
    int index;        // Индекс вершины
    double distance;  // Расчётное минимальное расстояние от стартовой вершины
    public Vertex(int index, double distance) {
        this.index = index;
        this.distance = distance;
    }
    @Override
    public int compareTo(Vertex other) {
        return Double.compare(this.distance, other.distance);
    }
}

public class DijkstraAlgorithm {
    private static final double INFINITY = Double.POSITIVE_INFINITY;

    public static Map<Integer, Double> dijkstra(List<List<Edge>> graph, int start) {
        int n = graph.size();
        PriorityQueue<Vertex> pq = new PriorityQueue<>();
        Map<Integer, Double> distances = new HashMap<>(); // Хранилище расстояний

        // Изначально все расстояния бесконечны, кроме стартовой вершины
        for (int i = 0; i < n; ++i) {
            distances.put(i, INFINITY);
        }
        distances.put(start, 0.0);
        pq.offer(new Vertex(start, 0));

        while (!pq.isEmpty()) {
            Vertex curr = pq.poll();
            int u = curr.index;
            double d = curr.distance;

            // Если текущее расстояние меньше рассчитанного, игнорируем вершину
            if (distances.get(u) < d) continue;

            // Обход соседей текущей вершины
            for (Edge e : graph.get(u)) {
                int v = e.to;
                double weight = e.cost;
                double newDistance = d + weight;

                // Если новый путь короче известного, обновляем расстояние
                if (newDistance < distances.get(v)) {
                    distances.put(v, newDistance);
                    pq.offer(new Vertex(v, newDistance)); // Добавляем обновленную вершину в очередь
                }
            }
        }
        return distances;
    }

    public static void main(String[] args) {
        List<List<Edge>> graph = new ArrayList<>();
        // Инициализация графа (пример графа из четырёх вершин)
        for (int i = 0; i < 4; i++) {
            graph.add(new ArrayList<>());
        }
        graph.get(0).add(new Edge(1, 1.0));
        graph.get(0).add(new Edge(2, 4.0));
        graph.get(1).add(new Edge(2, 2.0));
        graph.get(1).add(new Edge(3, 5.0));
        graph.get(2).add(new Edge(3, 1.0));

        // Выполнение алгоритма Дейкстры
        Map<Integer, Double> distances = dijkstra(graph, 0);

        System.out.println("Минимальные расстояния:");
        for (Integer key : distances.keySet()) {
            System.out.println(key + ": " + distances.get(key));
        }
    }
}






// ПОИСК КРАТЧАЙШЕГО ПУТИ НА JAVA

import java.util.*;

public class PathFinder {
    public static void main(String[] args) {
        // Пример графа (список смежности)
        Map<String, Set<String>> graph = new HashMap<>();
        graph.put("A", new HashSet<>(Arrays.asList("B", "C")));
        graph.put("B", new HashSet<>(Arrays.asList("A", "D", "E")));
        graph.put("C", new HashSet<>(Arrays.asList("A", "F")));
        graph.put("D", new HashSet<>(Collections.singletonList("B")));
        graph.put("E", new HashSet<>(Arrays.asList("B", "F")));
        graph.put("F", new HashSet<>(Arrays.asList("C", "E")));

        String startNode = "A"; // Начальная вершина
        String endNode = "F";   // Целевая вершина

        // Находим кратчайший путь
        List<String> path = findShortestPath(graph, startNode, endNode);

        if (path != null && !path.isEmpty()) {
            System.out.println("Кратчайший путь: " + String.join(" -> ", path));
        } else {
            System.out.println("Путь не найден.");
        }
    }

    /**
     * Поиск кратчайшего пути в графе с помощью BFS
     */
    public static List<String> findShortestPath(Map<String, Set<String>> graph, String start, String destination) {
        Queue<String> queue = new LinkedList<>();
        Map<String, String> parents = new HashMap<>(); // Хранит предыдущие вершины (предков)

        queue.add(start);
        parents.put(start, null); // Нет предшествующего узла у стартовой вершины

        while (!queue.isEmpty()) {
            String current = queue.remove();

            // Дошли до нужной вершины
            if (current.equals(destination)) {
                return buildPath(parents, destination);
            }

            // Переходим к соседним вершинам
            for (String neighbor : graph.getOrDefault(current, Collections.emptySet())) {
                if (!parents.containsKey(neighbor)) {
                    parents.put(neighbor, current); // Сохраняем предыдущий узел
                    queue.add(neighbor);
                }
            }
        }

        return null; // Путь не найден
    }

    /**
     * Реконструирует путь от целевого узла до стартового
     */
    private static List<String> buildPath(Map<String, String> parents, String destination) {
        List<String> path = new ArrayList<>();
        String current = destination;

        while (current != null) {
            path.add(0, current); // Добавляем вершину в начало пути
            current = parents.get(current);
        }

        return path;
    }
}
