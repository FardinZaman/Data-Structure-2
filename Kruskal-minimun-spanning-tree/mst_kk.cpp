#include<stdio.h>
#include<iostream>
#include"LinkedList.cpp"

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

class Cluster
{
public:

    int number;
    LinkedList ll;
};

void Kruskal(Graph g)
{
    int n = g.get_vertices();
    int m = g.get_edges();
    int weight = 0;

    Cluster* cluster = new Cluster[n];
    Min_Heap heap;
    Node nodes[m];
    int cluster_arr[n];

    Edge* tree = new Edge[m];
    int track = 0;

    for(int i=0 ; i<m ; i++)
    {
        nodes[i].index = i;
        nodes[i].distance = g.get_weight(g.edge[i].source,g.edge[i].destination);
    }

    heap.take_values(nodes , m);

    for (int i=0 ; i<n ; i++)
    {
        cluster[i].number = 1;
        cluster[i].ll.insertItem(i);

        cluster_arr[i] = i;
    }

    while(track < n-1)
    {
        Node now = heap.extract_min();
        int u = g.edge[now.index].source;
        int v = g.edge[now.index].destination;

        if(cluster_arr[u] != cluster_arr[v])
        {
            tree[track].source = u;
            tree[track].destination = v;
            track++;
            weight = weight + g.get_weight(u,v);

            int c1 = cluster_arr[u];
            int c2 = cluster_arr[v];

            if(cluster[c1].number >= cluster[c2].number)
            {
                cluster_arr[v] = c1;
                cluster[c1].number = cluster[c1].number + cluster[c2].number;
                cluster[c2].number = 0;
                cluster[c1].ll.length = cluster[c1].number;
                cluster[c2].ll.length = 0;

                ListNode* temp = cluster[c2].ll.list;
                while(temp != NULL)
                    {
                        cluster_arr[temp->item] = c1;
                        temp = temp->next;
                    }
                temp = cluster[c1].ll.list;
                cluster[c1].ll.list = cluster[c2].ll.list;
                cluster[c2].ll.list = NULL;
            }
            else
            {
                cluster_arr[u] = c2;
                cluster[c2].number = cluster[c1].number + cluster[c2].number;
                cluster[c1].number = 0;
                cluster[c2].ll.length = cluster[c2].number;
                cluster[c1].ll.length = 0;

                ListNode* temp = cluster[c1].ll.list;
                while(temp != NULL)
                    {
                        cluster_arr[temp->item] = c2;
                        temp = temp->next;
                    }
                temp = cluster[c2].ll.list;
                cluster[c2].ll.list = cluster[c1].ll.list;
                cluster[c1].ll.list = NULL;
            }
        }
    }

    for(int i=0 ; i<track ; i++)
    {
        cout<<"("<<tree[i].source<<","<<tree[i].destination<<")"<<endl;
    }
    cout<<endl;
    cout<<"MST weight : ";
    cout<<weight;
}

int main()
{
    freopen("input_6.txt","r",stdin);
    freopen("output_6.txt","w",stdout);

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

    Kruskal(g);
}
