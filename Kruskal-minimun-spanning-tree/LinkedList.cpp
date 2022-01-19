#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedList
{
public:

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        return SUCCESS_VALUE ;
    }

    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }


    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",length);
    }

    //------------write code for the functions below-----------

    int insertLast(int item)
    {
        ListNode * newNode;
        ListNode * temp;
        ListNode* anotherTemp = NULL;
        temp = list;
        while(temp!=NULL)
        {
            anotherTemp = temp;
            temp = temp->next;
        }
        newNode = new ListNode();
        newNode->item = item;
        anotherTemp->next = newNode;
        newNode->next = NULL;
        length++;
        return SUCCESS_VALUE;
    }

    int insertAfter(int oldItem, int newItem)
    {
        ListNode* fromSearch = searchItem(oldItem);
        if(fromSearch != NULL)
        {
            ListNode* newNode = new ListNode();
            newNode->item = newItem;
            newNode->next = fromSearch->next;
            fromSearch->next = newNode;
            length++;
            return SUCCESS_VALUE;
        }
        return NULL_VALUE;
    }

    ListNode * getItemAt(int pos)
    {
         if(pos<=length)
         {
             ListNode* temp;
             temp = list;
             for(int i = 1;i<pos;i++)
                temp = temp->next;
             return temp;
         }
         return NULL;
    }

    int deleteFirst()
    {
        ListNode* temp = list;
        if(temp!=NULL)
        {
            int firstNumber = list->item;
            list = list->next;
            /*temp->item = NULL;
            free(temp);*/
            delete temp;
            length--;
            return firstNumber;
        }
        return NULL_VALUE;
    }


    ~LinkedList()
    {

        while(list != NULL)
        {
            ListNode* temp = list;
            list = list->next;
            /*temp->item = NULL;
            free(temp);*/
            delete temp;
        }
        free(list);
        length = 0;
    }

};

/*int main(void)
{
    LinkedList ll;

    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert new item at last. 5. Insert an item after another item. \n");
        printf("6. Delete the first item. 7.Get an item from a position. \n");
        printf("8. Print. 9.Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            ll.insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            ll.deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==8)
        {
            ll.printList();
        }
        else if(ch==9)
        {
            break;
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            ll.insertLast(item);
        }
        else if(ch==5)
        {
            int item1;
            printf("New item : ");
            scanf("%d",&item1);
            int item2;
            printf("Existed item : ");
            scanf("%d",&item2);
            ll.insertAfter(item2,item1);
        }
        else if(ch==6)
        {
            ll.deleteFirst();
            printf("Deleted\n");
        }
        else if(ch==7)
        {
            int pos;
            printf("Position : ");
            scanf("%d",&pos);
            ListNode* temp = ll.getItemAt(pos);
            if(temp!=NULL)
                printf("%d\n",temp->item);
            else
                printf("Not found \n");
        }

    }

}*/
