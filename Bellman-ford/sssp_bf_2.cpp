#define INF 999
#include<stdio.h>
#include<iostream>
#include<list>

using namespace std;

class Edge
{
public:

    int source;
    int destination;
};

class Graph
{
    int vertices;
    int edges;
    //Edge* edge;
    //list<int> *adj_list;
    int** weight_array;

public:
    //list<int> *adj_list;
    Edge* edge;
    Graph(int vertices , int edges);
    void add_edge(int index,int u,int v,int weight);
    int get_weight(int u,int v)  {return weight_array[u][v];}
    int get_vertices()  {return this->vertices;}
    int get_edges()  {return this->edges;}
};

Graph::Graph(int vertices , int edges)
{
    this->vertices = vertices;
    this->edges = edges;
    this->edge = new Edge[edges];
    //adj_list = new list<int>[vertices];

    weight_array = new int*[vertices];
    for(int i=0 ; i<vertices ; i++)
    {
        weight_array[i] = new int[vertices];
    }
}

void Graph::add_edge(int index,int u,int v,int weight)
{
    //adj_list[u].push_back(v);
    Edge temp;
    temp.source = u;
    temp.destination = v;
    this->edge[index] = temp;
    weight_array[u][v] = weight;
}

void bellman_ford_2(Graph g , int source)
{
    int n = g.get_vertices();
    int m = g.get_edges();
    int dist[n];
    int prev[n];
    int dist_extra[n];

    for(int i=0 ; i<n ; i++)
    {
        prev[i] = -1;
        if(i != source)
        {
            dist[i] = INF;
            dist_extra[i] = INF;
        }
        else
        {
            dist[i] = 0;
            dist_extra[i] = 0;
        }
    }

    for(int r=0 ; r<n ; r++)
    {
        int itr;
        for(itr=0 ; itr<m ; itr++)
        {
            //list<int>::iterator itr;
            //for(itr = g.adj_list[u].begin() ; itr != g.adj_list[u].end() ; itr++)
            //
                int u = g.edge[itr].source;
                int v = g.edge[itr].destination;

                int sum = dist[u] + g.get_weight(u,v);

                if(sum < dist[v])
                {
                    if(r == n-1)
                        dist_extra[v] = sum;
                    else
                    {
                        dist_extra[v] = sum;
                        dist[v] = sum;
                        prev[v] = u;
                    }
                }
            //
        }
    }

    for(int j=0 ; j<n ; j++)
        cout<<j<<" "<<dist[j]<<endl;

    for(int k=0 ; k<n ; k++)
    {
        if(dist[k] != dist_extra[k])
        {
            cout<<"HAS NEGATIVE CYCLE"<<endl;
            break;
        }
        if(k == n-1)
            cout<<"NO NEGATIVE CYCLE"<<endl;
    }
}

int main()
{
    freopen("input_3.txt","r",stdin);
    freopen("input_4.txt","w",stdout);

    int vertex;
    int edge;
    cin>>vertex;
    cin>>edge;
    Graph g(vertex , edge);

    for(int i = 0 ; i<edge ; i++)
    {
        int first;
        int second;
        int length;
        cin>>first;
        cin>>second;
        cin>>length;

        g.add_edge(i , first , second , length);
    }

    bellman_ford_2(g , 0);

    //freopen("input_4.txt","w",stdin);
}
