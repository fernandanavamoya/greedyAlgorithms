#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// class for an edge in a graph
class Edge{
public:
    int source, destination, weight;
    Edge(int s, int d, int w) {
        source = s;
        destination = d;
        weight = w;
    }
};

// class for a graph
class Graph{
public:
    vector<Edge> edges; // vector with all edges of the graph

    // method that adds an edge to the undirected graph
    void addEdge(int s, int d, int w) {
        Edge obj(s, d, w); // create an edge  
        edges.push_back(obj); // add edge to the edges vector
    }
};

//declare a displayMST function to define it later
void displayMST(const vector<Edge> &);

//class for finding MST in the graph
class Kruskal {
public:
    int totalVertex; // total vertices
    vector<pair<int,int>> subsets; // vector of pais where <parent,rank>
    vector<Edge> mst; // vector of edges of minimum spanning tree

    Kruskal(int tV) {
        this->totalVertex = tV;

        subsets.resize(tV); // resize subsets to total vertices

        for(int i = 0; i < tV; i++) {
            subsets[i].first = i; //set parent to index
            subsets[i].second = 0; //set rank to zero
        }
    }

    // function that compares weight of edges in order to sort them in increasing order
    static bool sortByWeight(Edge &a, Edge &b) {
        return (a.weight < b.weight);
    }

    // function that creates a minimum spanning tree
    void createMST(Graph& graph) {
        //sort the edges of the graph by weight in increasing order
        sort(graph.edges.begin(), graph.edges.end(), sortByWeight);

        int countVertex = 0; // total edges = total vertixe - 1
        int countEdge = 0;

        // iterate through the vector of edges in the graph
        while(countEdge < (totalVertex-1) && countVertex < graph.edges.size()) {
            //get current edge
            Edge currEdge = graph.edges[countVertex++];

            // find the absolute parent 
            int source = find(currEdge.source); // get current edge source
            int dest = find(currEdge.destination); // get current edge destination
            
            // the sorce is not the same as the destination, not a cyrcle,
            // then it adds the edge to the vector of edges and makes an union
            if(source != dest) {  
                mst.push_back(currEdge); // add current edge to edges vector
                makeUnion(source, dest); // create a union (edge) between the two vertex
            }
        }
        displayMST(mst); // show mst
    }

    // recursive function to find the absolute parent (root)
    int find(int target) {
        // if index is not equal to parent value call find function with current parent value
        if(subsets[target].first != target) { 
            subsets[target].first = find(subsets[target].first);
        }
        return subsets[target].first;
    }

    // function that creates a union (edge) between the two vertex
    void makeUnion(int x, int y) {   
        // get absolute parent (root) of both vertex 
        int x_root = find(x);
        int y_root = find(y);

        // if-else for rank comparison & update parent-rank values
        if(subsets[x_root].second < subsets[y_root].second) { 
            subsets[x_root].first = y_root; // update parent
        }
        else if(subsets[x_root].second > subsets[y_root].second) {
            subsets[y_root].first = x_root; // update parent
        }
        else {
            subsets[x_root].first = y_root; // create union (edge)
            subsets[y_root].second++; // increment rank
        }
    }
};

// funciton to display all edges of MST & total cost
void displayMST(  const vector<Edge>&  edges)
{ 
    int totalMinimumCost=0;
    cout<<"All MST edges [source - destination = weight]\n";

    for( auto edge : edges) {
        cout<<edge.source<<" - "<<edge.destination<<" = "<<edge.weight<<'\n';

        totalMinimumCost+=edge.weight;
    }
    cout<<"total minimum cost = "<<totalMinimumCost<<endl;
}


int main() {
    Graph g;
    //add edeges to graph
    g.addEdge(0, 1, 50);
    g.addEdge( 0 , 2, 10);
    g.addEdge(0, 3, 50);
    g.addEdge(1, 4, 30);
    g.addEdge(3, 4, 100);
    g.addEdge(2, 4, 100);

    //create and object of kruskal class
    Kruskal graph(5);

    //call kruskal class's member function to find MST
    graph.createMST( g);

    return 0;
}
