#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
using namespace std;
unordered_set<long long> p1_seen;

long long p1_invalidID(long long id) {
    if (p1_seen.count(id))
        return 0;
    string s = to_string(id);
    int n = s.size();
    if (n % 2 != 0)
        return 0;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n / 2 + i])
            return 0;
    }
    p1_seen.insert(id);
    return id;
}

unordered_set<long long> p2_seen;
unordered_set<long long> check;
long long p2_invalidID(long long id) {
    if (p2_seen.count(id))
        return 0;
    if (check.count(id))
        return 0;
    check.insert(id);
    string s = to_string(id);
    int n = s.size();
    if (n < 2)
        return 0;
    // now instead of first and second half, the invalid id can be formbed by multiple equal parts 121212, 233233233, 111111
    for (int len = 1; len <= n / 2; len++) {
        if (n % len != 0)
            continue;
        bool valid = true;
        string pattern = s.substr(0, len);
        
        // Check if the entire string is made of this pattern repeated
        for (int i = len; i < n; i += len) {
            if (s.substr(i, len) != pattern) {
                valid = false;
                break;
            }
        }

        if (valid) {
            p2_seen.insert(id);
            cout << "p2 invalid id: " << id << endl;
            return id;
        }
    }
    return 0;
}


int main() {

    ifstream file("D:/Outsource/advent-of-code/2025/day2/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    if (!getline(file, line)) {
        cerr << "File is empty!" << endl;
        return 1;
    }

    stringstream ss(line);
    string token;
    long long p1 = 0;
    long long p2 = 0;
    while (getline(ss, token, ',')) {
        // token format: X-Y
        int dashPos = token.find('-');
        long long start = stoll(token.substr(0, dashPos));
        long long end = stoll(token.substr(dashPos + 1));
        // cout << "Range: " << start << " to " << end << endl;
        for (long long id = start; id <= end; id++) {
            p1 += p1_invalidID(id);
            p2 += p2_invalidID(id);
        }
    }

    cout << p1 << endl;
    cout << p2 << endl;
    file.close();
    return 0;
}
