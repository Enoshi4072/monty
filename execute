#include "monty.h"
void execute_instruction(stack_t **stack, char *opcode, unsigned int line_number)
{
	char *value_str;
	int value;
    if (strcmp(opcode, "push") == 0)
    {
        value_str = strtok(NULL, " \n\t");
        if (value_str == NULL)
        {
            printf("L%u: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }

        value = atoi(value_str);
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
    else if (strcmp(opcode, "pint") == 0)
{
    pint(stack, line_number);
}

    else
    {
        printf("L%u: unknown instruction %s\n", line_number, opcode);
        exit(EXIT_FAILURE);
    }
}
