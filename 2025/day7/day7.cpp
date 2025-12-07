//template for advent of code problems
#include <bits/stdc++.h>
using namespace std;

long long beamSplting(vector<string>& inputs) {
    long long ans = 0;
    int n = inputs.size();
    int m = inputs[0].length();
    queue<pair<int, int>> q;
    //find the starting point
    for (int j = 0; j < m; j++) {
        if (inputs[0][j] == 'S') {
            // inputs[1][j] = '|';
            q.push({ 1, j });
            break;
        }
    }

    //bfs by level
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x < 0 || x >= n - 1 || y < 0 || y >= m || inputs[x][y] == '|') {
            continue;
        }
        // cout << x << " " << y << endl;
        inputs[x][y] = '|';
        if (inputs[x + 1][y] == '^') {
            ans++;
            q.push({ x + 1, y - 1 });
            q.push({ x + 1, y + 1 });
        } else if (inputs[x + 1][y] == '.') {
            q.push({ x + 1, y });
        }
    }
    return ans;
}

long long numberOfTimeline(const vector<string>& inputs) {
    int n = inputs.size();
    int m = inputs[0].length();
    long long ans = 0;
    vector<vector<long long>> dp(n, vector<long long>(m, 0LL));
    for (int j = 0; j < m; j++) {
        if (inputs[0][j] == 'S') {
            dp[1][j] = 1;
        }
    }

    // for (auto x : dp) {
    //     for (auto y : x) {
    //         cout << y << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 1; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j] == 0) {
                continue;
            }
            //only index with > 0 value
            if (inputs[i + 1][j] == '^') {
                if (j > 0)
                    dp[i + 1][j - 1] += dp[i][j];
                if (j < m - 1)
                    dp[i + 1][j + 1] += dp[i][j];
            } else {
                dp[i+1][j] += dp[i][j];
            }
        }
    }

    for (int j = 0; j < m; j++) {
        ans += dp[n - 1][j];
    }
    return ans;
}
int main() {
    auto start = chrono::high_resolution_clock::now();

    ifstream file("D:/Outsource/advent-of-code/2025/day7/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    long long p1 = 0;
    long long p2 = 0;
    vector<string> inputs;
    string line;
    while (getline(file, line)) {
        // cout << line << endl;
        inputs.push_back(line);
    }

    file.close();
    //iteriate through inputs, draw the beam line
    p1 = beamSplting(inputs);

    auto end_p1 = chrono::high_resolution_clock::now();
    auto duration_p1 = chrono::duration_cast<chrono::microseconds>(end_p1 - start).count();

    //using inputs from p1
    p2 = numberOfTimeline(inputs);

    auto end_p2 = chrono::high_resolution_clock::now();
    auto duration_p2 = chrono::duration_cast<chrono::microseconds>(end_p2 - start).count();


    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
    cout << "Time taken for Part 1: " << duration_p1 << " ms" << endl;
    cout << "Time taken for Part 2: " << duration_p2 << " ms" << endl;

    return 0;
}