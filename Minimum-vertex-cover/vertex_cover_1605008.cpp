#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<list>
#include <ctime>
#include <algorithm>

#define INF 9999999

using namespace std;

//int random = 120;

double average(int arr[])
{
    int sum = 0;
    double avg;

    for(int i=0 ; i<5 ; i++)
        sum+=arr[i];
    return sum/5;
}

struct Edge
{
public:
    //int index;
    int u;
    int v;
};

class Graph
{
    int vertices;
    int edges;

public:
    int* degree;
    bool* covered;
    Edge* edge;
    Edge* sorted_edge;
    Graph(int vertices , int edges);
    void add_edge(int index,int u,int v);
    int get_vertices()  {return this->vertices;}
    int get_edges()  {return this->edges;}
    int vc_random();
    int vc_max_degree();
    bool compare_two_edge(Edge one , Edge two);
    void sort_edges(Edge* arr , int length);
};

Graph::Graph(int vertices , int edges)
{
    this->vertices = vertices;
    this->edges = edges;
    this->degree = new int[vertices];
    this->covered = new bool[edges];
    for(int i=0 ; i<vertices ; i++)
        degree[i] = 0;

    this->edge = new Edge[edges];
    this->sorted_edge = new Edge[edges];
}

void Graph::add_edge(int index,int u,int v)
{
    Edge temp;
    //temp.index = index;
    temp.u = u;
    temp.v = v;

    degree[u]++;
    degree[v]++;

    this->edge[index] = temp;
    this->sorted_edge[index] = temp;
}

int Graph::vc_random()
{
    int n = this->get_vertices();
    int m = this->get_edges();

    list<int> vertex_cover;

    for(int i=0 ; i<m ; i++)
        covered[i] = false;

    int picked = 0;
    //int no = 0;
    srand(time(0));
    random_shuffle(edge, edge+m);

    for(int random = 0; random < m; random++)
    {
        //int random = rand()%m;
        //if(picked >= m-1000)
            //random = no;
        //random = random%m;
        if(covered[random] == false)
        {
            covered[random] = true;
            picked++;

            vertex_cover.push_back(edge[random].u);
            vertex_cover.push_back(edge[random].v);

            for(int i=0 ; i<m ; i++)
            {
                if((edge[i].u == edge[random].u || edge[i].u == edge[random].v || edge[i].v == edge[random].u || edge[i].v == edge[random].v) && covered[i] == false)
                {
                    covered[i] = true;
                    picked++;
                }
            }
        }

        //no = no + 1;
        //random = random * 3;
        //cout<<picked<<endl;
        if(picked == m)
            break;
    }

    return vertex_cover.size();
}

bool Graph::compare_two_edge(Edge one , Edge two)
{
    int first = degree[one.u] + degree[one.v];
    int second = degree[two.u] + degree[two.v];

    if(first != second)
        return first > second;
}

void Graph::sort_edges(Edge* arr , int length)
{
    /*Edge temp[length];
    for(int k=0 ; k<length ; k++)
        temp[k] = arr[k];*/

    //sort(temp , temp+length , compare_two_edge);
    int i , j;
    for(i=0 ; i<length-1 ; i++)
    {
        for(j=0 ; j<length-1 ; j++)
        {
            int first = degree[arr[j].u] + degree[arr[j].v];
            int second = degree[arr[j+1].u] + degree[arr[j+1].v];
            if(first < second)
            {
                Edge temp_2 = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp_2;
            }
        }
    }

    //arr = temp;
}

int Graph::vc_max_degree()
{
    int n = this->get_vertices();
    int m = this->get_edges();

    list<int> vertex_cover;

    for(int i=0 ; i<m ; i++)
        covered[i] = false;

    int picked = 0;

    while(1)
    {
        //cout<<7;
        //sort_edges(sorted_edge , m);

//        int itr = 0;
//        int now = INF;
//        while(now == INF)
//        {
//            if(covered[sorted_edge[itr].index] == false)
//            {
//                now = itr;
//            }
//            else
//            {
//                itr++;
//            }
//        }


        int max_deg = 0, now = -1;
        for(int i=0; i<m; i++)
        {
            int u = sorted_edge[i].u;
            int v = sorted_edge[i].v;
            if(degree[u]+degree[v] > max_deg)
            {
                max_deg = degree[u]+degree[v];
                now = i;
            }
        }

        /*for(int temp = 0 ; temp<m ; temp++)
        {
            cout<<degree[sorted_edge[temp].u] + degree[sorted_edge[temp].v]<<endl;
        }
        cout<<endl;*/
        //cout<<degree[sorted_edge[now].u] + degree[sorted_edge[now].v]<<endl;
        //cout<<sorted_edge[now].index<<endl;
        covered[now] = true;
        picked++;

        vertex_cover.push_back(sorted_edge[now].u);
        vertex_cover.push_back(sorted_edge[now].v);
        degree[sorted_edge[now].u] = 0;
        degree[sorted_edge[now].v] = 0;

        for(int i=0 ; i<m ; i++)
        {
            if(sorted_edge[i].u == sorted_edge[now].u && covered[i] == false)
            {
                covered[i] = true;
                picked++;
                degree[sorted_edge[i].v]--;
            }
            else if(sorted_edge[i].u == sorted_edge[now].v && covered[i] == false)
            {
                covered[i] = true;
                picked++;
                degree[sorted_edge[i].v]--;
            }
            else if(sorted_edge[i].v == sorted_edge[now].u && covered[i] == false)
            {
                covered[i] = true;
                picked++;
                degree[sorted_edge[i].u]--;
            }
            else if(sorted_edge[i].v == sorted_edge[now].v && covered[i] == false)
            {
                covered[i] = true;
                picked++;
                degree[sorted_edge[i].u]--;
            }
        }

        //cout<<picked<<endl;

        if(picked == m)
            break;
    }

    return vertex_cover.size();
}


int main()
{
    freopen("worst.txt","r",stdin);
    //freopen("output_4.txt","w",stdout);

    int vertex;
    int edge;
    cin>>vertex;
    cin>>edge;
    Graph g(vertex , edge);

    for(int i = 0 ; i<edge ; i++)
    {
        int first;
        int second;

        cin>>first;
        cin>>second;

        g.add_edge(i , first-1 , second-1);
    }

    //cout<<g.vc_random();
    int first[5];
    int d = 0;
    first[d++] = g.vc_random();
    first[d++] = g.vc_random();
    first[d++] = g.vc_random();
    first[d++] = g.vc_random();
    first[d++] = g.vc_random();

    sort(first , first+5);

    cout<<"Best : "<<first[0]<<endl;
    cout<<"Worst : "<<first[4]<<endl;
    cout<<"Average : "<<average(first)<<endl;

    int k = g.vc_max_degree();
    cout<<k;
}
