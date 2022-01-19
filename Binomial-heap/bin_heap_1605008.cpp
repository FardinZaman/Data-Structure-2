#include<stdio.h>
#include<iostream>

#define INF 9999999

using namespace std;

class Node
{
public:
    int value;
    int order;
    Node* parent;
    Node* child;
    Node* linker;
};

class Binomial_heap
{
public:

    Node* heap;
    Node* heap_after_reverse;
    Node* track;
    Node* prev_track;

    Binomial_heap() {heap = NULL;track = NULL;prev_track = NULL;}
    Node* link_heaps(Node* heap_1 , Node* heap_2);
    void merge_heaps(Node* heap_1 , Node* heap_2);
    Node* union_heaps(Node* heap_1 , Node* heap_2);
    void insert_key(int number);
    int find_min();
    void reverse_the_heap(Node* heap);
    int extract_min();
    void print();
};

Node* Binomial_heap::link_heaps(Node* heap_1 , Node* heap_2)
{
    Node* heap_now;
    Node* for_heap_1;
    Node* for_heap_2;
    Node* temp_1;
    Node* temp_2;

    for_heap_1 = heap_1;
    for_heap_2 = heap_2;

    if(for_heap_1 == NULL)
        heap_now = for_heap_2;
    else if(for_heap_2 == NULL)
        heap_now = for_heap_1;
    else
    {
        if(for_heap_1->order <= for_heap_2->order)
            heap_now = for_heap_1;
        else
            heap_now = for_heap_2;
    }
    //cout<<heap_now->order;
    //cout<<for_heap_1->value;
    //cout<<for_heap_2->order;
    /*while(for_heap_1 != NULL && for_heap_2 != NULL)
    {

        if(for_heap_1->order <= for_heap_2->order)
        {
            temp_1 = for_heap_1->linker;
            for_heap_1->linker = for_heap_2;
            for_heap_1 = temp_1;
        }
        else
        {
            temp_2 = for_heap_2->linker;
            for_heap_2->linker = for_heap_1;
            for_heap_2 = temp_2;
        }
    }*/

    while(for_heap_1 != NULL && for_heap_2 != NULL)
    {
        if(for_heap_1->order <= for_heap_2->order)
        {
            if(for_heap_1->linker == NULL)
            {
                for_heap_1->linker = for_heap_2;
                for_heap_1 = NULL;
            }
            else if(for_heap_1->linker->order <= for_heap_2->order)
            {
                for_heap_1 = for_heap_1->linker;
            }
            else if(for_heap_1->linker->order > for_heap_2->order)
            {
                temp_1 = for_heap_1->linker;
                for_heap_1->linker = for_heap_2;
                for_heap_1 = temp_1;
            }
        }
        else if(for_heap_1->order > for_heap_2->order)
        {
            if(for_heap_2->linker == NULL)
            {
                for_heap_2->linker = for_heap_1;
                for_heap_2 = NULL;
            }
            else if(for_heap_2->linker->order <= for_heap_1->order)
            {
                for_heap_2 = for_heap_2->linker;
            }
            else if(for_heap_2->linker->order > for_heap_1->order)
            {
                temp_2 = for_heap_2->linker;
                for_heap_2->linker = for_heap_1;
                for_heap_2 = temp_2;
            }
        }

    }
    return heap_now;
}

void Binomial_heap::merge_heaps(Node* heap_1 , Node* heap_2)
{
    heap_1->parent = heap_2;
    int flag = 1;

    Node* temp;
    Node* temp_2;
    Node* temp_3;
    temp = heap_1;
    temp_2 = heap_2->child;
    while(temp != NULL && temp_2 != NULL)
    {
        flag = 2;
        temp_3 = temp;
        while(temp_3->linker != NULL)
        {
            temp_3 = temp_3->linker;
        }
        temp_3->linker = temp_2;

        temp = temp->child;
        temp_2 = temp_2->child;
    }
    if(flag == 1)
        heap_1->linker = NULL;
    //heap_1->linker = heap_2->child;
    heap_2->child = heap_1;
    //heap_2->parent = NULL;
    heap_2->order++;
}

Node* Binomial_heap::union_heaps(Node* heap_1 , Node* heap_2)
{
    Node* heap_now;
    heap_now = link_heaps(heap_1 , heap_2);
    if(heap_now == NULL){
        return heap_now;
    }

    Node* x;
    Node* prev_x;
    Node* next_x;

    x = heap_now;
    prev_x = NULL;
    next_x = x->linker;
    //cout<<x->order<<" ";
    //cout<<next_x->order<<" ";

    while(next_x != NULL){

    if(x->order != next_x->order || (next_x->linker != NULL && next_x->linker->order == x->order))
    {
        prev_x = x;
        x = next_x;
    }
    else
    {
        if(x->value <= next_x->value)
        {
            x->linker = next_x->linker;
            next_x->linker = NULL;
            merge_heaps(next_x , x);
        }
        else
        {
            if(prev_x == NULL)
                heap_now = next_x;
            else
                prev_x->linker = next_x;

            x->linker = NULL;
            merge_heaps(x , next_x);
            x = next_x;
        }
    }
    next_x = x->linker;
    }

    return heap_now;
}

