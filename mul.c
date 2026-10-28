
#include "apc.h"

void multiplication(node *tail1, node *tail2,
                    node **headR, node **tailR)
{
    node *temp1, *temp2;
    node *headP = NULL, *tailP = NULL;
    node *headSum = NULL, *tailSum = NULL;
    int product, carry, zeros, i;

    temp2 = tail2;
    zeros = 0;

    while (temp2 != NULL)
    {
        temp1 = tail1;
        carry = 0;

        // Multiply by the current digit of operand 2 
        while (temp1 != NULL)
        {
            product = temp1->data * temp2->data + carry;

            if (insert_first(&headP, &tailP, product % 10) == FAILURE)
            {
                printf("Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            carry = product / 10;
            temp1 = temp1->prev;
        }

        if (carry != 0)
        {
            if (insert_first(&headP, &tailP, carry) == FAILURE)
            {
                printf("Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        // Append zeros for decimal-place shifting 
        for (i = 0; i < zeros; i++)
        {
            if (insert_last(&headP, &tailP, 0) == FAILURE)
            {
                printf("Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        if (*headR == NULL)
        {
            *headR = headP;
            *tailR = tailP;
        }
        else
        {
            headSum = NULL;
            tailSum = NULL;

            addition(*tailR, tailP, &headSum, &tailSum);

            delete_list(headR, tailR);
            delete_list(&headP, &tailP);

            *headR = headSum;
            *tailR = tailSum;
        }

        headP = NULL;
        tailP = NULL;

        temp2 = temp2->prev;
        zeros++;
    }

    remove_pre_zeros(headR);

    // Refresh tail 
    temp1 = *headR;
    while (temp1 != NULL && temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    *tailR = temp1;
}

