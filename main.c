#include "apc.h"

int main(int argc, char *argv[])
{
node *head1 = NULL, *tail1 = NULL;
node *head2 = NULL, *tail2 = NULL;
node *headR = NULL, *tailR = NULL;


/* Step 1: Validate CLA */
if (cla_validation(argc, argv) == FAILURE)
{
    return FAILURE;
}

/* Step 2: Create lists for both operands */
create_list(argv[1], &head1, &tail1);
create_list(argv[3], &head2, &tail2);

/* Step 3: Remove leading zeros */
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

/* Step 4: Identify the operator */
char oper = argv[2][0];

/* Step 5: Perform arithmetic operation */
switch (oper)
{
    case '+':
        addition(tail1, tail2, &headR, &tailR);
        break;

    case '-':
        subtraction(tail1, tail2, &headR, &tailR);
        break;

    case 'x':
    case 'X':
        multiplication(tail1, tail2, &headR, &tailR);
        break;

    case '/':
        division(head1, head2, &headR, &tailR);
        break;

    default:
        printf("Invalid operator\n");
        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);
        return FAILURE;
}

/* Step 6: Display the result */
printf("Result: ");
print_list(headR);

/* Step 7: Free allocated memory */
delete_list(&head1, &tail1);
delete_list(&head2, &tail2);
delete_list(&headR, &tailR);

return SUCCESS;


}
