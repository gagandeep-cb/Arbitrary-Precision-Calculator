#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;

    // Validation

    // Create 2 lists of operands

    // Remove pre zeros

    char oper = argv[2][0];

    switch(oper)
    {
	case '+':
	    addition(tail1, tail2, &headR, &tailR);
	    break;

	case '-':
	    break;

	case 'x':
	case 'X':
	    break;

	case '/':
	    break;

	default:
	    printf("Invalid operator\n");
    }
}

