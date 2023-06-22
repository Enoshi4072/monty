#include "monty.h"

/**
 * push - Pushes an element to the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number being executed.
 * @n: Value to push.
 */
void push(stack_t **stack, unsigned int line_number, int n)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }

    new_node->n = n;
    new_node->prev = NULL;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    new_node->next = *stack;
    *stack = new_node;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number being executed.
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *temp = *stack;

    while (temp != NULL)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

/**
 * free_stack - Frees a stack.
 * @stack: Pointer to the stack.
 */
void free_stack(stack_t *stack)
{
    stack_t *temp;

    while (stack != NULL)
    {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}

