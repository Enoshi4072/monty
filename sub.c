#include "monty.h"

void sub(stack_t **stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "Error: can't sub, stack too short\n");
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n -= (*stack)->n;
    pop(stack);
}

