#include "monty.h"

void swap(stack_t **stack)
{
	int temp;
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "Error: can't swap, stack too short\n");
        exit(EXIT_FAILURE);
    }

    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}

