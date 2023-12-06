#include <iostream>
#include <random>
#include <fstream>
#include <string>

using namespace std;

// Тест на простоту Миллера–Рабина
// Полезная функция для выполнения модульного возведения в степень.
// Он возвращает (x^ y) % p
int power(int x, unsigned int y, int p) {
    int res = 1; // Инициализировать результат
    x = x % p; // Обновите x, если оно больше или равно p

    while (y > 0) {
        // Если y нечетно, умножьте x на результат
        if (y & 1)
            res = (res * x) % p;

        // когда y равно
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

// Эта функция вызывается для всех k испытаний. Он возвращается
// false, если n является составным, и возвращает true, если n
// вероятно, простое число.
// d - нечетное число, такое, что d *2 = n-1
// для некоторого r >= 1
bool miillerTest(int d, int n) {
    // Выберите случайное число в [2..n-2]
    // Угловые шкафы убедитесь, что n > 4
    int a = 2 + rand() % (n - 4);

    // Вычислить a^d % n
    int x = power(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    // Продолжайте возводить x в квадрат, пока не произойдет одно из следующих
    // действий случиться (1) d не достигает n-1 (2) (x^2) % n не равно 1 (3) (x^
    // 2) % n не равно n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    // Возвратный композит
    return false;
}

// Он возвращает false, если n является составным, и возвращает true, если n
// вероятно является простым числом. k - это входной параметр, который
// определяет уровень точности. Более высокое значение k указывает на большую
// точность.
bool isPrimeMillerRabin(int n, int k) {
    // Угловые случаи
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // Найдите r такое, что n = 2^d * r + 1 для некоторого r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Повторить заданное количество 'k' раз
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}

// Функция создания рандомного числа
long long random_number(int len) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<unsigned long long> dist(0, 9);

    unsigned long long number = 0;
    for (int j = 0; j < len; ++j) {
        number = number * 10 + dist(rng);
    }
    return number;
}

// Функция записи в test.txt
void create_number(int qty, int len) {
    vector<unsigned long long> massiv;
    unsigned long long M;
    ofstream out("test.txt");
    for (int i = 0; i < qty;) {
        M = random_number(len);
        if ((!isPrimeMillerRabin(M, 4)) && (M % 2) && (M % 5) && (to_string(M).length() == len)) {
            massiv.push_back(M);
            i++;
        }
    }
    for (auto rm : massiv) {
        out << rm << '\n';
    }
    out.close();
}