#include<iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

long long findLargestJoltage(const string& line, int length) {
    vector<int> banks;
    vector<int> ans (length, 0);
    for (auto c : line) {
        banks.push_back(c - '0');
    }
    if (banks.size() != line.length()) {
        cerr << "wrong!!";
        exit(1);
    }

    if(ans.size() > banks.size()){
        cerr << "not enough data";
        exit(1);
    }

    for(int i = 0; i < length; i++){
        int j;
        if(i == 0)
            j = 0;
        else
            j = ans[i-1]+1;
        ans[i] = j;
        for( ;j < banks.size() - length + i + 1; j++){
            if(banks[ans[i]] < banks[j]){
                ans[i] = j;
            }
        }
    }

    long long x = 0;
    for(int i = 0; i < length; i++){
        x = x* 10LL + (long long) banks[ans[i]];
    }
    cout << x << " : " << line << endl;
    return x;
}

/*
17383
*/

int main() {
    ifstream file("D:/Outsource/advent-of-code/2025/day3/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    string line;
    // if (!getline(file, line)) {
    //     cerr << "Error reading line!" << endl;
    //     return 1;
    // }
    long long sum = 0;

    while (getline(file, line)) {
        sum += findLargestJoltage(line, 12);
        // cout << line << endl;
    }
    cout << sum;
    return 0;
}