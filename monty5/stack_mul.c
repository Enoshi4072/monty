#include "monty.h"

void stack_mul(stack_t **stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "Error: can't mul, stack too short\n");
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n *= (*stack)->n;
    pop(stack);
}

