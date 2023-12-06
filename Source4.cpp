#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

#include "to_create_number.h"
#include "to_read_number.h"
#include "calculation.h"

using namespace std;
using namespace std::chrono;

int main() {
    setlocale(LC_ALL, "Russian");

    create_number(500, 10);
    vector<unsigned long long> test_chisla = read_number();

    vector<unsigned long long> save_position;
    vector<unsigned long long> save_nomer;
    vector<unsigned long long> save_massiv;
    vector<unsigned long long> save_k;
    vector<unsigned long long> save_time;

    ofstream outSave;
    ofstream outTime;

    for (int k = 10; k <= 20; ++k) {
        int t = k + 1;
        int rx;
        unsigned long long n;

        int save = 0;
        save_position.clear();
        save_nomer.clear();
        save_massiv.clear();
        save_k.clear();
        save_time.clear();

        cout << endl;
        cout << "Для k = " << k << endl;

        // Начало отсчёта времени
        // цикл по числам из массива test_chisel
        auto start = high_resolution_clock::now();
        for (int g = 0; g < test_chisla.size(); ++g) {
            n = test_chisla[g];

            // создание факторный базы
            vector<long long> FB = { -1, 2 };
            int p = 3;
            int i = 2;
            while (i < k) {
                if (isPrime(p)) {
                    long long b = (n % p);
                    long long rm = sqrt_m(b);

                    if (rm * rm == b) {
                        FB.push_back(p);
                        i++;
                    }
                }
                p += 2;
            }

            // перебор x = 0, 1, -1, 2, -2, ...
            int count = 0;
            vector<long long> x = { 0 };

            unsigned long long m = sqrt_m(n);
            // функция нахождения подходящих пар
            for (i = 0; (count < t) && (abs(x[i]) < m); ++i) {
                if (x[i] > 0) {
                    if (Good(b_i(x[i], m, n), FB, k)) {
                        count++;
                    }
                }
                else {
                    if (Good(-b_i(x[i], m, n), FB, k)) {
                        count++;
                    }
                }

                if (i % 2 == 0) {
                    rx = x[i] * (-1) + 1;
                }
                else {
                    rx = x[i] * (-1);
                }
                x.push_back(rx);
            }

            // выход из цикла
            if (count == t) {
                cout << endl;
                cout << "Пары найдены!" << endl;
                cout << "Для " << g + 1 << " числа: " << n << endl;
                cout << endl;

                save_massiv.push_back(n);
                save_nomer.push_back(g);
                save++;
                save_position.push_back(save);
            }

            if (abs(x[i]) >= m) {
                cout << g + 1 << " Нет" << endl;
            }
        }

        // Конец отсчёта времени
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        save_time.push_back(duration.count());
        save_k.push_back(k);

        outSave.open("save.txt", ios::app);
        outSave << "Для k = " << k << '\n';
        outSave << "Нашли подходящие пары для этих чисел:" << '\n';
        for (size_t rsp = 0; rsp < save_position.size(); ++rsp) {
            outSave << save_nomer[rsp] + 1 << ": " << save_massiv[rsp] << '\n';
        }
        outSave << "Всего чисел: " << save_position.size() << '\n';
        outSave << '\n';
        outSave.close();

        outTime.open("time.txt", ios::app);
        for (size_t rt = 0; rt < save_k.size(); ++rt) {
            outTime << "Для k = " << save_k[rt] << '\n';
            outTime << "Время, затрачиваемое функцией: " << save_time[rt] << " микросекунды" << '\n';
            outTime << '\n';
        }
        outTime.close();
    }
}