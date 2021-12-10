/*
Floyd-Warshall's ALGORITHM
Finds the minimum spanning tree for a weighted undirected graph.

Fernanda Nava Moya - A01023896
22/10/2021
*/

#include <iostream>
#include <climits>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;
 
// Define infinity
#define I INT_MAX

// function to sort answer vector
bool sortMST(const vector<int>& a, const vector<int>& b){
    return (a[3] < b[3]);
}
 

int i =0 ; // counter for recurse function
unordered_map<int, vector<int>> map_;  // map to store path
int a = 0; // variable that stores the node before the destination
int counter = 0; // counter of insertion nodees
// Recursive function to print path of given, vertex `u` from source vertex `v`
int printPath(vector<vector<int>> matrix, vector<vector<int>> path, int v, int u)
{
    // base case
    if (path[v][u] == v) {
        return 0;
    }
    // call path function recursively
    printPath(matrix, path, v, path[v][u]);
    i++;
    // adds original source node to map
    if(i == 1) {
        map_[v] = {path[v][u], matrix[v][path[v][u]], counter++};
        // returns the node before
        return path[v][u];
    }
    // if the return value is not 0 then adds the node to the map
    if(printPath(matrix,  path, v, path[v][u]) != 0) {
        // adds node to map
        map_[printPath(matrix, path, v, path[v][u])] = {path[v][u], matrix[printPath(matrix, path, v, path[v][u])][path[v][u]], counter++};
        // saves the node before of the destination node
        a = path[v][u];
    }
     // returns the node before
    return path[v][u];
}
 
// Function to print the shortest cost with path information between all pairs of vertices
void printSolution(vector<vector<int>> matrix, vector<vector<int>> path, int s, int d)
{
    // calls recursive function to get path
    printPath(matrix, path, s, d);
    // add destination node to map with the node before stores value in 'a'
    map_[a] = {d, matrix[a][d], counter++};
}
 
// Function with Floyd–Warshall algorithm
void floydWarshall(vector<vector<int>> adjMatrix, int num) {

    vector<vector<int>> path, matrix;
    vector<int> emptyVector = {};
    path.push_back(emptyVector);
    matrix.push_back(emptyVector);

    // put all values of the matrix to INT_MAX
    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            path[i].push_back(I);
            matrix[i].push_back(I);
            path.push_back(emptyVector);
            matrix.push_back(emptyVector);
        }
    }
 
    // initializes all lists
    for (int v = 0; v < num; v++) {
        for (int u = 0; u < num; u++) {
            // initially, cost would be the same as the weight of the edge
            matrix[v][u] = adjMatrix[v][u]; 
            if (v == u) {
                path[v][u] = 0;
            }
            else if (matrix[v][u] != INT_MAX) {
                path[v][u] = v;
            }
            else {
                path[v][u] = -1;
            }
        }
    }
 
    // Floyd–Warshall algorithm
    for (int k = 0; k < num; k++) {
        for (int v = 0; v < num; v++) {
            for (int u = 0; u < num; u++) {
                // If vertex `k` is on the shortest path from `v` to `u`, then it updates the value of `matrix[v][u]` and `path[v][u]`
                if (matrix[v][k] != INT_MAX && matrix[k][u] != INT_MAX && matrix[v][k] + matrix[k][u] < matrix[v][u]) {
                    path[v][u] = path[k][u];
                    matrix[v][u] = matrix[v][k] + matrix[k][u];
                }
            } 
            // if diagonal elements become negative, the graph contains a negative-weight cycle
            if (matrix[v][v] < 0) {
                cout << "NO CYCLE FOUND!";
                return;
            }
        }
    } 
    // Print the shortest path between all pairs of vertices
    printSolution(matrix, path, 2, 5);
}
 
// Driver code
int main(int argc, char *argv[]) {
    // get number of vertex
    int num = stoi(argv[1]);

    // create vectors for origin, destination and weight
    vector<int> source, destination, cost;

    int counter = 1;
    // get origin values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        source.push_back(stoi(argv[i]));
    }
    // get destination values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        destination.push_back(stoi(argv[counter]));
    }
    // get cost values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        cost.push_back(stoi(argv[counter]));
    }

    // store origin, destination and weights values ordered for each vertex
    vector<vector<int>> w;
    for(int i = 0; i < num; i++) {
        w.push_back({source[i],destination[i],cost[i]});
    }    
    vector<vector<int>> adjMatrix;
    vector<int> emptyVector = {};
    adjMatrix.push_back(emptyVector);

    // put all values of the matrix to INT_MAX
    for (int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            adjMatrix[i].push_back(I);
            adjMatrix.push_back(emptyVector);
        }
    }
    // add the resived values into the matrix 
    for(int i = 0; i < w.size(); i++) {
        adjMatrix[w[i][0]][w[i][1]] = w[i][2];
    }
    
    // Run Floyd–Warshall algorithm
    floydWarshall(adjMatrix, num);
    
    // create ans vector
    vector<vector<int>> ans;
    for(auto x: map_) {
        ans.push_back({x.first, x.second[0], x.second[1], x.second[2]});
    }

    // sort ans vector according to insertion value
    sort(ans.begin(), ans.end(), sortMST);
    // print all values of ans vector 
    for(auto i: ans) {
        cout << i[0] << " " << i[1] << " " << i[2] << endl;
    }
 
    return 0;
}