void Binomial_heap::insert_key(int number)
{
    Node* temp = new Node();
    Node* temp_2;
    temp->value = number;
    temp->order = 0;
    temp->parent = NULL;
    temp->child = NULL;
    temp->linker = NULL;
    temp_2 = temp;

    this->heap = union_heaps(this->heap , temp_2);
}

int Binomial_heap::find_min()
{
    if(this->heap == NULL)
    {
        cout<<"Heap is empty"<<endl;
        return INF;
    }

    Node* temp;
    Node* temp_2;
    temp = this->heap;
    temp_2 = temp->linker;

    int minimum = temp->value;
    track = temp;

    while(temp_2 != NULL)
    {
        if(temp_2->value < minimum)
        {
            minimum = temp_2->value;
            track = temp_2;
            prev_track = temp;
        }

        temp = temp->linker;
        temp_2 = temp_2->linker;
    }

    return minimum;
}

void Binomial_heap::reverse_the_heap(Node* heap)
{
    if(heap->linker != NULL)
    {
        reverse_the_heap(heap->linker);
        heap->linker->linker = heap;
    }
    else
    {
        heap_after_reverse = heap;
    }
}

int Binomial_heap::extract_min()
{
    if(this->heap == NULL)
    {
        cout<<"Heap is empty"<<endl;
        return INF;
    }

    int minimum = this->find_min();

    if(prev_track != NULL)
        prev_track->linker = track->linker;
    if(this->heap == track)
        this->heap = track->linker;

    Node* orphan;
    orphan = track->child;

    Node* temp;
    temp = orphan;

    if(temp == NULL)
        return minimum;

    while(1)
    {
        if(temp->order <=1)
            break;

        int ord = temp->order;

        Node* temp_2;
        temp_2 = temp;
        Node* temp_3;
        temp_3 = temp->linker;

        for(int i=1 ; i<ord ; i++)
        {
            temp_2 = temp_2->child;
            temp_3 = temp_3->child;

            Node* walk
            ;
            walk = temp_2;

            while(walk->linker != temp_3)
            {
                walk = walk->linker;
            }
            walk->linker = NULL;
        }
        temp = temp->linker;
    }

    reverse_the_heap(orphan);
    orphan->linker = NULL;

    this->heap = union_heaps(this->heap , heap_after_reverse);
    return minimum;
}

void Binomial_heap::print()
{
    if(this->heap == NULL)
        cout<<"Heap is empty"<<endl;

    Node* walk;
    walk = this->heap;
    Node* climb;
    int w = 1;
    int c;
    Node* walk_the_level;

    while(walk != NULL)
    {
        cout<<"Heap "<<w<<":"<<endl<<endl;
        climb = walk;
        c = 1;
        while(climb != NULL)
        {
            walk_the_level = climb;
            cout<<"level "<<c<<": ";

            while(walk_the_level != NULL)
            {
                cout<<walk_the_level->value<<" ";
                if(walk_the_level == walk)
                    break;
                walk_the_level = walk_the_level->linker;
            }
            climb = climb->child;
            c++;
            cout<<endl;
        }

        walk = walk->linker;
        w++;
        cout<<endl;
    }
}

int main()
{
    int arr[4] = {5 , 12 , 8 , 10};
    int arr_2[4] = {14 , 2 , 3 , 1};

    Binomial_heap bh;
    Binomial_heap bh_2;

    for(int i=0 ; i<4 ; i++)
        bh.insert_key(arr[i]);
    for(int i=0 ; i<4 ; i++)
        bh_2.insert_key(arr_2[i]);
    //bh.insert_key(2);
    //bh.insert_key(9);
    //bh_2.print();
    //cout<<bh.heap->order;
    //cout<<bh_2.heap->order;
    bh.heap = bh.union_heaps(bh.heap , bh_2.heap);
    bh.print();
    //bh.print();
    //bh.merge_heaps(bh_2.heap , bh.heap);
    //bh_2.heap = bh_2.union_heaps(bh_2.heap , bh.heap);
    //bh_2.print();
    //cout<<bh.extract_min();
    //bh.print();
    while(1)
    {
       int choice;
       cout<<"Choose : 1.Insert  2.Find Minimum  3.Extract Minimum  4.Union  5.Print  6.Exit"<<endl;
       cin>>choice;
       cout<<endl;

       if(choice == 1)
       {
           int number;
           cout<<"Enter the value : ";
           cin>>number;
           bh.insert_key(number);
       }

       else if(choice == 2)
       {
           int minimum = bh.find_min();
           if(minimum == INF)
           {
               continue;
           }
           cout<<minimum<<endl;
       }

       else if(choice == 3)
       {
           int minimum = bh.extract_min();
           if(minimum == INF)
           {
               continue;
           }
           cout<<minimum<<endl;
       }

       else if(choice == 4)
       {
           int n , value;
           cout<<"Enter 2nd heap size : ";
           cin>>n;

           Binomial_heap bh_2;
           cout<<"Enter the values : "<<endl;
           for(int i=0 ; i<n ; i++)
           {
               cin>>value;
               bh_2.insert_key(value);
           }
           bh_2.print();
           bh.heap = bh.union_heaps(bh.heap , bh_2.heap);
       }

       else if(choice == 5)
       {
           bh.print();
       }

       else if(choice == 6)
           break;

       else
           continue;
    }
}
