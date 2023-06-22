#include "monty.h"

typedef void (*OpcodeFunction)(stack_t**);

void process_opcode(FILE* file, stack_t** stack, unsigned int* line_number);
void push(stack_t** stack, int value);
void pall(stack_t** stack);
void pint(stack_t** stack);
void pop(stack_t** stack);
void swap(stack_t** stack);
void add(stack_t** stack);
void nop(stack_t** stack);
void sub(stack_t** stack);
void stack_div(stack_t** stack);
void stack_mul(stack_t** stack);
void stack_mod(stack_t** stack);

typedef struct {
    char opcode[5];
    OpcodeFunction function;
} OpcodeEntry;

OpcodeEntry opcodeTable[] = {
    { "pint", pint },
    { "pop", pop },
    { "swap", swap },
    { "add", add },
    { "nop", nop },
    { "sub", sub },
    { "div", stack_div },
    { "mul", stack_mul },
    { "mod", stack_mod },
};

int main(int argc, char* argv[])
{
    FILE* file;
    stack_t* stack;
    unsigned int line_number;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    stack = NULL;
    line_number = 1;

    while (!feof(file))
    {
        process_opcode(file, &stack, &line_number);
        line_number++;
    }

    fclose(file);
    free(stack);
    return EXIT_SUCCESS;
}

void process_opcode(FILE* file, stack_t** stack, unsigned int* line_number)
{
    char opcode[20];
    int numOpCodes;
    int i;
    OpcodeFunction function;

    if (fscanf(file, "%19s", opcode) != 1)
    {
        fprintf(stderr, "Error: invalid opcode at line %u\n", *line_number);
        exit(EXIT_FAILURE);
    }

    if (strcmp(opcode, "push") == 0)
    {
        int value;
        if (fscanf(file, "%d", &value) != 1)
        {
            fprintf(stderr, "L%u: usage: push integer\n", *line_number);
            exit(EXIT_FAILURE);
        }
        push(stack, value);
        return;
    }

    if (strcmp(opcode, "pall") == 0)
    {
        pall(stack);
        return;
    }

    numOpCodes = sizeof(opcodeTable) / sizeof(opcodeTable[0]);
    function = NULL;

    for (i = 0; i < numOpCodes; i++)
    {
        if (strcmp(opcodeTable[i].opcode, opcode) == 0)
        {
            function = opcodeTable[i].function;
            break;
        }
    }

    if (function != NULL)
    {
        function(stack);
    }
    else
    {
        fprintf(stderr, "L%u: unknown instruction %s\n", *line_number, opcode);
        exit(EXIT_FAILURE);
    }
}

void push(stack_t** stack, int value)
{
    stack_t* new_node = (stack_t*)malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->next = *stack;
    *stack = new_node;
}

void pall(stack_t** stack)
{
    stack_t* current = *stack;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void pint(stack_t** stack)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pint, stack empty\n", *line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->data);
}

void pop(stack_t** stack)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%u: can't pop an empty stack\n", *line_number);
        exit(EXIT_FAILURE);
    }

    stack_t* temp = *stack;
    *stack = (*stack)->next;
    free(temp);
}

void swap(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't swap, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int temp = (*stack)->data;
    (*stack)->data = (*stack)->next->data;
    (*stack)->next->data = temp;
}

void add(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't add, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int sum = (*stack)->data + (*stack)->next->data;
    pop(stack);
    (*stack)->data = sum;
}

void nop(stack_t** stack)
{
    (void)stack; // Unused parameter, avoids compiler warning
    return;
}

void sub(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't sub, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int sub = (*stack)->next->data - (*stack)->data;
    pop(stack);
    (*stack)->data = sub;
}

void stack_div(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't div, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->data == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int div = (*stack)->next->data / (*stack)->data;
    pop(stack);
    (*stack)->data = div;
}

void stack_mul(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mul, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int mul = (*stack)->data * (*stack)->next->data;
    pop(stack);
    (*stack)->data = mul;
}

void stack_mod(stack_t** stack)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%u: can't mod, stack too short\n", *line_number);
        exit(EXIT_FAILURE);
    }

    if ((*stack)->data == 0)
    {
        fprintf(stderr, "L%u: division by zero\n", *line_number);
        exit(EXIT_FAILURE);
    }

    int mod = (*stack)->next->data % (*stack)->data;
    pop(stack);
    (*stack)->data = mod;
}

