//template for advent of code problems
#include <bits/stdc++.h>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    
    ifstream file("D:/Outsource/advent-of-code/2025/day??/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    long long p1 = 0;
    long long p2 = 0;

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();

    auto end_p1 = chrono::high_resolution_clock::now();
    auto duration_p1 = chrono::duration_cast<chrono::microseconds>(end_p1 - start).count();

    auto end_p2 = chrono::high_resolution_clock::now();
    auto duration_p2 = chrono::duration_cast<chrono::microseconds>(end_p2 - start).count();

    
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
    cout << "Time taken for Part 1: " << duration_p1 << " μs" << endl;
    cout << "Time taken for Part 2: " << duration_p2 << " μs" << endl;

    return 0;
}