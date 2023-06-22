#include "monty.h"

int main(int argc, char *argv[])
{
	FILE *file;
	char line[100];
	unsigned int line_number;
	char *opcode;
	stack_t *stack;
    if (argc != 2)
    {
        printf("Usage: monty <file>\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    line_number = 0;
    stack = NULL;

    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        opcode = strtok(line, " \n\t");
        if (opcode == NULL || opcode[0] == '#')
            continue;

        execute_instruction(&stack, opcode, line_number);
    }

    fclose(file);
    free_stack(&stack);

    return EXIT_SUCCESS;
}
