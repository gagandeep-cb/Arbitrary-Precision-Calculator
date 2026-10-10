#include "apc.h"

int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        return FAILURE;
    }

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head == NULL)
    {
        *tail = new;
    }
    else
    {
        (*head)->prev = new;
    }

    *head = new;

    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        return FAILURE;
    }

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;
        *tail = new;
    }

    return SUCCESS;
}

void create_list(char *operand, node **head, node **tail)
{
    int i = 0;

    while (operand[i] != '\0')
    {
        int digit = operand[i] - '0';

        if (insert_last(head, tail, digit) == FAILURE)
        {
            delete_list(head, tail);
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        i++;
    }
}
void print_list(node *head)
{
    node *temp = head;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int delete_list(node **head, node **tail)
{
    node *temp = *head;
    node *next = NULL;

    if (*head == NULL)
    {
        return FAILURE;
    }

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}
int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    node *temp1 = head1;
    node *temp2 = head2;

    //Compare the number of digits 
    if (len1 > len2)
    {
        return OPERAND1;
    }

    if (len2 > len1)
    {
        return OPERAND2;
    }

// Compare digits from left to right 
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
        {
            return OPERAND1;
        }

        if (temp1->data < temp2->data)
        {
            return OPERAND2;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return SAME;
}

int list_len(node *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

void remove_pre_zeros(node **head)
{
    node *temp;

    if (*head == NULL)
    {
        return;
    }

    while ((*head)->data == 0 && (*head)->next != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}