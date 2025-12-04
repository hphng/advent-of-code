#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

vector<pair<int, int>> DIRECTIONS{ {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, -1}, {-1, 1} };

int p1_rolls(vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].length();
    int numberOfRolls = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '@') {
                continue;
            }
            //each roll, check around
            int count = 0;
            for (int d = 0; d < DIRECTIONS.size(); d++) {
                int x = i + DIRECTIONS[d].first;
                int y = j + DIRECTIONS[d].second;

                if (x >= m || x < 0 || y >= n || y < 0 || grid[x][y] != '@') {
                    continue;
                }
                count++;
            }

            if (count < 4) {
                numberOfRolls++;
            }
        }
    }
    return numberOfRolls;
}

int p2_rolls(vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].length();\

    vector<vector<int>> surrounding(m, vector<int>(n, 0));
    queue<pair<int, int>> removedRolls;
    //add initail rolls that can be removed + calculate the rolls surrounding
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '@') {
                surrounding[i][j] = -1;
                continue;
            }
            //each roll, check around
            int count = 0;
            for (int d = 0; d < DIRECTIONS.size(); d++) {
                int x = i + DIRECTIONS[d].first;
                int y = j + DIRECTIONS[d].second;

                if (x >= m || x < 0 || y >= n || y < 0 || grid[x][y] != '@') {
                    continue;
                }
                count++;
            }
            surrounding[i][j] = count;

            if (count < 4) {
                removedRolls.push({i, j});
                surrounding[i][j] = -1;
            }
        }
    }
    int ans = 0;
    //bfs
    while(!removedRolls.empty()){
        ans++;
        auto [x, y] = removedRolls.front();
        // cout << x << " " << y << endl;
        removedRolls.pop();
        surrounding[x][y] = -1;
        for(int d = 0; d < DIRECTIONS.size(); d++){
            int newX = x + DIRECTIONS[d].first;
            int newY = y + DIRECTIONS[d].second;
            if(newX < 0 || newX >= m || newY < 0 || newY >= n || surrounding[newX][newY] == -1){
                continue;
            }
            surrounding[newX][newY]--;
            if(surrounding[newX][newY] < 4){
                removedRolls.push({newX, newY});
                surrounding[newX][newY] = -1;
            }
        }
    }
    return ans;
}
int main() {
    ifstream file("D:/Outsource/advent-of-code/2025/day4/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    string line;
    vector<string> lines;
    int p1 = 0;
    int p2 = 0;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    p1 = p1_rolls(lines);
    p2 = p2_rolls(lines);
    cout << "part 1:" << p1 << endl;
    cout << "part 2:" << p2 << endl;
    return 0;
}