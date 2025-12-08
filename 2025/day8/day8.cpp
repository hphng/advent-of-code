//template for advent of code problems
#include <bits/stdc++.h>
#include "UnionFind.h"
using namespace std;

struct JunctionBox
{
    vector<int> coordinate;
    JunctionBox(const vector<int>& coordinate)
        : coordinate(coordinate) {
    }

    void print() const {
        cout << coordinate[0] << " " << coordinate[1] << " " << coordinate[2] << endl;
    }

    double distanceToAnother(JunctionBox compareBox) {
        if (coordinate.size() != compareBox.coordinate.size()) {
            cerr << "Error: JunctionBoxes have different dimensions!" << endl;
            return -1; // or throw exception
        }
        double square = 0.0;
        for (int i = 0; i < coordinate.size(); i++) {
            square = square + (coordinate[i] - (double) compareBox.coordinate[i]) * (coordinate[i] - (double) compareBox.coordinate[i]);
        }

        double result = sqrt(square);

        return result;
    }
};

long long threeLargestSizesMultiply(const vector<JunctionBox>& inputs) {
    long long ans = 1;
    int n = inputs.size();
    UnionFind uf(n);

    //calculate distance between the boxes
    //distances, first box, second box
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>> > pq;
    for (int i = 0; i < n; i++) {
        JunctionBox first = inputs[i];
        for (int j = i + 1; j < n; j++) {
            JunctionBox second = inputs[j];
            double distance = first.distanceToAnother(second);
            pq.push({ distance, {i, j} });
        }
    }
    //1000 pairs
    for (int i = 1; i <= 1000; i++) {
        auto x = pq.top();
        pq.pop();
        double distance = x.first;
        int firstIndex = x.second.first;
        int secondIndex = x.second.second;
        // cout << distance << " " << firstIndex << " " << secondIndex << endl;
        uf.merge(firstIndex, secondIndex);
    }

    priority_queue<int> maxSizes;
    unordered_set<int> unique;
    for (int i = 0; i < n; i++) {
        if(uf.find(i) != i){
            continue;
        }
        int curSize = uf.getSize(i);
        maxSizes.push(curSize);
    }

    //top 3 circuit
    for (int i = 1; i <= 3; i++) {
        ans = ans * maxSizes.top();
        cout << maxSizes.top() << endl;
        maxSizes.pop();
    }

    return ans;
}

long long lastConnectedPair(const vector<JunctionBox>& inputs) {
    long long ans = 1;
    int n = inputs.size();
    UnionFind uf(n);

    //calculate distance between the boxes
    //distances, first box, second box
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>> > pq;
    for (int i = 0; i < n; i++) {
        JunctionBox first = inputs[i];
        for (int j = i + 1; j < n; j++) {
            JunctionBox second = inputs[j];
            double distance = first.distanceToAnother(second);
            pq.push({ distance, {i, j} });
        }
    }
    int numberofDisconnected = n;
    while(numberofDisconnected > 1){
        auto x = pq.top();
        pq.pop();
        double distance = x.first;
        int firstIndex = x.second.first;
        int secondIndex = x.second.second;
        // cout << distance << " " << firstIndex << " " << secondIndex << endl;
        if(uf.merge(firstIndex, secondIndex)){
            numberofDisconnected--;
        }
        JunctionBox firstBox = inputs[firstIndex];
        JunctionBox secondBox = inputs[secondIndex];
        ans = firstBox.coordinate[0] * secondBox.coordinate[0];
    }
    return ans;
}
int main() {
    auto start = chrono::high_resolution_clock::now();

    ifstream file("D:/Outsource/advent-of-code/2025/day8/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    long long p1 = 0;
    long long p2 = 0;

    vector<JunctionBox> inputs;
    string line;
    while (getline(file, line)) {
        // cout << line << endl;
        stringstream ss(line);
        string token;
        vector<int> boxCoordinate;
        while (getline(ss, token, ',')) {
            int num = stoi(token);
            boxCoordinate.push_back(num);
        }
        JunctionBox newBox = JunctionBox(boxCoordinate);
        // newBox.print();
        inputs.push_back(newBox);
    }

    file.close();

    p1 = threeLargestSizesMultiply(inputs);
    auto end_p1 = chrono::high_resolution_clock::now();
    auto duration_p1 = chrono::duration_cast<chrono::microseconds>(end_p1 - start).count();

    p2 = lastConnectedPair(inputs);

    auto end_p2 = chrono::high_resolution_clock::now();
    auto duration_p2 = chrono::duration_cast<chrono::microseconds>(end_p2 - start).count();


    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;

    cout << "Time taken for Part 1: " << duration_p1 << " μs" << endl;
    cout << "Time taken for Part 2: " << duration_p2 << " μs" << endl;

    return 0;
}