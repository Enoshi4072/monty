#include "monty.h"

/* Function to remove the top element from the stack */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *top;
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    top = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(top);
}

