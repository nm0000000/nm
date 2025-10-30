#include <iostream>
#include <vector>
using namespace std;

// Функция бинарного поиска
int binarySearch(const vector<int>& arr, int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;  // Элемент найден
        } else if (arr[mid] < target) {
            low = mid + 1;  // Искомый элемент правее середины
        } else {
            high = mid - 1;  // Искомый элемент левее середины
        }
    }
    return -1;  // Элемент не найден
}

// Функция экспоненциального поиска
int exponentialSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) return -1;  // Массив пуст

    // Проверяем первый элемент
    if (arr[0] == target) return 0;

    // Экспоненциально увеличиваем шаг
    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;  // Удвоение шага
    }

    // Находим диапазон и производим бинарный поиск
    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

// Основная функция
int main() {
    vector<int> arr = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    int target = 55;

    int index = exponentialSearch(arr, target);
    if (index != -1) {
        cout << "Индекс элемента: " << index << endl;
    } else {
        cout << "Элемент не найден." << endl;
    }

    return 0;

// Результат:
// Индекс элемента:10

}
