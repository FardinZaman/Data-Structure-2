#include<stdio.h>
#include<iostream>
#include<list>

#define INF 999

using namespace std;

class Node
{
public:

    int index;
    int distance;
};

class Min_Heap
{
public:

    int heap_size;
    Node* heap_arr;

    Min_Heap()  {heap_size = 0;heap_arr = NULL;}
    void take_values(Node arr[] , int length);
    int get_left_index(int index) {return index*2 +1;}
    int get_right_index(int index)  {return index*2 + 2;}
    int get_parent(int index)  {return (index-1)/2;}
    //int get_size()  {return this->heap_size;}
    bool is_empty()  {return (heap_size==0);}
    bool is_in_heap(int index);
    void Build_Min_Heap();
    void Min_Heapify(int index);
    void delete_min();
    Node extract_min();
    void decrease_key(int index , int decrease);
    void just_sift_up(int index);
};

void Min_Heap::take_values(Node arr[] , int length)
{
    this->heap_size = length;
    this->heap_arr = new Node[length];

    for(int i=0 ; i<length ; i++)
        heap_arr[i] = arr[i];

    this->Build_Min_Heap();
}

void Min_Heap::Build_Min_Heap()
{
    int n = this->heap_size-1;
    for(int i=n/2 ; i>=0 ; i--)
    {
        this->Min_Heapify(i);
    }
}

void Min_Heap::Min_Heapify(int index)
{
    int left = this->get_left_index(index);
    int right = this->get_right_index(index);

    int maximum = 0;

    if(left<=this->heap_size-1 && this->heap_arr[left].distance<this->heap_arr[index].distance)
        maximum = left;
    else
        maximum = index;

    if(right<=this->heap_size-1 && this->heap_arr[right].distance<this->heap_arr[maximum].distance)
        maximum = right;

    if(maximum != index)
    {
        Node temp;
        temp = this->heap_arr[index];
        this->heap_arr[index] = this->heap_arr[maximum];
        this->heap_arr[maximum] = temp;

        this->Min_Heapify(maximum);
    }
}

Node Min_Heap::extract_min()
{
    Node root = this->heap_arr[0];
    this->delete_min();
    //cout<<root<<endl;
    return root;
    //cout<<root<<endl;
}

void Min_Heap::delete_min()
{
    Node* temp = new Node[heap_size-1];
    temp[0] = this->heap_arr[heap_size-1];
    for(int i=1 ; i<this->heap_size-1 ; i++)
        temp[i] = this->heap_arr[i];

    delete[] this->heap_arr;
    this->heap_arr = temp;

    this->heap_size--;

    this->Min_Heapify(0);
}

void Min_Heap::decrease_key(int index , int decrease)
{
    int track;
    for(track=0 ; track<this->heap_size ; track++)
    {
        if(this->heap_arr[track].index == index)
            break;
    }
    this->heap_arr[track].distance = decrease;
    this->just_sift_up(track);
}

void Min_Heap::just_sift_up(int index)
{
    int child = index;
    int parent = this->get_parent(child);

    while(this->heap_arr[child].distance < this->heap_arr[parent].distance)
    {
        Node temp;
        temp = this->heap_arr[child];
        this->heap_arr[child] = this->heap_arr[parent];
        this->heap_arr[parent] = temp;

        child = parent;
        parent = get_parent(child);
    }
}

bool Min_Heap::is_in_heap(int index)
{
    for(int i=0 ; i<this->heap_size ; i++)
    {
        if(this->heap_arr[i].index == index)
            return true;
    }
    return false;
}

class Graph
{
    int vertices;
    //list<int> *adj_list;
    int** weight_array;

public:
    list<int> *adj_list;
    Graph(int vertices);
    void add_edge(int u,int v,int weight);
    int get_weight(int u,int v)  {return weight_array[u][v];}
    int get_vertices()  {return this->vertices;}
};

Graph::Graph(int vertices)
{
    this->vertices = vertices;
    adj_list = new list<int>[vertices];

    weight_array = new int*[vertices];
    for(int i=0 ; i<vertices ; i++)
    {
        weight_array[i] = new int[vertices];
    }
}

void Graph::add_edge(int u,int v,int weight)
{
    adj_list[u].push_back(v);
    weight_array[u][v] = weight;
}

void dijkstra(Graph g,int source)
{
    int n = g.get_vertices();
    int dist[n];
    int prev[n];
    Node arr[n];

    for(int i=0 ; i<n ; i++)
    {
        dist[i] = INF;
        prev[i] = -1;

        Node temp;
        temp.index = i;
        temp.distance = INF;
        if(i == source)
            temp.distance = 0;
        arr[i] = temp;
    }

    dist[source] = 0;

    Min_Heap H;
    H.take_values(arr , n);

    while(!H.is_empty())
    {
        Node now = H.extract_min();
        int u = now.index;
        cout<<u<<" "<<dist[u]<<endl;

        list<int>::iterator itr;
        for(itr = g.adj_list[u].begin() ; itr != g.adj_list[u].end() ; itr++)
        {
            int v = *itr;

            if(!H.is_in_heap(v))
                continue;

            int sum = dist[u] + g.get_weight(u,v);

            if(sum < dist[v])
            {
                dist[v] = sum;
                prev[v] = u;

                H.decrease_key(v , dist[v]);
            }
        }
    }

    cout<<endl;

    for(int j=0 ; j<n ; j++)
    {
        int k = j;
        cout<<k<<" "<<k;
        k = prev[k];
        while(k != -1)
        {
            cout<<"<-"<<k;
            k = prev[k];
        }
        cout<<endl;
    }
}

int main()
{
    freopen("input_2.txt","r",stdin);

    int vertex;
    int edge;
    cin>>vertex;
    cin>>edge;
    Graph g(vertex);

    for(int i = 0 ; i<edge ; i++)
    {
        int first;
        int second;
        int length;
        cin>>first;
        cin>>second;
        cin>>length;

        g.add_edge(first , second , length);
    }

    dijkstra(g , 0);
}
