#pragma once

// ���������� ������� ����� b i-��� �� ����
long long b_i(long long x, long long m, long long n) {
    long long b_i;
    b_i = ((long long)pow(x + m, 2) - n);
    return b_i;
}

// ���������� ����� �� �������� �����
long long sqrt_m(long long n) {
    long long m;
    m = sqrt(n);
    return m;
}

// ������� ��� ��������, ������������� �� ������ �������� �����
bool isPrime(long long n) {
    // ��������� 0 � 1 �� �������� �������� �������
    // ���������� �������� false.
    if (n == 1 || n == 0) {
        return false;
    }

    // ��������� ���� �� 2 ��
    // ���������� ������ �� n.
    for (long long i = 2; i * i <= n; i++) {
        // ���� ����� ������� �� i,
        // �� n �� �������� ������� ������.
        if (n % i == 0)
            return false;
    }

    // � ��������� ������ n - ������� �����.
    return true;
}

// ������� ������� ���������� ����������� �� ����� �� ��������� ����,
// ����� ����� �� ������� ��������� � ���������� ���������
bool Good(long long n, std::vector<long long> FB, int k) {
    if (n < 0)
        n = n * (-1);

    int i = 1;

    while ((i < k) && (n != 1))
        if (n % FB[i] == 0)
            n = n / FB[i];
        else
            i++;

    if (n == 1)
        return true;
    else
        return false;
}