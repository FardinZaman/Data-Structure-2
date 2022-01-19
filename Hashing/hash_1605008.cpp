#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<cstring>

#define c1 9
#define c2 20
#define INF 999999;

using namespace std;

bool is_taken(string* s , string t , int index)
{
    for(int i=0 ; i<=index ; i++)
    {
        if(t.compare(s[i]) == 0)
            return true;
    }

    return false;
}

string* random_generator()
{
    string* now = new string[10000];

    for(int i=0 ; i<10000 ; i++)
        now[i] = "";

    char alphabet[52];

    for(int i=0 ; i<26 ; i++)
    {
        alphabet[i] = 'a' + i;
        alphabet[26+i] = 'A' + i;
    }

    char temp[7];

    int k = 0;

    while(k<10000)
    {
        for(int j=0 ; j<7 ; j++)
        {
            temp[j] = alphabet[rand() % 52];
        }

        string then = temp;

        if(is_taken(now , then , k))
            continue;
        else
        {
            now[k] = then;
            k++;
        }

    }

    return now;
}

struct search_output
{
    int result;
    int hit;
};

int hash_1(string key , int number)
{
    int h = 0;
    int a = 127;

    for(int i=0 ; i<7 ; i++)
    {
        h = (a*h + key[i]) % number;
    }

    return h;
}

int hash_2(string key , int number)
{
    unsigned long h = 5381;

    for(int i=0 ; i<7 ; i++)
    {
        h = (h<<5) + h + key[i];
    }

    return h%number;
}

int aux_hash(string key  ,int number)
{
    int sum = 0;

    for(int i=0 ; i<7 ; i++)
    {
        sum += (int) key[i];
    }

    return sum%number;
}

class Hash_node
{
public:

    string key;
    int value;
};

class List_node
{
public:

    Hash_node item;
    List_node* next;
};

class Linked_list
{
    List_node* list;
    int length;

public:

    Linked_list()
    {
        list = NULL;
        length = 0;
    }

    void insert_node(Hash_node h)
    {
        List_node* node = new List_node();
        node->item.key = h.key;
        node->item.value = h.value;

        node->next = NULL;

        if(list == NULL)
        {
            list = node;
            length++;
            return;
        }

        List_node* temp = list;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = node;
        length++;
    }

    search_output searching(string key)
    {
        List_node* temp = list;
        int hits = 1;

        search_output out;

        out.result = -INF;

        while(temp != NULL)
        {
            if(temp->item.key.compare(key) == 0)
            {
                out.result = temp->item.value;
                break;
            }
            temp = temp->next;
            hits++;
        }

        out.hit = hits;

        return out;
    }

    void delete_node(string key)
    {
        List_node* temp = list;
        List_node* prev = NULL;

        while(temp != NULL)
        {
            if(temp->item.key.compare(key) == 0)
                break;

            prev = temp;
            temp = temp->next;
        }

        if(temp == NULL)
            return;

        if(temp == list)
        {
            list = list->next;
            delete temp;
            length--;
        }

        else
        {
            prev->next = temp->next;
            delete temp;
            length--;
        }
    }

    int get_length()
    {
        return length;
    }
};

class Hash_table_chain_1
{
    Linked_list* table;
    int size;

    int collisions;
    int hits;

public:

    Hash_table_chain_1(int s)
    {
        size = s;

        table = new Linked_list[size];

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        Hash_node h;
        h.key = key;
        h.value = value;

        int index = hash_1(key , size);
        table[index].insert_node(h);

        collisions += table[index].get_length() - 1;
    }

    int searching(string key)
    {
        int index = hash_1(key , size);

        search_output out = table[index].searching(key);

        hits += out.hit;

        return out.result;
    }

    void delete_node(string key)
    {
        int index = hash_1(key , size);

        table[index].delete_node(key);
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};

class Hash_table_chain_2
{
    Linked_list* table;
    int size;

    int collisions;
    int hits;

public:

    Hash_table_chain_2(int s)
    {
        size = s;

        table = new Linked_list[size];

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        Hash_node h;
        h.key = key;
        h.value = value;

        int index = hash_2(key , size);
        table[index].insert_node(h);

        collisions += table[index].get_length() - 1;
    }

    int searching(string key)
    {
        int index = hash_2(key , size);

        search_output out = table[index].searching(key);

        hits += out.hit;

        return out.result;
    }

    void delete_node(string key)
    {
        int index = hash_1(key , size);

        table[index].delete_node(key);
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};

class Hash_table_double_hashing_1
{
    Hash_node* table;
    int size;
    int* status;

    int collisions;
    int hits;

public:

    Hash_table_double_hashing_1(int s)
    {
        size = s;
        table = new Hash_node[size];
        status = new int[size];

        for(int i=0 ; i<size ; i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        int i=0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + i*second) % size;

            if(status[index] == 1)
                collisions++;

            else
            {
                table[index].key = key;
                table[index].value = value;
                status[index] = 1;

                return;
            }

            if(i>0 && index == first)
            {
                return;
            }

            i++;
        }

        /*table[index].key = key;
        table[index].value = value;
        status[index] = 1;*/
    }

    int searching(string key)
    {
        int i = 0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        hits++;

        while(1)
        {
            index = (first + i*second) % size;

            if(table[index].key.compare(key) != 0)
                hits++;
            else
                return table[index].value;

            if(i>0 && index == first)
                return -INF;

            i++;
        }
    }

    void delete_node(string key)
    {
        int i=0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + i*second) % size;

            if(table[index].key.compare(key) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;

                return;
            }

            if(i>0 && index == first)
                return;

            i++;
        }
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};

class Hash_table_double_hashing_2
{
    Hash_node* table;
    int size;
    int* status;

    int collisions;
    int hits;

public:

