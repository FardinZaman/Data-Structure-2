#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

class Node
{
public:

    int value;
    Node* left;
    Node* right;
    Node* parent;
};

class Splay_Tree
{
public:
    Node* root;
    void left_rotation(Node* x);
    void right_rotation(Node* x);
    void splay(Node* x);
    Node* search_for(int number);
    void insert_node(int number);
    void join(Splay_Tree L , Splay_Tree R);
    void delete_node(int number);
    void print(Node* root);
};

void Splay_Tree::left_rotation(Node* x)
{
    Node* rgt = x->right;
    Node* lft = rgt->left;
    Node* prt = x->parent;

    if(prt != NULL)
    {
        if(prt->right == x)
            prt->right = rgt;
        else
            prt->left = rgt;
    }

    if(lft != NULL)
    {
        lft->parent = x;
    }

    rgt->parent = prt;
    rgt->left = x;

    x->parent = rgt;
    x->right = lft;
}

void Splay_Tree::right_rotation(Node* x)
{
    Node* lft = x->left;
    Node* rgt = lft->right;
    Node* prt = x->parent;

    if(prt != NULL)
    {
        if(prt->right == x)
            prt->right = lft;
        else
            prt->left = lft;
    }

    if(rgt != NULL)
    {
        rgt->parent = x;
    }

    lft->parent = prt;
    lft->right = x;

    x->parent = lft;
    x->left = rgt;
}

void Splay_Tree::splay(Node* x)
{
    while(1)
    {
        Node* P = x->parent;
        if(P == NULL)
            break;

        Node* G = P->parent;

        if(G == NULL)
        {
            if(P->left == x)
                right_rotation(P);
            else
                left_rotation(P);
            break;
        }

        if(G->left == P)
        {
            if(P->left == x)
            {
                right_rotation(P);
                right_rotation(G);
            }
            else
            {
                left_rotation(P);
                right_rotation(G);
            }
        }

        else
        {
            if(P->right == x)
            {
                left_rotation(P);
                left_rotation(G);
            }
            else
            {
                right_rotation(P);
                left_rotation(G);
            }
        }
    }
    root = x;
}

Node* Splay_Tree::search_for(int number)
{
    if(root == NULL)
        return NULL;
    Node* x = root;
    while(x != NULL)
    {
        if(x->value == number)
            break;

        if(number < x->value)
        {
            if(x->left != NULL)
                x = x->left;
            else
                break;
        }

        else
        {
            if(x->right != NULL)
                x = x->right;
            else
                break;
        }
    }

    splay(x);
    if(x->value == number)
        return x;
    else
        return NULL;
}

void Splay_Tree::insert_node(int number)
{
    if(root == NULL)
    {
        root = new Node();
        root->left = NULL;
        root->right = NULL;
        root->parent = NULL;
        root->value = number;
        return;
    }

    Node* x;
    x = root;

    while(1)
    {
        if(x->value == number)
            break;

        if(number < x->value)
        {
            if(x->left != NULL)
                x = x->left;
            else
            {
                x->left = new Node();
                x->left->parent = x;
                x->left->left = NULL;
                x->left->right = NULL;
                x->left->value = number;
                x = x->left;

                break;
            }
        }

        else
        {
            if(x->right != NULL)
                x = x->right;
            else
            {
                x->right = new Node();
                x->right->parent = x;
                x->right->left = NULL;
                x->right->right = NULL;
                x->right->value = number;
                x = x->right;

                break;
            }
        }
    }

    splay(x);
}

void Splay_Tree::join(Splay_Tree L , Splay_Tree R)
{
    if(L.root == NULL)
    {
        root = R.root;
        return;
    }

    Node* left_max;
    left_max = L.root;
    while(left_max->right != NULL)
    {
        left_max = left_max->right;
    }
    L.splay(left_max);

    root = left_max;
    root->right = R.root;
    if(root->right != NULL)
        root->right->parent = root;

}

void Splay_Tree::delete_node(int number)
{
    Node* target;
    target = search_for(number);

    if(target == NULL)
    {
        cout<<"Not Found"<<endl;
        return;
    }

    splay(target);

    Splay_Tree L;
    Splay_Tree R;

    L.root = target->left;
    if(L.root != NULL)
        L.root->parent = NULL;
    R.root = target->right;
    if(R.root !=NULL)
        R.root->parent = NULL;

    join(L,R);

    free(target);
}

void Splay_Tree::print(Node* root)
{
    if(root == NULL)
    {
        cout<<"No Tree"<<endl;
        return;
    }

    if(root != NULL)
        cout<<root->value<<" ";
    if(root->left != NULL)
        cout<<"left : "<<root->left->value<<" ";
    if(root->right != NULL)
        cout<<"right : "<<root->right->value<<" ";
    cout<<endl;

    if(root->left != NULL)
        print(root->left);

    if(root->right != NULL)
        print(root->right);

    return;
}

int main()
{
    Splay_Tree ST;
    ST.root = NULL;
    //int arr[5];
    int arr[5] = {23 , 9 , 14 , 17 , 5};
    for(int i=0 ; i<5 ; i++)
    {
        ST.insert_node(arr[i]);
    }
    //ST.delete_node(17);
    //ST.print(ST.root);
    while(1)
    {
        cout<<"Choose option : 1.Insert  2.Search  3.Delete  4.Print  5.Exit\n";
        int choice;
        cin>>choice;

        if(choice == 1)
        {
            cout<<"Enter Value : "<<endl;
            int num;
            cin>>num;
            ST.insert_node(num);
        }

        else if(choice == 2)
        {
            cout<<"Enter Value : "<<endl;
            int num;
            cin>>num;
            Node* temp = ST.search_for(num);
            if(temp == NULL)
                cout<<"Not Found"<<endl;
            else
                cout<<"Found"<<endl;
        }

        else if(choice == 3)
        {
            cout<<"Enter Value : "<<endl;
            int num;
            cin>>num;
            ST.delete_node(num);
        }

        else if(choice == 4)
            ST.print(ST.root);

        else if(choice == 5)
            break;

        else
            continue;
    }
}
