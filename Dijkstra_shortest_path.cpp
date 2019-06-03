#include <iostream>
#include <climits>
#include <list>
#include <queue>
using namespace std;

void dijkstra_use_array(int graph[9][9], int src);
void addEdge_adjacencyList(list<pair<int, int>> graph[], int u, int v, int weight);
void dijkstra_use_list(list<pair<int, int>> graph[], int src);
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

	// Create an example graph in adjacency list form
	list<pair<int, int>> graph2[9];
	//create same graph as above
	addEdge_adjacencyList(graph2, 0, 1, 4);
	addEdge_adjacencyList(graph2, 0, 7, 8);
	addEdge_adjacencyList(graph2, 1, 2, 8);
	addEdge_adjacencyList(graph2, 1, 7, 11);
	addEdge_adjacencyList(graph2, 2, 3, 7);
	addEdge_adjacencyList(graph2, 2, 5, 4);
	addEdge_adjacencyList(graph2, 2, 8, 2);
	addEdge_adjacencyList(graph2, 3, 4, 9);
	addEdge_adjacencyList(graph2, 3, 5, 14);
	addEdge_adjacencyList(graph2, 5, 6, 2);
	addEdge_adjacencyList(graph2, 6, 7, 1);
	addEdge_adjacencyList(graph2, 6, 8, 6);
	addEdge_adjacencyList(graph2, 7, 8, 7);

	dijkstra_use_list(graph2, 0);
}
void dijkstra_use_array(int graph[9][9], int src)
{
	cout<<"using array implementation..."<<endl;
	int dist[9]; //The output array, dist[i] will be the shortest dist from vertex 0 to vertex i
	bool sptSet[9];  //boolean flags, sptSet[i] will be true if vertex i is already in the shortest path tree
	for(int i=0;i<9;++i)  //initialize both arrays
		dist[i] = INT_MAX, sptSet[i] = false;
	int parent[9] = {0,0,0,0,0,0,0,0,0}; // to store the 'parent node' to each vertext, not necessary if only we only need distance output

	//define a utility function
    // it picks vertex with minimum distance to source, and yet not in shortest path tree
	auto minDistance = [&dist, &sptSet](){
		int min_ix=-1, min=INT_MAX;
		for(int i=0;i<9;++i)
			if(sptSet[i]==false && dist[i]<min)
				min = dist[i], min_ix = i;
		return min_ix;
	};

	//define a utility function
	// it updates the distance array after vertex v is added into shortest path tree
	auto updateDistance = [&dist, &sptSet, &graph, &parent](int v){
		for(int i=0;i<9;++i)
			//update distance if the following conditions are met:
			// 1. vertex i is connected to vertext v
			// 2. vertex i is NOT in shortest path tree
			// 3. vertex i's current distance to source is greater than src->v + v->i
			if(!sptSet[i] && graph[v][i] !=0 && dist[v]+graph[v][i]<dist[i])
				dist[i] = dist[v]+graph[v][i], parent[i]=v;
	};
	dist[src]=0; //start with source vertex
	for(int i=0;i<9;++i)
	{
		int ix = minDistance(); //get vertex with minimum dist to src
		//cout<<ix<<endl;
		sptSet[ix]=true;
		updateDistance(ix);
	}
	//print out the resulting distance
	cout<<"Display results:"<<endl;
	cout<<"Vertex\tDistance from source\tShortest path"<<endl;
	for(int i=0;i<9;++i)
	{
		cout<<i<<"\t"<<dist[i]<<"\t";
		//restore the shortest path
		int v = i;
		cout<<v;
		while(parent[v]!=0)
			cout<<"<-"<<parent[v], v=parent[v];

		cout<<"<-"<<0<<endl;
	}

//	for(auto v:parent)
//		cout<<v<<endl;
}

void addEdge_adjacencyList(list<pair<int, int>> graph[], int u, int v, int weight)
{
	graph[u].push_back(make_pair(v, weight));
	graph[v].push_back(make_pair(u, weight));
}

void dijkstra_use_list(list<pair<int, int>> graph[], int src)
{
	// use min heap (priority_queue) to implement
	// here i use priority_queue,
	// another way to implement is to use <algorith> min_element while store the distances still in a list
	// e.g, list<int>::iterator i=min_element(dist.begin(), dist.end())
	//      do something, then: dist.remove(i);
	cout<<"using priority_queue implementation..."<<endl;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> dist;
	bool sptSet[9]; //boolean flags, sptSet[i] will be true if vertex i is already in the shortest path tree
	for(auto &i:sptSet) i=false;
	int shortestPathDist[9]; //store the shortest dist
	for(auto &i:shortestPathDist) i=INT_MAX;
	int parent[9] = {0,0,0,0,0,0,0,0,0}; // to store the 'parent node' to each vertext, not necessary if only we only need distance output
	dist.push(make_pair(0, src));
	while(!dist.empty())
	{
		// fetch weight-vertex from top of the min heap
		pair<int, int> tmpPair = dist.top();
		dist.pop();
		int shortestDist = tmpPair.first;
		int v = tmpPair.second;
		//if this vertex were not previously included in shortest path tree
		if(sptSet[v] == false)
		{
			sptSet[v] = true;
			shortestPathDist[v] = shortestDist;
		}
		//push adjacent vertices into heap, if they were not traversed yet.
		for(auto cit = graph[v].cbegin(); cit!=graph[v].cend(); cit++)
		{
			int nextV = cit->first;
			int weight = cit->second;
			if(sptSet[nextV]==false)
				dist.push(make_pair(shortestDist+weight, nextV));
		}
	}

	//print out the resulting distance
	cout<<"Display results:"<<endl;
	cout<<"Vertex\tDistance from source\tShortest path"<<endl;
	for(int i=0;i<9;++i)
	{
		cout<<i<<"\t"<<shortestPathDist[i]<<"\t";
//		//restore the shortest path
//		int v = i;
//		cout<<v;
//		while(parent[v]!=0)
//			cout<<"<-"<<parent[v], v=parent[v];
//
		cout<<"<-"<<0<<endl;
	}

}
