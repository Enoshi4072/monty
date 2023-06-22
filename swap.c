#include "monty.h"

/* Function to swap the top two elements of the stack */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;
    if (*stack == NULL || (*stack)->next == NULL)
    {
        printf("L%u: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
}
