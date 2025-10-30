#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функционал для отображения состояния массива
void printArray(const vector<int>& arr) {
    for (auto num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Основной алгоритм гравитационной сортировки
void beadSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Максимальная высота бусинок (самое большое число)
    int max_height = *max_element(arr.begin(), arr.end());

    // Создание матрицы "бусинок" (количество строк = len(arr))
    vector<vector<bool>> beads(arr.size(), vector<bool>(max_height));

    // Наполнение матрицы: вертикальные линии представляют числа
    for (size_t i = 0; i < arr.size(); ++i) {
        fill(beads[i].begin(), beads[i].begin() + arr[i], true);
    }

    // Моделирование "падения" бусинок вниз
    for (int col = 0; col < max_height; ++col) {
        // Подсчет количества "упавших" бусинок в каждом столбце
        int count = 0;
        for (const auto& row : beads) {
            if (row[col]) count++;
        }

        // Перестроение матриц (сбрасываем бусы вниз)
        for (size_t i = 0; i < arr.size(); ++i) {
            beads[i][col] = (i < count);
        }
    }

    // Восстанавливаем отсортированную последовательность из "матрицы"
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = accumulate(beads[i].begin(), beads[i].end(), 0);
    }
}

// Точка входа программы
int main() {
    vector<int> arr = {5, 3, 1, 7, 4, 6, 2};
    cout << "Исходный массив: ";
    printArray(arr);

    beadSort(arr);

    cout << "Отсортированный массив: ";
    printArray(arr);

    return 0;
}
