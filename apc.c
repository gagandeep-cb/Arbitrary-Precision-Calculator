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
