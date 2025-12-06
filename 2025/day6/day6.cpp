//template for advent of code problems
#include <bits/stdc++.h>
using namespace std;

long long p1_homework(vector<vector<string>>& inputs) {
    long long result = 0;
    int n = inputs.size();
    int m = inputs[0].size();
    for (int j = 0; j < m; j++) {
        long long cur = 0;
        if (inputs[n - 1][j] == "+") {
            cur = 0;
            for (int i = 0; i < n - 1; i++) {
                cur += stoll(inputs[i][j]);
            }
        } else if (inputs[n - 1][j] == "*") {
            cur = 1;
            for (int i = 0; i < n - 1; i++) {
                cur *= stoll(inputs[i][j]);
            }
        }
        result += cur;
    }
    return result;
}

long long p2_homework(vector<string>& inputs) {
    long long result = 0;
    int n = inputs.size();
    int m = inputs[0].length();
    const int ADD = 1;
    const int MULT = 2;
    int operation = 0;

    long long cur = 0;
    for(int j = 0; j < m; j++) {
        if(inputs[n-1][j] == '+') {
            operation = ADD;
        } else if(inputs[n-1][j] == '*') {
            operation = MULT;
        }

        string numStr = "";
        bool isSpace = true;
        for(int i = 0; i < n - 1; i++) {
            if(isdigit(inputs[i][j])){
                isSpace = false;
            }
            numStr += inputs[i][j];
        }

        if(isSpace) {
            // cout << cur << endl;
            result += cur;
            cur = 0;
            continue;
        }
        long long num = stoll(numStr);
        if(operation == ADD) {
            cur += num;
        } else if(operation == MULT) {
            if(cur == 0) cur = 1;
            cur *= num;
        }
    }
    result += cur;
    // cout << result << endl;
    return result;
}
    
int main() {
    auto start = chrono::high_resolution_clock::now();

    ifstream file("D:/Outsource/advent-of-code/2025/day6/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<vector<string>> inputs;
    vector<string> p2_inputs;

    long long p1 = 0;
    long long p2 = 0;

    string line;
    int row = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        p2_inputs.push_back(line);
        string token;
        inputs.push_back(vector<string>());
        while (ss >> token) {
            inputs[row].push_back(token);
            // cout << token << endl;
        }
        row++;
    }

    file.close();

    // cout << "Input has " << inputs.size() << " rows" << endl;
    // for (int i = 0; i < inputs.size(); i++) {
    //     cout << "Row " << i << ": ";
    //     for (auto& s : inputs[i]) {
    //         cout << s << " ";
    //     }
    //     cout << endl;
    // }

    p1 = p1_homework(inputs);

    auto end_p1 = chrono::high_resolution_clock::now();
    auto duration_p1 = chrono::duration_cast<chrono::microseconds>(end_p1 - start).count();

    p2 = p2_homework(p2_inputs);

    auto end_p2 = chrono::high_resolution_clock::now();
    auto duration_p2 = chrono::duration_cast<chrono::microseconds>(end_p2 - start).count();


    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
    cout << "Time taken for Part 1: " << duration_p1 << " ms" << endl;
    cout << "Time taken for Part 2: " << duration_p2 << " ms" << endl;

    return 0;
}