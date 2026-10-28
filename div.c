
#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{
    //Division by zero check 
    if (head2 == NULL || (head2->data == 0 && head2->next == NULL))
    {
        printf("Error: Division by zero is not allowed.\n");
        return;
    }

    // If dividend is less than divisor, quotient is 0 
    if (compare_list(head1, head2) == OPERAND2)
    {
        insert_last(headR, tailR, 0);
        return;
    }

    // If dividend equals divisor, quotient is 1
    if (compare_list(head1, head2) == SAME)
    {
        insert_last(headR, tailR, 1);
        return;
    }

    // Find tail of divisor 
    node *tail2 = head2;
    while (tail2 != NULL && tail2->next != NULL)
    {
        tail2 = tail2->next;
    }

    // Long division 
    node *curr = head1;
    node *bufHead = NULL, *bufTail = NULL;

    while (curr != NULL)
    {
        insert_last(&bufHead, &bufTail, curr->data);
        remove_pre_zeros(&bufHead);

        //Re-align buffer tail 
        if (bufHead != NULL)
        {
            bufTail = bufHead;
            while (bufTail->next != NULL)
            {
                bufTail = bufTail->next;
            }
        }
        else
        {
            bufTail = NULL;
        }

        //Repeated subtraction for current digit 
        int count = 0;
        while (compare_list(bufHead, head2) == OPERAND1 || compare_list(bufHead, head2) == SAME)
        {
            node *diffHead = NULL, *diffTail = NULL;
            subtraction(bufTail, tail2, &diffHead, &diffTail);

            delete_list(&bufHead, &bufTail);
            bufHead = diffHead;
            bufTail = diffTail;

            if (bufHead != NULL)
            {
                bufTail = bufHead;
                while (bufTail->next != NULL)
                {
                    bufTail = bufTail->next;
                }
            }

            count++;
        }

        insert_last(headR, tailR, count);
        curr = curr->next;
    }

    //Free buffer 
    delete_list(&bufHead, &bufTail);

    //Remove leading zeros in quotient 
    remove_pre_zeros(headR);

    // Refresh tailR 
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
