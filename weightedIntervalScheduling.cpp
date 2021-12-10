/*WEIGHTED INTERVAL SCHEDULING*/

#include <bits/stdc++.h>
#include <vector>

using namespace std;

// sorts tasks by finish time
bool sortByTime (const vector<int>& a, const vector<int>& b) {
    return (a[2] < b[2]);
}


 /* Gets the next compatible task by comparing the finish time of the one before and the 
 start time of the current one, using iterative binary search*/
int findP (const vector<vector<int>> tasks, int current) {
    int left = 0, right = current - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (tasks[mid][2] <= tasks[current][1]) {
            if (tasks[mid + 1][2] <= tasks[current][1])
                left = mid + 1;
            else
                return mid+1;
        }
        else 
            right = mid - 1;
    }
    return 0; 
}

// a[0] = [index, start, finish, weight]
vector<int> weightedIntervalScheduling (vector<vector<int>> tasks) {
    // sort taks by finish time
    sort(tasks.begin(), tasks.end(), sortByTime); // O( n log n) 

    vector<int> weight, p;
    vector<int> OPT(tasks.size(), 0);
    int temp;

    for (int i = 0; i <tasks.size(); i++) {
        weight.push_back(tasks[i][3]);
        temp = findP(tasks,i);
        p.push_back(temp);
    }

    int optimal = 0, index = 0;
    for (int i = 0; i < tasks.size(); i++) {
        OPT[i+1] = max(weight[i] + OPT[p[i]], OPT[i]);
        if (optimal != OPT[i+1]) {
            optimal = OPT[i+1];
            index = i+1;
        }
    }

    vector<int> solution;
    solution.push_back(weight[index-1]);
    solution.push_back(tasks[p[index-1]-1][3]);
    return solution;
}

int main() {
    vector<vector<int>> tasks;
    tasks.push_back({1,0,3,3});
    tasks.push_back({2,1,4,2});
    tasks.push_back({3,0,5,4});
    tasks.push_back({4,3,6,1});
    tasks.push_back({5,4,7,2});
    tasks.push_back({6,3,9,5});
    tasks.push_back({7,5,10,2});
    tasks.push_back({8,8,10,1});

    vector<int> solution = weightedIntervalScheduling(tasks);

    for (int i = 0; i < solution.size(); i++) {
        cout << solution[i] << " ";
    }
    return 0;
}
