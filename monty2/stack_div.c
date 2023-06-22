#include "monty.h"

void stack_div(stack_t **stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "Error: can't div, stack too short\n");
        exit(EXIT_FAILURE);
    }

    if ((*stack)->n == 0)
    {
        fprintf(stderr, "Error: division by zero\n");
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n /= (*stack)->n;
    pop(stack);
}
