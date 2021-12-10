/*
PRIM'S ALGORITHM
Finds the minimum spanning tree for a weighted undirected graph.

Fernanda Nava Moya - A01023896
13/10/2021
*/

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <bits/stdc++.h>

using namespace std;

// function to sort answer vector by weight
bool sortMST(const vector<int>& a, const vector<int>& b){
    return (a[2] < b[2]);
}

// method for MTS with Prim's Algorithm
void prim(int E, vector<vector<int>> edge) {
    int V = 3; 
    set<int> vertex; // set of vertex
    map<int,vector<pair<int,int>>> edges; // map to store origin of edge and make a pair of destination and weight

    // for each edge t
    for(int i = 0; i < E; i++) {
        int origin = edge[i][0]; // get origin
        int destination = edge[i][1]; // get destination
        int weight = edge[i][2]; // get weight
        // add in map as a key the origin and make pair of destination and weight
        edges[origin].push_back(make_pair(destination,weight));
        // add in map as a key the destination and make pair of origin and weight
        edges[destination].push_back(make_pair(origin,weight));
        vertex.insert(origin); // insert in set the origin
        vertex.insert(destination); // insert in set the destination
    }

    set<int> S; // with vertex included
    set<int> Q(vertex); // not vertex included

    // map to store min weight for edge with adjacent vertex of included vertices
    map<int,pair<int,int>> cost;
    // map to store MST's edges
    map<int, pair<int,int> > mst;

    // init all initial weight cost to maximum value
    for(auto q : Q) {
        // male pair for each weight cost
        cost[q] = make_pair(NULL, INT_MAX);
    }

    // set vertex '0' as a starting node
    S.insert(0);
    Q.erase(Q.find(0));

    // set minimum cost for all vertices adjacent to already-included vertices
    while(Q.size() > 0) {
        // iterate through destination
        for(auto i : S) {
            for(auto edge : edges[i]) {
                // if the origin is not in set 'S'
                if(S.find(edge.first) == S.end()) {                                                      
                    // find minimum edge's weight that connected to adjacent vertex and set it into weight cost's map
                    if(edge.second < cost[edge.first].second) {
                        cost[edge.first] = make_pair(i, edge.second); // create key and pair
                    }
                }
            }
        }
        // find not-yet adjacent vertex that contains minimum weight
        pair<int,int> mincost_vertex = make_pair(NULL, INT_MAX); // create pair for minimum weight cost
        int adj_vertex = -1; // store adjacent vertex that contains minimum weight

        // iterate through each weight cost
        for(auto each_cost : cost) {
            if(S.find(each_cost.first) == S.end()) {
                // find adjacent vertex that contains minimum weight
                if(each_cost.second.second < mincost_vertex.second) {
                    mincost_vertex = each_cost.second; 
                    adj_vertex = each_cost.first;
                }
            }
        }

        // store new included MST's vertices for later print-out
        mst[adj_vertex] = mincost_vertex;
        // add choosen adjacent vertex into already included vertex list
        S.insert(adj_vertex);
        // remove choosen adjacent vertex from remaining vertex list
        Q.erase(Q.find(adj_vertex));
    }

    // print out MST
    vector<vector<int>> ans;
    for(auto result : mst) {
        ans.push_back({result.first, result.second.first, result.second.second});
    }
    // sort answer vector
    sort(ans.begin(), ans.end(), sortMST);
    // print origin, destination and weight
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i][1] << " " << ans[i][0] << " " << ans[i][2] << endl;
    }
}

int main(int argc, char *argv[]) {
    // get number of vertex
    int num = stoi(argv[1]);

    // create vectors for origin, destination and weight
    vector<int> origin, destination, weight;

    int counter = 1;
    // get origin values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        origin.push_back(stoi(argv[i]));
    }
    // get destination values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        destination.push_back(stoi(argv[counter]));
    }
    // get weight values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        weight.push_back(stoi(argv[counter]));
    }

    // store origin, destination and weights values ordered for each vertex
    vector<vector<int>> ans;
    for(int i = 0; i < num; i++) {
        ans.push_back({origin[i],destination[i],weight[i]});
    }
    
    // get minimum spanning tree
    prim(16,ans);
    
    return 0;
}