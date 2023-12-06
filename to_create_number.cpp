#include <iostream>
#include <random>
#include <fstream>
#include <string>

using namespace std;

// ���� �� �������� ��������������
// �������� ������� ��� ���������� ���������� ���������� � �������.
// �� ���������� (x^ y) % p
int power(int x, unsigned int y, int p) {
    int res = 1; // ���������������� ���������
    x = x % p; // �������� x, ���� ��� ������ ��� ����� p

    while (y > 0) {
        // ���� y �������, �������� x �� ���������
        if (y & 1)
            res = (res * x) % p;

        // ����� y �����
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

// ��� ������� ���������� ��� ���� k ���������. �� ������������
// false, ���� n �������� ���������, � ���������� true, ���� n
// ��������, ������� �����.
// d - �������� �����, �����, ��� d *2 = n-1
// ��� ���������� r >= 1
bool miillerTest(int d, int n) {
    // �������� ��������� ����� � [2..n-2]
    // ������� ����� ���������, ��� n > 4
    int a = 2 + rand() % (n - 4);

    // ��������� a^d % n
    int x = power(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    // ����������� ��������� x � �������, ���� �� ���������� ���� �� ���������
    // �������� ��������� (1) d �� ��������� n-1 (2) (x^2) % n �� ����� 1 (3) (x^
    // 2) % n �� ����� n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    // ���������� ��������
    return false;
}

// �� ���������� false, ���� n �������� ���������, � ���������� true, ���� n
// �������� �������� ������� ������. k - ��� ������� ��������, �������
// ���������� ������� ��������. ����� ������� �������� k ��������� �� �������
// ��������.
bool isPrimeMillerRabin(int n, int k) {
    // ������� ������
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // ������� r �����, ��� n = 2^d * r + 1 ��� ���������� r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // ��������� �������� ���������� 'k' ���
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;

    return true;
}

// ������� �������� ���������� �����
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

// ������� ������ � test.txt
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