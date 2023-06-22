#include "monty.h"
 /* Function to print the value at the top of the stack */
void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        printf("L%u: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}

