
/*
---------------- Project Details --------------------

Project Name : Arbitrary Precision Calculator (APC)

Name         : Gagandeep C Banakar

Project Type : Data Structures and Algorithms in C 

Data Structure: Doubly Linked List (DLL)

Date: 12/10/2026 to 28/10/2026

Description  :
The Arbitrary Precision Calculator (APC) is a C-based project
designed to perform arithmetic operations on large integers
that exceed the limits of standard C data types.

It uses a Doubly Linked List to store and process individual
digits and Command-Line Arguments (CLA) to receive operands
and operators.

The project supports addition, subtraction, multiplication,
and division of large integers.

Key Concepts Used:
1. Doubly Linked List
2. Dynamic Memory Allocation
3. Pointers
4. Command-Line Arguments
5. Functions and Modular Programming
6. Arithmetic Algorithms

------------------------------------------------------
*/


#include "apc.h"

int main(int argc, char *argv[])
{
node *head1 = NULL, *tail1 = NULL;
node *head2 = NULL, *tail2 = NULL;
node *headR = NULL, *tailR = NULL;


// Step 1: Validate CLA 
if (cla_validation(argc, argv) == FAILURE)
{
    return 1;
}

// Step 2: Create lists for both operands 
create_list(argv[1], &head1, &tail1);
create_list(argv[3], &head2, &tail2);

// Step 3: Remove leading zeros 
remove_pre_zeros(&head1);
remove_pre_zeros(&head2);

tail1 = head1;
tail2 = head2;

while (tail1->next != NULL)
{
    tail1 = tail1->next;
}

while (tail2->next != NULL)
{
    tail2 = tail2->next;
}

// Step 4: Identify signs and operator 
char oper = argv[2][0];
int sign1 = (argv[1][0] == '-') ? -1 : 1;
int sign2 = (argv[3][0] == '-') ? -1 : 1;
int result_sign = 1;

// Step 5: Perform arithmetic operation 
switch (oper)
{
    case '+':
    {
        if (sign1 == sign2)
        {
            result_sign = sign1;
            addition(tail1, tail2, &headR, &tailR);
        }
        else
        {
            int cmp = compare_list(head1, head2);
            if (cmp == SAME)
            {
                subtraction(tail1, tail2, &headR, &tailR);
                result_sign = 1;
            }
            else if (cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);
                result_sign = sign2;
            }
        }
        break;
    }

    case '-':
    {
        int eff_sign2 = -sign2;

        if (sign1 == eff_sign2)
        {
            result_sign = sign1;
            addition(tail1, tail2, &headR, &tailR);
        }
        else
        {
            int cmp = compare_list(head1, head2);
            if (cmp == SAME)
            {
                subtraction(tail1, tail2, &headR, &tailR);
                result_sign = 1;
            }
            else if (cmp == OPERAND1)
            {
                subtraction(tail1, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                subtraction(tail2, tail1, &headR, &tailR);
                result_sign = eff_sign2;
            }
        }
        break;
    }

    case '*':
    case 'x':
    case 'X':
    {
        result_sign = (sign1 == sign2) ? 1 : -1;
        multiplication(tail1, tail2, &headR, &tailR);
        break;
    }

    case '/':
    {
        result_sign = (sign1 == sign2) ? 1 : -1;
        division(head1, head2, &headR, &tailR);
        break;
    }

    default:
        printf("Invalid operator\n");
        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);
        return 1;
}

// Step 6: Display the result
printf("Result: ");
if (result_sign == -1 && headR != NULL && (headR->data != 0 || headR->next != NULL))
{
    printf("-");
}
print_list(headR);

// Step 7: Free allocated memory 
delete_list(&head1, &tail1);
delete_list(&head2, &tail2);
delete_list(&headR, &tailR);

return 0;


}
