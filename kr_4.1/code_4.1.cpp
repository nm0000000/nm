#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <random>

using namespace std;

// Генераторы случайных чисел
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> real_dist(0.0, 1.0);
uniform_int_distribution<int> int_dist(0, 100);

double random_double(double a, double b) {
    return a + (b - a) * real_dist(gen);
}

int random_int(int a, int b) {
    return uniform_int_distribution<int>(a, b)(gen);
}

// Вычисление суммарного расстояния от всех клиентов до ближайших центров
double totalDistance(const vector<pair<double, double>>& clients,
                     const vector<pair<double, double>>& centers) {
    double total = 0.0;
    for (const auto& client : clients) {
        double min_dist = 1e30;
        for (const auto& center : centers) {
            double dx = client.first - center.first;
            double dy = client.second - center.second;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
        total += min_dist;
    }
    return total;
}

// Алгоритм имитации отжига для задачи размещения объектов
vector<pair<double, double>> sa_facility_location(
    const vector<pair<double, double>>& clients,
    int k, double temp, double cooling
) {
    // Инициализация: случайные позиции k центров
    vector<pair<double, double>> centers(k);
    for (int i = 0; i < k; i++) {
        centers[i] = {
            random_double(-10, 10),
            random_double(-10, 10)
        };
    }
    double current_cost = totalDistance(clients, centers);

    while (temp > 1e-6) {
        // Создаём кандидата: сдвигаем один случайный центр
        vector<pair<double, double>> new_centers = centers;
        int idx = random_int(0, k - 1);
        new_centers[idx].first += random_double(-1, 1) * temp;
        new_centers[idx].second += random_double(-1, 1) * temp;

        double new_cost = totalDistance(clients, new_centers);

        // Критерий Метрополиса
        if (new_cost < current_cost) {
            // Принимаем улучшение однозначно
            centers = new_centers;
            current_cost = new_cost;
        } else {
            // Вычисляем вероятность принятия ухудшения
            double delta = new_cost - current_cost;
            double probability = exp(-delta / temp);

            // Генерируем случайное число от 0 до 1
            double rand_prob = random_double(0.0, 1.0);

            if (rand_prob < probability) {
                // Принимаем ухудшение с вероятностью probability
                centers = new_centers;
                current_cost = new_cost;
            }
        }

        // Охлаждение
        temp *= cooling;
    }

    return centers;
}

int main() {
    int n, k;
    double temp, cooling;

    cout << "Введите количество клиентов: ";
    cin >> n;
    cout << "Введите количество центров (k): ";
    cin >> k;
    cout << "Введите начальную температуру (temp): ";
    cin >> temp;
    cout << "Введите коэффициент охлаждения (cooling, например 0.99): ";
    cin >> cooling;

    vector<pair<double, double>> clients(n);
    cout << "Введите координаты клиентов (x y):\n";
    for (int i = 0; i < n; i++) {
        cin >> clients[i].first >> clients[i].second;
    }

    // Запуск алгоритма
    vector<pair<double, double>> result = sa_facility_location(clients, k, temp, cooling);

    // Вывод результата
    cout << "\nОптимальные позиции центров:\n";
    for (int i = 0; i < k; i++) {
        cout << "Центр " << (i + 1) << ": ("
             << result[i].first << ", " << result[i].second << ")\n";
    }

    double final_cost = totalDistance(clients, result);
    cout << "Итоговая суммарная дистанция: " << final_cost << endl;

    return 0;
}


// Пример работы алгоритма:
// Введите количество клиентов: 3
// Введите количество центров (k): 2
// Введите начальную температуру (temp): 85
// Введите коэффициент охлаждения (cooling, например 0.99): 0,6
// Введите координаты клиентов (x y):

// Оптимальные позиции центров:
// Центр 1: (-1.84145, -2.25673)
// Центр 2: (78.575, 10.5646)
// Итоговая суммарная дистанция: 8.73806
