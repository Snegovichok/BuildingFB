#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Функция чтения из test.txt
vector<unsigned long long> read_number() {
    vector<unsigned long long> test_chisla;
    unsigned long long chislo;
    string line;
    ifstream in("test.txt");
    while (getline(in, line)) {
        istringstream iss(line);
        chislo = atoll(line.c_str());
        while (iss >> chislo) {
            test_chisla.push_back(chislo);
        }
    }
    in.close();
    return test_chisla;
}