#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Функция поиска прыжками
int jumpSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    int blockSize = sqrt(n); // Размер блока (m)

    // Ищем ближайший блок, где последний элемент >= искомому
    int prevBlockStart = 0;
    while (prevBlockStart < n && arr[min(prevBlockStart + blockSize, n)-1] < target) {
        prevBlockStart += blockSize;
    }

    // Линейный поиск в нужном блоке
    for (int i = max(prevBlockStart - blockSize, 0); i < min(prevBlockStart + blockSize, n); ++i) {
        if (arr[i] == target) {
            return i; // Нашли элемент
        }
    }

    return -1; // Элемент не найден
}

// Основная функция
int main() {
    vector<int> arr = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    int target = 55;

    int index = jumpSearch(arr, target);
    if (index != -1) {
        cout << "Элемент найден на позиции: " << index << endl;
    } else {
        cout << "Элемент не найден." << endl;
    }

    return 0;

// Результат:
// Элемент найден на позиции: 10

}
