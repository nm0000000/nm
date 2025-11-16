// СОЗДАНИЕ БИНАРНОЙ КУЧИ НА JAVA

import java.util.Arrays;

class BinaryHeap<T extends Comparable<T>> {
    private T[] data;
    private int size;

    @SuppressWarnings("unchecked")
    public BinaryHeap(int initialCapacity) {
        this.data = (T[]) new Comparable[initialCapacity];
        this.size = 0;
    }

    // Метод для добавления элемента в кучу
    public void insert(T element) {
        ensureCapacity();
        data[size++] = element;
        swim(size - 1); // Восстанавливаем свойства кучи снизу-вверх
    }

    // Метод для извлечения минимального элемента
    public T extractMin() throws Exception {
        if (size == 0) {
            throw new Exception("Куча пуста.");
        }
        T minElement = data[0];
        data[0] = data[--size];
        sink(0); // Восстанавливаем свойства кучи сверху-вниз
        return minElement;
    }

    // Внутренняя операция "swim": плавание вверх
    private void swim(int pos) {
        while (pos > 0 && less(pos, parentIndex(pos))) {
            swap(pos, parentIndex(pos));
            pos = parentIndex(pos);
        }
    }

    // Внутренняя операция "sink": погружение вниз
    private void sink(int pos) {
        while (hasLeftChild(pos)) {
            int childPos = leftChildIndex(pos);
            if (hasRightChild(pos) && less(rightChildIndex(pos), childPos)) {
                childPos = rightChildIndex(pos);
            }
            if (less(pos, childPos)) {
                break;
            }
            swap(pos, childPos);
            pos = childPos;
        }
    }

    // Индексация родителей и детей
    private boolean hasLeftChild(int pos) {
        return leftChildIndex(pos) < size;
    }

    private boolean hasRightChild(int pos) {
        return rightChildIndex(pos) < size;
    }

    private int parentIndex(int pos) {
        return (pos - 1) / 2;
    }

    private int leftChildIndex(int pos) {
        return 2 * pos + 1;
    }

    private int rightChildIndex(int pos) {
        return 2 * pos + 2;
    }

    // Вспомогательная функция для сравнения элементов
    private boolean less(int first, int second) {
        return data[first].compareTo(data[second]) < 0;
    }

    // Перестановка элементов
    private void swap(int first, int second) {
        T temp = data[first];
        data[first] = data[second];
        data[second] = temp;
    }

    // Увеличение емкости массива
    private void ensureCapacity() {
        if (size == data.length) {
            data = Arrays.copyOf(data, 2 * data.length);
        }
    }

    // Преобразование обычного массива в кучу
    public void buildHeap(T[] array) {
        size = array.length;
        System.arraycopy(array, 0, data, 0, size);
        for (int i = parentIndex(size - 1); i >= 0; i--) {
            sink(i);
        }
    }

    // Методы для удобства тестирования
    public String toString() {
        return Arrays.toString(Arrays.copyOfRange(data, 0, size));
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public static void main(String[] args) throws Exception {
        BinaryHeap<Integer> binaryHeap = new BinaryHeap<>(10);
        binaryHeap.insert(10);
        binaryHeap.insert(5);
        binaryHeap.insert(15);
        binaryHeap.insert(3);
        binaryHeap.insert(20);

        System.out.println(binaryHeap.toString()); // Текущее состояние кучи
        System.out.println("Минимальный элемент: " + binaryHeap.extractMin());
        System.out.println("Новый вид кучи: " + binaryHeap.toString());
    }
}
