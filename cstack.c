#include "cstack.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_QUANTITY 10

static struct stack_entry stack_table[MAX_STACK_QUANTITY];

hstack_t stack_new()
{
    for (int i = 0; i < MAX_STACK_QUANTITY; i++)
    {
        if (stack_table[i].is_busy)
            continue;
        
        stack_table[i].is_busy = true;

        return i;
    }

    return -1;
}

int stack_valid_handler(const hstack_t stack)
{
    if ((stack < 0) || (stack > (MAX_STACK_QUANTITY - 1)))
        return 1; //ok...
    
    if (!stack_table[stack].is_busy)
        return 1; //ok...

    return 0; //ok...
}

void stack_free(const hstack_t stack)
{
    if (stack_valid_handler(stack))
        return;
    
    struct node *prev = NULL;

    for (struct node *p = stack_table[stack].last_node; p != NULL; p = prev)
    {
        prev = p->prev;

        free(p); //deallocate node + data
    }

    stack_table[stack].is_busy = false;
    stack_table[stack].count = 0;
    stack_table[stack].last_node = NULL;
}

unsigned int stack_size(const hstack_t stack)
{
    if (stack_valid_handler(stack))
        return 0;
    
    return stack_table[stack].count;
}

void stack_push(const hstack_t stack, const void *data_in, const unsigned int size)
{
    if (stack_valid_handler(stack) || !data_in || !size)
        return;

    struct node *new_node = malloc(sizeof(struct node) + size); //allocate block for node + data_in
    
    if (!new_node)
        return;
    
    new_node->size = size;
    new_node->data = (unsigned char *)new_node + sizeof(struct node);
    new_node->prev = stack_table[stack].last_node;
    
    memcpy(new_node->data, data_in, size);

    stack_table[stack].last_node = new_node;
    stack_table[stack].count++;
}

unsigned int stack_pop(const hstack_t stack, void *data_out, const unsigned int size)
{
    if (stack_valid_handler(stack) || !data_out || !size)
        return 0;

    if (stack_size(stack) == 0)
        return 0;

    struct node *last_node = stack_table[stack].last_node;

    if (last_node->size > size)
        return 0;

    memcpy(data_out, last_node->data, size);

    stack_table[stack].last_node = last_node->prev;
    stack_table[stack].count--;

    free(last_node); //deallocate node + data

    return size;
}