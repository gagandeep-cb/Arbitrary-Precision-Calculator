#include "apc.h"

int cla_validation(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Error: Invalid number of arguments.\n");
        printf("Usage: ./a.out <operand1> <operator> <operand2>\n");
        return FAILURE;
    }

    // Validate operator: must be 1 character: +, -, *, x, X, 
    if (strlen(argv[2]) != 1)
    {
        printf("Error: Invalid operator. Supported operators: +, -, '*', x, X, /\n");
        return FAILURE;
    }

    char op = argv[2][0];
    if (op != '+' && op != '-' && op != '*' && op != 'x' && op != 'X' && op != '/')
    {
        printf("Error: Invalid operator '%c'. Supported operators: +, -, *, x, X, /\n", op);
        return FAILURE;
    }

    //Validate operand 1: optional sign (+/-) followed by digits 
    int i = 0;
    if (argv[1][0] == '\0')
    {
        printf("Error: Operand 1 is empty.\n");
        return FAILURE;
    }
    if (argv[1][0] == '+' || argv[1][0] == '-')
    {
        i++;
        if (argv[1][i] == '\0')
        {
            printf("Error: Operand 1 has sign but no digits.\n");
            return FAILURE;
        }
    }
    while (argv[1][i] != '\0')
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Error: Operand 1 contains non-digit character '%c'.\n", argv[1][i]);
            return FAILURE;
        }
        i++;
    }

    // Validate operand 2: optional sign (+/-) followed by digits 
    i = 0;
    if (argv[3][0] == '\0')
    {
        printf("Error: Operand 2 is empty.\n");
        return FAILURE;
    }
    if (argv[3][0] == '+' || argv[3][0] == '-')
    {
        i++;
        if (argv[3][i] == '\0')
        {
            printf("Error: Operand 2 has sign but no digits.\n");
            return FAILURE;
        }
    }
    while (argv[3][i] != '\0')
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
            printf("Error: Operand 2 contains non-digit character '%c'.\n", argv[3][i]);
            return FAILURE;
        }
        i++;
    }

    // Validate division by zero 
    if (op == '/')
    {
        int all_zeros = 1;
        i = (argv[3][0] == '+' || argv[3][0] == '-') ? 1 : 0;
        for (; argv[3][i] != '\0'; i++)
        {
            if (argv[3][i] != '0')
            {
                all_zeros = 0;
                break;
            }
        }
        if (all_zeros)
        {
            printf("Error: Division by zero is not allowed.\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}

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

    if (operand[0] == '+' || operand[0] == '-')
    {
        i = 1;
    }

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