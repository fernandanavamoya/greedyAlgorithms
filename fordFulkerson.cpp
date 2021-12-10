/*
Ford-Fulkerson's ALGORITHM
Finds the maximum flow in a flow network.

Fernanda Nava Moya - A01023896
05/11/2021
*/
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define I INT_MAX

// BFS method that returns true if there's a path from source to target
bool bfs(vector<vector<int>> &resAdjMatrix, int source, int target, vector<int> &parent)
{
	// array for all nodes visited, initialized to false
    int len = resAdjMatrix.size();
    bool visited[len] = {false};

	// queue that checks each node
	queue<int> q;

	// push source into the queue and mark it as visited, it has no parent.
	q.push(source);
	visited[source] = true;
	parent[source] = -1;

	// while loop that will visit all vertex
	while (q.empty() == false) {
		int u = q.front(); // get front of queue
		q.pop(); // pop queue

		// for loop that check's all u's 
		for (int i = 0; i < len; i++) {
			int v = i;
            int capacity = resAdjMatrix[u][v];
            
            // if there is a neighbor that hasn't been visited, and the capacity is bigger than 0
            if(visited[v] == false && capacity > 0) {
                // Push the neighbor onto the queue, mark it's parent, and mark it as visited
				q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
		}
	}
	
	// If the target got visited, then we found a path to it
    if(visited[target] == true) return true;
	// if not visited it returns false
	return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(vector<vector<int>> &adjMatrix, int source, int target)
{
	// initialize flow to zero
	int maxFlow = 0;

	// residual graph, same as the original graph
	vector<vector<int>> resAdjMatrix;
	vector<int> emptyVector = {};

	int len = adjMatrix.size();

	for(int i = 0; i < len; i++) {
		resAdjMatrix.push_back(emptyVector);
		for (int j = 0; j < adjMatrix[i].size(); j++) {
			resAdjMatrix[i].push_back(adjMatrix[i][j]);
		}
	}

	// create an empty parent vectorfor BFS to store the augmenting path.
	vector<int> parent;
	for (int i = 0; i < len; i++) {
		parent.push_back(-1);
	}

	// The flow increases while there is a path from source to sink
	while(bfs(resAdjMatrix, source, target, parent) == true) {
		// find th max flow through the path found
		int pathFlow = I;
		// iterate though the path found
		int v = target;
		while(v != source) {
			// get parent
			int u = parent[v];
			// update the pathflow if it's smaller
			int capacity = resAdjMatrix[u][v];
			// get min between capacity and pathFlow
			pathFlow = min(pathFlow, capacity);
			// get next edge in tha path
			v = u;
		}

		// update the residual capacities of the edges and reverse edges
		v = target;
		while(v != source) {
			// get parent
			int u = parent[v];
			// update the capacity
			resAdjMatrix[u][v] -= pathFlow;
			resAdjMatrix[v][u] += pathFlow;
			// get next edge in the path
			v = u;
		}
		// add this path's flow to total max flow so far 
		maxFlow += pathFlow;
	}

	// return the overall flow
	return maxFlow;
}

// Driver program to test above functions
int main(int argc, char *argv[]) {
	// get number of vertex
    int num = stoi(argv[1]);

    // create vectors for origin, destination and weight
    vector<int> origin, destination, weight, nums;

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
	// get values of start and target
	nums.push_back(stoi(argv[counter+1])); // start 
	nums.push_back(stoi(argv[counter+2])); // target

	// store origin, destination and weights values ordered for each vertex
	vector<vector<int>> w;
    for(int i = 0; i < num; i++) {
        w.push_back({origin[i],destination[i],weight[i]});
    }    
    vector<vector<int>> adjMatrix;
    vector<int> emptyVector = {};

    // put all values of the matrix to INT_MAX
    for (int i = 0; i < num; i++) {
		adjMatrix.push_back(emptyVector);
        for(int j = 0; j < num; j++) {
            adjMatrix[i].push_back(0);
        }
    }
    // add the resived values into the matrix 
    for(int i = 0; i < w.size(); i++) {
        adjMatrix[w[i][0]][w[i][1]] = w[i][2];
    }

	// for(int i = 0; i < num; i++) {
	// 	for(int j = 0; j < num; j++) {
	// 		cout << adjMatrix[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	cout << fordFulkerson(adjMatrix, nums[0], nums[1]) << endl;

	return 0;
}
