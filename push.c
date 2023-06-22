#include "monty.h"

/* Function to push an element onto the stack */
void push(stack_t **stack, unsigned int line_number, int value)
{
	stack_t *new_node;
	(void)line_number;
    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
        (*stack)->prev = new_node;

    *stack = new_node;
}

/* Function to print all values on the stack */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;
	(void)line_number;
    current = *stack;
    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/* Function to free the stack */
void free_stack(stack_t **stack)
{
    stack_t *current = *stack;
    stack_t *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *stack = NULL;
}
