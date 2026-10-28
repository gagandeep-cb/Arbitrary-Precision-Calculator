#include "apc.h"

void addition(node *tail1, node *tail2,
              node **headR, node **tailR)
{
    int sum, carry = 0, digit;

    node *temp1 = tail1;
    node *temp2 = tail2;

    while (temp1 != NULL || temp2 != NULL || carry != 0)
    {
        sum = carry;

        if (temp1 != NULL)
        {
            sum += temp1->data;
            temp1 = temp1->prev;
        }

        if (temp2 != NULL)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }

        digit = sum % 10;
        carry = sum / 10;

        if (insert_first(headR, tailR, digit) == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(headR, tailR);
            exit(EXIT_FAILURE);
        }
    }
}
