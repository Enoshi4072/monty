#include "monty.h"

void pop(stack_t **stack)
{
        stack_t *top;
    if (*stack == NULL)
    {
        fprintf(stderr, "Error: can't pop an empty stack\n");
        exit(EXIT_FAILURE);
    }

    top = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(top);
}
