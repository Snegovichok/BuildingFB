#pragma once

// Ќахождение второго числа b i-тых из пары
long long b_i(long long x, long long m, long long n) {
    long long b_i;
    b_i = ((long long)pow(x + m, 2) - n);
    return b_i;
}

// Ќахождение корн€ от большого числа
long long sqrt_m(long long n) {
    long long m;
    m = sqrt(n);
    return m;
}

// ‘ункци€ дл€ проверки, соответствует ли данные простому числу
bool isPrime(long long n) {
    // ѕоскольку 0 и 1 не €вл€ютс€ простыми числами
    // возвращает значение false.
    if (n == 1 || n == 0) {
        return false;
    }

    // «апустите цикл от 2 до
    // квадратный корень из n.
    for (long long i = 2; i * i <= n; i++) {
        // ≈сли число делитс€ на i,
        // то n не €вл€етс€ простым числом.
        if (n % i == 0)
            return false;
    }

    // ¬ противном случае n - простое число.
    return true;
}

// ‘ункции котора€ определ€ет разлогаетс€ ли число по факторной базе,
// делим число на простые множители и возвращает результат
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