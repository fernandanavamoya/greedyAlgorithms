/*
COIN CHANGE PROBLEM:
Goal: given some currency denominations {eg. US denomination: 1, 5, 10, 25, 100}, 
devise a method to pay amount to customer using fewest coins.
*/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<int> cashierAlgorithm(int x, vector<int> coins) {
    sort(coins.begin(), coins.end(), greater<int>());
    vector<int> result;
    int count = 0;

    while (x > 0) {
        int k = coins[count];
        if(k > x) {
            count++;
        }
        else {
            x -= k;
            result.push_back(k);
        }
    }
    if(result.size() == 0) cout << "NO SOLUTION" << endl;
    return result;
}

int main() {
    vector<int> coins = {1, 5, 10, 25, 100};
    vector<int> solution = cashierAlgorithm(34, coins);

    for (auto i : solution) {
        cout << i << " ";
    }

    return 0;
}