#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <vector>
using namespace std;

class UnionFind {
public:
    vector<int> parents, ranks, sizes;

    UnionFind(int n) {
        parents.resize(n);
        ranks.resize(n, 0);
        sizes.resize(n, 1);
        for (int i = 0; i < n; i++)
            parents[i] = i;
    }

    bool merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY){
            return false;
        }
        if (ranks[rootX] < ranks[rootY]) {
            parents[rootX] = rootY;
            sizes[rootY] += sizes[rootX];
        } else if (ranks[rootX] > ranks[rootY]) {
            parents[rootY] = rootX;
            sizes[rootX] += sizes[rootY];
        } else {
            parents[rootX] = rootY;
            ranks[rootY]++;
            sizes[rootY] += sizes[rootX];
        }
        return true;
    }

    int getSize(int x) {
        return sizes[find(x)];
    }

    int find(int x) {
        if (x != parents[x])
            parents[x] = find(parents[x]);
        return parents[x];
    }
};

#endif
