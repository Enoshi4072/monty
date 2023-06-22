#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* Function prototypes */
void push(stack_t **stack, unsigned int line_number, int value);
void pall(stack_t **stack, unsigned int line_number);
void free_stack(stack_t **stack);
void execute_instruction(stack_t **stack, char *opcode, unsigned int line_number);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: monty <file>\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char line[100];
    unsigned int line_number = 0;
    stack_t *stack = NULL;

    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        char *opcode = strtok(line, " \n\t");
        if (opcode == NULL || opcode[0] == '#')
            continue;

        execute_instruction(&stack, opcode, line_number);
    }

    fclose(file);
    free_stack(&stack);

    return EXIT_SUCCESS;
}

/* Function to push an element onto the stack */
void push(stack_t **stack, unsigned int line_number, int value)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        printf("Error: malloc failed\n");
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
    stack_t *current = *stack;
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

/* Function to execute an instruction based on the opcode */
void execute_instruction(stack_t **stack, char *opcode, unsigned int line_number)
{
    if (strcmp(opcode, "push") == 0)
    {
        char *value_str = strtok(NULL, " \n\t");
        if (value_str == NULL)
        {
            printf("L%u: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }

        int value = atoi(value_str);
        if (value == 0 && strcmp(value_str, "0") != 0)
        {
            printf("L%u: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }

        push(stack, line_number, value);
    }
    else if (strcmp(opcode, "pall") == 0)
    {
        pall(stack, line_number);
    }
    // Add more opcode handling here if needed
    else
    {
        printf("L%u: unknown instruction %s\n", line_number, opcode);
        exit(EXIT_FAILURE);
    }
}
