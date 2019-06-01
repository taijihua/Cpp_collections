#include <iostream>
#include <climits>
using namespace std;

void dijkstra_use_array(int graph[9][9], int src);
int main()
{
	// Create an example graph in adjacency matrix form
	int graph[9][9] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
            {4, 0, 8, 0, 0, 0, 0, 11, 0},
            {0, 8, 0, 7, 0, 4, 0, 0, 2},
            {0, 0, 7, 0, 9, 14, 0, 0, 0},
            {0, 0, 0, 9, 0, 10, 0, 0, 0},
            {0, 0, 4, 14, 10, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 1, 6},
            {8, 11, 0, 0, 0, 0, 1, 0, 7},
            {0, 0, 2, 0, 0, 0, 6, 7, 0}
           };
	//method 1. use arrays for the algorithm
	// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
	dijkstra_use_array(graph, 0);
}
void dijkstra_use_array(int graph[9][9], int src)
{
	cout<<"using array implementation..."<<endl;
	int dist[9]; //The output array, dist[i] will be the shortest dist from vertex 0 to vertex i
	bool sptSet[9];  //boolean flags, sptSet[i] will be true if vertex i is already in the shortest path tree
	for(int i=0;i<9;++i)  //initialize both arrays
		dist[i] = INT_MAX, sptSet[i] = false;

	//define a utility function
    // it picks vertex with minimum distance to source, and yet not in shortest path tree
	auto minDistance = [dist, sptSet](){
		int min_ix=-1, min=INT_MAX;
		for(int i=0;i<9;++i)
			if(sptSet[i]==false && dist[i]<min)
				min = dist[i], min_ix = i;
		return min_ix;
	};

	//define a utility function
	// it updates the distance array after vertex v is added into shortest path tree
	auto updateDistance = [&dist, sptSet, graph](int v){
		for(int i=0;i<9;++i)
			//update distance if the following conditions are met:
			// 1. vertex i is connected to vertext v
			// 2. vertex i is NOT in shortest path tree
			// 3. vertex i's current distance to source is greater than src->v + v->i
			if(!sptSet[i] && graph[v][i] !=0 && dist[v]+graph[v][i]<dist[i])
				dist[i] = dist[v]+graph[v][i];
	};
	dist[src]=0; //start with source vertex
	for(int i=0;i<9;++i)
	{
		for(int val:dist)
			cout<<val<<endl;
		int ix = minDistance(); //get vertex with minimum dist to src
		cout<<ix<<endl;
		sptSet[ix]=true;
		updateDistance(ix);
	}
	//print out the resulting distance
	cout<<"Display results:"<<endl;
	for(int i=0;i<9;++i)
		cout<<i<<" "<<dist[i]<<endl;
}
