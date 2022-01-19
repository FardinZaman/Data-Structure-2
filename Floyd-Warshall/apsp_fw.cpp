#include<stdio.h>
#include<iostream>


#define INF 999

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

void floyd_warshall(Graph g)
{
    int n = g.get_vertices();
    int m = g.get_edges();
    int dist[n][n];
    int pred[n][n];

    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    for(int k=0 ; k<m ; k++)
    {
        int u = g.edge[k].source;
        int v = g.edge[k].destination;

        dist[u][v] = g.get_weight(u,v);
    }

    for(int k=0 ; k<n ; k++)
    {
        for(int i=0 ; i<n ; i++)
        {
            for(int j=0 ; j<n ; j++)
            {
                if(k == n-1)
                    pred[i][j] = dist[i][j];
                int sum = dist[i][k] + dist[k][j];
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > sum)
                    dist[i][j] = sum;
            }
        }
    }

    cout<<"All Pair Shortest Path : \n"<<endl;
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            if(dist[i][j] == INF)
                cout<<"INF"<<"   ";
            else if(dist[i][j] < 0)
                cout<<dist[i][j]<<"    ";
            else
                cout<<dist[i][j]<<"     ";
        }
        cout<<endl;
    }
    cout<<"\n";

    cout<<"Predecessor Matrix : \n"<<endl;
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            if(pred[i][j] == INF)
                cout<<"INF"<<"   ";
            else if(pred[i][j] < 0)
                cout<<pred[i][j]<<"    ";
            else
                cout<<pred[i][j]<<"     ";
        }
        cout<<endl;
    }
    cout<<"\n";

    cout<<"Negative Cycle : ";
    for(int d=0 ; d<n ; d++)
    {
        if(dist[d][d] < 0)
        {
            cout<<"Yes"<<endl;
            break;
        }
        if(d == n-1)
            cout<<"No"<<endl;
    }
}


int main()
{
    freopen("input_5.txt","r",stdin);
    //freopen("output_5.txt","w",stdout);

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

    floyd_warshall(g);

    //freopen("input_4.txt","w",stdin);
}
