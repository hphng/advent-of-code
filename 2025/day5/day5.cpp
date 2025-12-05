#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> merge(vector<vector<long long>>& intervals){
    int n = intervals.size();
    sort(intervals.begin(), intervals.end(), [](const vector<long long>& p, const vector<long long>& q){
        return p[0] < q[0];
    });
    vector<vector<long long>> ans;
    vector<long long> compare = intervals[0];
    for(int i = 1; i < n; i++){
        const vector<long long>& cur = intervals[i];
        if(compare[1] < cur[0]){
            ans.push_back(compare);
            compare = cur;
            continue;
        }

        compare[0] = min(compare[0], cur[0]);
        compare[1] = max(compare[1], cur[1]); 
    }
    ans.push_back(compare);
    return ans;
}

bool isFresh(vector<vector<long long>>& intervals, long long query){
    int l = 0, r = intervals.size() - 1;
    while(l <= r){
        int mid = l + (r - l) / 2;
        if(intervals[mid][0] <= query && query <= intervals[mid][1]){
            return true;
        }
        else if(query < intervals[mid][0]){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    return false;
}

long long numberOfFreshIngredients(vector<vector<long long>>& intervals){
    long long total = 0;
    for(auto interval: intervals){
        total = total + (interval[1] - interval[0] + 1);
    }
    return total;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    ifstream file("D:/Outsource/advent-of-code/2025/day5/input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    string line;
    vector<vector<long long>> ranges;
    //get ranges
    while (getline(file, line)) {
        if(line.empty()) break;
        //the format is "x1-x2"
        string left_str = line.substr(0, line.find('-'));
        string right_str = line.substr(line.find('-') + 1);
        long long left = stoll(left_str);
        long long right = stoll(right_str);
        ranges.push_back({left, right});
    }
    vector<vector<long long>> sortedIntervals = merge(ranges);
    long long p2 = numberOfFreshIngredients(sortedIntervals);
    auto end_p2 = chrono::high_resolution_clock::now();
    auto duration_p2 = chrono::duration_cast<chrono::microseconds>(end_p2 - start).count();
    //PART 1
    long long p1 = 0;
    vector<long long> queries;
    //get queries
    while (getline(file, line)) {
        if (line.length() == 0) {
            continue;
        }
        long long query = stoll(line);
        if(isFresh(sortedIntervals, query)){
            p1++;
        }
        queries.push_back(query);
    }
    auto end_p1 = chrono::high_resolution_clock::now();
    auto duration_p1 = chrono::duration_cast<chrono::microseconds>(end_p1 - start).count();
    file.close();
    
    cout << "Part 1: " << p1 << endl;
    cout << "Part 2: " << p2 << endl;
    cout << "Time taken for Part 1: " << duration_p1 << " ms" << endl;
    cout << "Time taken for Part 2: " << duration_p2 << " ms" << endl;

    return 0;
}