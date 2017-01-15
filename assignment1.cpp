#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cctype>
#include<cassert>
#include<climits>
#include<cerrno>
#include<cfloat>
#include<ciso646>
#include<clocale>
#include<csetjmp>
#include<csignal>
#include<cstdarg>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cwchar>
#include<cwctype>
 
//containers
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<deque>
#include<set>
#include<complex>
#include<string>
#include<stack>
#include<bitset>
#include<istream>
#include<valarray>
 
//IOs
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>
#include<exception>
#include<ios>
#include<iosfwd>
#include<ostream>
#include<iterator>
#include<stdexcept>
#include<streambuf>
 
 
//algorithm & miscellaneous
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<limits>
#include<locale>
#include<memory>
#include<new>

using namespace std;
//Graph class implementing Adjacency List with help of STL map 
class Graph
{
	int V,E;
	//adjacency List is maintained using array of map where each pair is <destination vertex,weight of edge> 
	map<int,int> *adjList;
	
	public:
	bool weighted;
	//graph contructor
	Graph(int v,int e,bool w):V(v),E(e),weighted(w)
	{
		adjList=new map<int,int>[V];		
	}
	// utility function for checking cycle in graph
	bool _isCycle(int u, bool marked[], bool currentPath[])
	{
    		if(!marked[u])
    		{
        		marked[u] = true;
        		currentPath[u] = true;
 			map<int,int>::iterator i;
        		for(i = adjList[u].begin(); i!=adjList[u].end(); ++i)
        		{
				int v=i->first;
            			if ( !marked[v] && _isCycle(v,marked,currentPath))
                			return true;
            			else if (currentPath[v])
                			return true;
        		}
 
    		}
    		currentPath[u]=false;
    		return false;
	}
        //function checks whether there is cycle in graph or not 
	bool isCycle()
	{
    		bool *marked = new bool[V];
    		bool *currentPath = new bool[V];
    		memset(marked,0,V*sizeof(bool));
		memset(currentPath,0,V*sizeof(bool));
		bool cycle;
    		for(int i = 0; i < V; i++)
        		if (_isCycle(i, marked,currentPath))
            		{	
				delete marked;
				delete currentPath;
				return true;
					
 			}
		delete marked;
		delete currentPath;
		return false;
	}
	// utility function for finding topological sorting
	void _TPSort(int u, bool marked[], vector<int> &tps)
	{
    		marked[u] = true;
    		map<int,int>::iterator i;
    		for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
		{
			int v=i->first;
        		if (!marked[v])
           			_TPSort(v, marked, tps);
		}
 		tps.push_back(u);
	}
	// function for printing topological sorted order of graph	 
	void TPSort(vector<int> &tps)
	{
		bool *marked = new bool[V];
    		memset(marked,0,V*sizeof(bool));
		for (int u = 0; u < V; u++)
      		if (!marked[u])
        		_TPSort(u, marked, tps);
	        reverse(tps.begin(),tps.end());
		cout<<"\nTopological Sorting Order of All nodes\n";
		for(int i=0;i<tps.size();i++)
		{
			cout<<tps[i]<<"  ";
		}
		cout<<"\n";
	}
	// finding shortest path form source to all vertex of graph
	void weightedShortestPath(int source,vector<int> &tps)
	{
		int *distance=new int[V];
		int *parent=new int[V];
		for(int i=0;i<V;i++)
		{
			distance[i]=INT_MAX/2;
			parent[i]=-2;
		}
		distance[source]=0;
		parent[source]=-1;				
		for(int i=0;i<tps.size();i++)		
		{	
			int u=tps[i];			
			map<int,int>::iterator it;
			for(it=adjList[u].begin();it!=adjList[u].end();it++)
			{
				int v=it->first;
				int weight=it->second;
				if(distance[v]>distance[u]+weight)
				{
					distance[v]=distance[u]+weight;
					parent[v]=u;					
				}
			}
		}
		cout<<"\n\nDistance of all nodes in shortest path  "<<"\n";
		for(int i=0;i<V;i++)
			if(distance[i]>=INT_MAX/2)
				cout<<"INF ";
			else
				cout<<distance[i]<<"  ";

		cout<<"\n\nParent of all nodes in shortest path  "<<"\n";
		for(int i=0;i<V;i++)
			if(parent[i]==-2)
				cout<<"NIL ";
			else
				cout<<parent[i]<<"  ";	
		cout<<"\n";
		delete distance;
		delete parent;
	}
	
	//printing adjacency list of graph using friend function of class
	friend	ostream& operator<<(ostream &out,const Graph &g)
	{
		out<<"\nVertex= "<<g.V<<" Edges= "<<g.E<<"\n";
		out<<"\nAdjacency List of all Nodes\n";
		for(int i=0;i<g.V;i++)
		{	
			out<<i<<" ---->>  ";
			map<int,int>::iterator it;
			for(it=g.adjList[i].begin();it!=g.adjList[i].end();it++)
			{
				if(g.weighted)
					out<<"( "<< it->first <<" , "<<it->second<<" )  ";
				else
					out<< it->first <<" ";
			}
			out<<"\n";
		}
		return out;
	}
	// reading all edges of graph using friend function of graph
	friend	istream& operator>>(istream &in,Graph &g)
	{
		int u,v;
		for(int i=0;i<g.E;i++)
		{	
			if(g.weighted)
			{
				int w;
				in>>u>>v>>w;
				if(u!=v)
				{
					g.adjList[u].insert(make_pair(v,w));
				}
			}
			else
			{
				in>>u>>v;
				if(u!=v)
				{
					g.adjList[u].insert(make_pair(v,1));
				}
			}
		}
		return in;
	}
};
int main()
{
	
	int V,E;
	int w;
	//read no's of vertex ,edges and type of graph weighted (1)/unweighted(0)
	cin>>V>>E>>w;
	Graph g(V,E,w==1);
	cin>>g;
	cout<<g;
	//vector for storing topological order of graph
	vector<int> tps;
	if(!g.isCycle())
		g.TPSort(tps);
	else
	{
		cout<<"\ngraph has cycle topological sort can not be generated\n";
		exit(0);
	}
	//reading source for shortest path distance
	int source;
	cin>>source;	
	g.weightedShortestPath(source,tps);
	return 0;	
}
/*

testcase1
7 8 0
0 1
0 2
1 3
2 5
3 4
3 5
6 4
5 6
0


testcase 2
6 10 1
0 1 5
0 2 3
1 2 2
1 3 6
2 3 7
3 4 -1
4 5 -2
2 4 4
2 5 2
3 5 1
1

assignment 3

4 6 0
0 1
0 2
2 0
1 2
2 3
3 3
0
*/
