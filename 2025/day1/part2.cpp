#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream file("D:/Outsource/advent-of-code/2025/day1/input.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }
    int point = 50;
    const int MOD = 100;
    int ans = 0;
    string line;
    while (getline(file, line))
    {
        char direction = line[0];
        int distance = stoi(line.substr(1));
        ans += distance / MOD;
        int remainder = distance % MOD;
        if (direction == 'L')
        {
            if(remainder >= point && point != 0){
                ans += 1;
            }
            point = (point - remainder + MOD) % MOD;
        }
        else if (direction == 'R'){
            if(remainder + point >= MOD && point != 0){
                ans += 1;
            }
            point = (point + remainder) % MOD;
        }
    }
    cout << ans << endl;
    file.close();
    return 0;
}