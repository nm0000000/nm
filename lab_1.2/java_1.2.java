// СОЗДАНИЕ МУЛЬТИСПИСКА НА JAVA
public class Node {
    int data;
    Node prev;
    Node next;
    public Node(int data)
    {
        this.data = data;
        this.prev = null;
        this.next = null;
    }
}
public class DoublyLinkedList {
    Node head;
    Node tail;
    public DoublyLinkedList()
    {
        this.head = null;
        this.tail = null;
    }
}




// СОЗДАНИЕ ОЧЕРЕДИ НА JAVA
import java.util.LinkedList;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        Queue<String> queue = new LinkedList<>();
        queue.add("апельсин");
        queue.add("мандарин");
        queue.add("манго");
        
        while (!queue.isEmpty()) {
            String fruit = queue.poll();
            if (fruit != null) {
                System.out.println(fruit);
            }
        }
    }
}




// СОЗДАНИЕ ДЕКА НА JAVA
import java.util.Deque;
import java.util.ArrayDeque;

class StackExample {
    public static void main(String[] args) {
        Deque<Integer> stack = new ArrayDeque<>();
        
        stack.push(10);
        stack.push(30);
        stack.push(20);
        
        while (!stack.isEmpty()) {
            System.out.println(stack.pop());
        }
    }
}




// СОЗДАНИЕ ПРИОРИТЕТНОЙ ОЧЕРЕДИ НА JAVA
import java.util.PriorityQueue;
import java.util.Comparator;

class MinHeapExample {
    public static void main(String[] args) {
        // Создание очереди с натуральным порядком (min-heap)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        
        // Добавление элементов
        minHeap.offer(40);
        minHeap.offer(8);
        minHeap.offer(55);
        minHeap.offer(21);
        
        // Извлечение элементов (будут извлекаться в порядке возрастания)
        while (!minHeap.isEmpty()) {
            System.out.println(minHeap.poll());
            // Вывод: 8, 21, 40, 55
        }
    }
}
