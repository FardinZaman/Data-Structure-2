#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int dequeue();
    bool empty();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ;
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}


class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int position);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Edge
{
public:

    int source;
    int destination;
    int flow;
};

class Graph
{
	int vertices, edges ;
	bool directed ;
	ArrayList  * adjList ;
	int* color;
	int** weight_array;

public:
	Graph(int vertex , int edges);
	Edge* edge;
	int* parent;
	void add_edge(int index, int u, int v, int w);
	bool bfs(int** residual , int source , int destination);
    int get_vertices()  {return this->vertices;}
    int get_edges()  {return this->edges;}
    int get_weight(int u,int v)  {return weight_array[u][v];}
};

Graph::Graph(int vertex , int edges)
{
	this->vertices = vertex ;
	this->edges = edges ;
	this->edge = new Edge[edges];

	color = NULL;
	parent = NULL;

	if(adjList!=NULL) delete[] adjList ;
	adjList = new ArrayList[this->vertices] ;

	weight_array = new int*[vertices];
    for(int i=0 ; i<vertices ; i++)
    {
        weight_array[i] = new int[vertices];
    }

    for(int i=0 ; i<vertices ; i++)
        for(int j=0 ; j<vertices ; j++)
            weight_array[i][j] = 0;
}

void Graph::add_edge(int index , int u, int v, int w)
{
	adjList[u].insertItem(v) ;
	adjList[v].insertItem(u) ;

    weight_array[u][v] = w;

    Edge temp;
    temp.source = u;
    temp.destination = v;
    this->edge[index] = temp;
}

bool Graph::bfs(int** residual , int source , int destination)
{
	color = (int*)malloc(vertices*sizeof(int));
	parent = (int*)malloc(vertices*sizeof(int));

    for(int i=0; i<vertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
    }

    Queue q ;

    color[source] = GRAY;
    parent[source] = NULL;

    q.enqueue(source) ;

    while( !q.empty() )
    {
        int u = q.dequeue();
        for(int i=0 ; i<adjList[u].getLength() ; i++)
        {
            int v = adjList[u].getItem(i);
            if(color[v] == WHITE && residual[u][v]>0)
            {
                color[v] = GRAY;
                parent[v] = u;
                q.enqueue(v);
            }

        }
        color[u] = BLACK;
    }
    return (color[destination] == BLACK);
}

void Ford_Fulkerson(Graph g , int source , int sink)
{
    int u;
    int n = g.get_vertices();
    int m = g.get_edges();
    int flow;
    int max_flow = 0;
    int min_cut = 0;

    int** residual;

    residual = new int*[n];
    for(int i=0 ; i<n ; i++)
    {
        residual[i] = new int[n];
    }

    for(int u=0 ; u<n ; u++)
    {
        for(int v=0 ; v<n ; v++)
        {
            residual[u][v] = g.get_weight(u,v);
        }
    }

    for(int i=0 ; i<m ; i++)
    {
        g.edge[i].flow = 0;
    }

    while(g.bfs(residual , source , sink))
    {
        flow = INFINITY;

        for(int v=sink ; v!=source ; v=g.parent[v])
        {
            u = g.parent[v];
            flow = min(flow , residual[u][v]);
        }

        for(int v=sink ; v!=source ; v=g.parent[v])
        {
            u = g.parent[v];
            residual[u][v] = residual[u][v] - flow;
            residual[v][u] = residual[v][u] + flow;

            for(int i=0 ; i<m ; i++)
            {
                if(g.edge[i].source == u && g.edge[i].destination == v)
                    g.edge[i].flow = g.edge[i].flow + flow;
                if(g.edge[i].source == v && g.edge[i].destination == u)
                    g.edge[i].flow = g.edge[i].flow - flow;
            }
        }

        max_flow = max_flow + flow;
    }

    cout<<"MAX_FLOW : "<<max_flow<<endl;
    for(int i=0 ; i<m ; i++)
    {
        cout<<"("<<g.edge[i].source<<","<<g.edge[i].destination<<") : "<<g.edge[i].flow<<endl;
    }
    cout<<endl;

    for(int i=0 ; i<m ; i++)
    {
        if((g.parent[g.edge[i].source] != -1 || g.edge[i].source == source) && g.parent[g.edge[i].destination] == -1)
        {
            min_cut = min_cut + g.get_weight(g.edge[i].source , g.edge[i].destination);
            cout<<"("<<g.edge[i].source<<","<<g.edge[i].destination<<")"<<endl;
        }
    }
    cout<<"MIN_CUT : "<<min_cut<<endl;
}

int main()
{
    freopen("input_7.txt","r",stdin);
    freopen("output_7.txt","w",stdout);

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

    int source;
    int sink;
    cin>>source;
    cin>>sink;

    Ford_Fulkerson(g , source , sink);
}
