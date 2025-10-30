#include <iostream>
#include <vector>
using namespace std;

// Вспомогательная функция для переворота части массива
void flip(vector<int>& arr, int i) {
    int start = 0;
    while (start < i) {
        swap(arr[start], arr[i]);
        start++;
        i--;
    }
}

// Основной метод блинной сортировки
void pancakeSort(vector<int>& arr) {
    int currSize = arr.size();  // Текущий размер несортированной части массива
    while (currSize > 1) {
        // Найдем индекс наибольшего элемента в оставшейся части массива
        int maxIndex = 0;
        for (int j = 1; j < currSize; ++j) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }

        // Если максимум находится не в самом начале, переворачиваем его в начало
        if (maxIndex != 0) {
            flip(arr, maxIndex);  // Переворот первой части
        }

        // Теперь переворачиваем всю несортированную часть, чтобы максимум оказался последним
        flip(arr, currSize - 1);  // Переворот всей оставшейся части

        // Уменьшаем размер несортированного участка
        currSize--;
    }
}

// Функция вывода массива
void printArray(const vector<int>& arr) {
    for (int elem : arr) {
        cout << elem << " ";
    }
    cout << endl;
}

// Тестовая функция
int main() {
    vector<int> arr = {3, 6, 2, 4, 5, 1};
    cout << "Исходный массив: ";
    printArray(arr);

    pancakeSort(arr);

    cout << "Отсортированный массив: ";
    printArray(arr);

    return 0;

// Исходный массив: 3 6 2 4 5 1 
// Отсортированный массив: 1 2 3 4 5 6

}
