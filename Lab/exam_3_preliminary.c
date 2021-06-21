#include "stdio.h"
#include "stdlib.h"
#include "lab3.h"

Student** create_student_array(int* student_id_list, int student_count)
{
    int i;
    Student *p, **stdp = malloc(sizeof(p)*student_count);
    for (i=0 ; i<student_count ; i++)
    {
        stdp[i] = malloc(sizeof(Student));
        stdp[i]->studentID = student_id_list[i];
    }
    return stdp;
}

Node* insert_head(Node* head, int new_node_data)
{
    Node *newhead = malloc(sizeof(Node));
    newhead->data = new_node_data;
    newhead->next = head;
    return newhead;
}

Node* remove_kth_node(Node* head, int index)
{
    int i;
    Node *prev=malloc(sizeof(Node)), *follow=head, *curr=head;
    
    if (index == 0)
    {
        if (head->next != NULL) head = head->next;
        else return NULL;
    }
    
    for (i=0 ; i<index ; i++)
    {
        if (i == index-1)
        {
            prev = curr;
        }
        curr = curr->next;
    }

    if (curr->next == NULL)
    {
        prev->next = NULL;
    }
    else
    {
        follow = curr->next;
        prev->next = follow;
    }
    
    return head;
}

int find_occurrences(Node* head, int data)
{
    Node *curr = head;
    int i=0;
    
    if (head == NULL) return i;
    
    while (curr->next != NULL)
    {
        if (data == curr->data) i+=1;
        curr = curr->next;
    }
    if (data == curr->data) i+=1;
    
    return i;
}

Node* copy_to_head(Node* head, int index)
{
    
    Node *curr=head;
    int *marr = NULL;
    int len, i, j;
    
    if (head==NULL) return NULL;
    
    for (len=0 ; curr->next!=NULL ; len++, curr=curr->next);
    len += 1;
    curr=head;

    marr = malloc(sizeof(head) * (len+1));
    
    for (i=0, j=0 ; i<len ; i++)
    {
        if (i >= index) marr[j++] = curr->data;
        curr = curr->next;
    }

    for (j-=1 ; j!=-1 ; j--)
    {
        head = insert_head(head, marr[j]);
    }
    
    return head;
}

Node* sum_consecutive_pairs(Node* head)
{
    
    int *sums = NULL, i=0, len;
    Node *curr = head, *later = (head->next);
    
    for (len=0 ; curr->next!=NULL ; len++, curr=curr->next);
    len += 1;
    curr=head;
    sums = malloc(sizeof(int) * len);
    
    while (later != NULL)
    {
        sums[i++] = curr->data + later->data;
        curr = curr->next;
        later = later->next;
    }
    
    for (len=i, i=0, curr=head ; i<len ; i++)
    {
        curr->data = sums[i];
        if (i == len-1) curr->next = NULL;
        else curr = curr->next;
    }
    
    return head;
}
