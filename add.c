#include "monty.h"
/**
 * add - Adds the top two elements of the stack.
 * @stack: Pointer to the stack.
 *
 * Description: Adds the top two elements of the stack. The result is stored in
 * the second element from the top, and the top element is removed.
 * If the stack contains less than two elements, an error is raised.
 */

void add(stack_t **stack)
{
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "Error: can't add, stack too short\n");
exit(EXIT_FAILURE);
}
(*stack)->next->n += (*stack)->n;
pop(stack);
}