    Hash_table_double_hashing_2(int s)
    {
        size = s;
        table = new Hash_node[size];
        status = new int[size];

        for(int i=0 ; i<size ; i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        int i=0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + i*second) % size;

            if(status[index] == 1)
                collisions++;

            else
            {
                table[index].key = key;
                table[index].value = value;
                status[index] = 1;

                return;
            }

            if(i>0 && index == first)
            {
                return;
            }

            i++;
        }

        /*table[index].key = key;
        table[index].value = value;
        status[index] = 1;*/
    }

    int searching(string key)
    {
        int i = 0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        hits++;

        while(1)
        {
            index = (first + i*second) % size;

            if(table[index].key.compare(key) != 0)
                hits++;
            else
                return table[index].value;

            if(i>0 && index == first)
                return -INF;

            i++;
        }
    }

    void delete_node(string key)
    {
        int i=0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + i*second) % size;

            if(table[index].key.compare(key) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;

                return;
            }

            if(i>0 && index == first)
                return;

            i++;
        }
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};

class Hash_table_custom_probing_1
{
    Hash_node* table;
    int size;
    int* status;

    int collisions;
    int hits;

public:

    Hash_table_custom_probing_1(int s)
    {
        size = s;
        table = new Hash_node[size];
        status = new int[size];

        for(int i=0 ; i<size ; i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        int i=0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(status[index] == 1)
                collisions++;

            else
            {
                table[index].key = key;
                table[index].value = value;
                status[index] = 1;

                return;
            }

            if(i>0 && index == first)
            {
                return;
            }

            i++;
        }

        /*table[index].key = key;
        table[index].value = value;
        status[index] = 1;*/
    }

    int searching(string key)
    {
        int i = 0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        hits++;

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(table[index].key.compare(key) != 0)
                hits++;
            else
                return table[index].value;

            if(i>0 && index == first)
                return -INF;

            i++;
        }
    }

    void delete_node(string key)
    {
        int i=0;
        int index;
        int first = hash_1(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(table[index].key.compare(key) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;

                return;
            }

            if(i>0 && index == first)
                return;

            i++;
        }
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};

class Hash_table_custom_probing_2
{
    Hash_node* table;
    int size;
    int* status;

    int collisions;
    int hits;

public:

    Hash_table_custom_probing_2(int s)
    {
        size = s;
        table = new Hash_node[size];
        status = new int[size];

        for(int i=0 ; i<size ; i++)
        {
            table[i].key = "";
            table[i].value = 0;
            status[i] = 0;
        }

        collisions = 0;
        hits = 0;
    }

    void insert_node(string key , int value)
    {
        int i=0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(status[index] == 1)
                collisions++;

            else
            {
                table[index].key = key;
                table[index].value = value;
                status[index] = 1;

                return;
            }

            if(i>0 && index == first)
            {
                return;
            }

            i++;
        }

        /*table[index].key = key;
        table[index].value = value;
        status[index] = 1;*/
    }

    int searching(string key)
    {
        int i = 0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        hits++;

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(table[index].key.compare(key) != 0)
                hits++;
            else
                return table[index].value;

            if(i>0 && index == first)
                return -INF;

            i++;
        }
    }

    void delete_node(string key)
    {
        int i=0;
        int index;
        int first = hash_2(key , size);
        int second = aux_hash(key , size);

        while(1)
        {
            index = (first + c1*i*second + c2*i*i) % size;

            if(table[index].key.compare(key) == 0)
            {
                table[index].key = "";
                table[index].value = 0;
                status[index] = -1;

                return;
            }

            if(i>0 && index == first)
                return;

            i++;
        }
    }

    int get_collisions()
    {
        return collisions;
    }

    int get_hits()
    {
        return hits;
    }

    double average_hits(double now)
    {
        double d = (double) hits;

        return d/now;
    }
};


int main()
{
    Hash_table_chain_1 htc1(10000);
    Hash_table_chain_2 htc2(10000);
    Hash_table_double_hashing_1 htdh1(10000);
    Hash_table_double_hashing_2 htdh2(10000);
    Hash_table_custom_probing_1 htcp1(10000);
    Hash_table_custom_probing_2 htcp2(10000);

    string* s;
    s = random_generator();

    for(int i=0 ; i<10000 ; i++)
    {
        htc1.insert_node(s[i] , i+1);
        htc2.insert_node(s[i] , i+1);
        htdh1.insert_node(s[i] , i+1);
        htdh2.insert_node(s[i] , i+1);
        htcp1.insert_node(s[i] , i+1);
        htcp2.insert_node(s[i] , i+1);
    }

    for(int i=0 ; i<1000 ; i++)
    {
        htc1.searching(s[i]);
        htc2.searching(s[i]);
        htdh1.searching(s[i]);
        htdh2.searching(s[i]);
        htcp1.searching(s[i]);
        htcp2.searching(s[i]);
    }

    cout<<"                                         Hash_1                                                          Hash_2\n\n";

    cout<<"                      Collisions                          Avg Hits                     Collisions                             Avg Hits\n";

    cout<<"Chaining Method :       "<<htc1.get_collisions()<<"                               "<<htc1.average_hits(1000);
    cout<<"                          "<<htc2.get_collisions()<<"                                  "<<htc2.average_hits(1000)<<endl;

    cout<<"Double Hashing :        "<<htdh1.get_collisions()<<"                            "<<htdh1.average_hits(1000);
    cout<<"                          "<<htdh2.get_collisions()<<"                               "<<htdh2.average_hits(1000)<<endl;

    cout<<"Custom Probing :        "<<htcp1.get_collisions()<<"                            "<<htcp1.average_hits(1000);
    cout<<"                          "<<htcp2.get_collisions()<<"                               "<<htcp2.average_hits(1000)<<endl;
}
