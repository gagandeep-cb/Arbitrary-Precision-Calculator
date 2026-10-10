#include "apc.h"

int main(void)
{
    node *head = NULL;
    node *tail = NULL;

    create_list("000123", &head, &tail);

    printf("Before removing zeros: ");
    print_list(head);

    remove_pre_zeros(&head);

    printf("After removing zeros: ");
    print_list(head);

    delete_list(&head, &tail);

    return 0;
}