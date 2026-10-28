#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int digit1, digit2;
    int diff;
    int borrow = 0;

    node *temp1 = tail1;
    node *temp2 = tail2;

    while (temp1 != NULL)
    {
        digit1 = temp1->data - borrow;
        digit2 = 0;

        if (temp2 != NULL)
        {
            digit2 = temp2->data;
            temp2 = temp2->prev;
        }

        borrow = 0;

        if (digit1 < digit2)
        {
            digit1 = digit1 + 10;
            borrow = 1;
        }

        diff = digit1 - digit2;

        if (insert_first(headR, tailR, diff) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            exit(EXIT_FAILURE);
        }

        temp1 = temp1->prev;
    }

    remove_pre_zeros(headR);

    if (*headR != NULL)
    {
        node *temp = *headR;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        *tailR = temp;
    }
    else
    {
        *tailR = NULL;
    }
}
