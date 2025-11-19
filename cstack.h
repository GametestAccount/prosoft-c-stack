#ifndef CSTACK_H
#define CSTACK_H

#include <stdbool.h>

typedef int hstack_t;

struct node
{
    unsigned int size;
    void *data;
    struct node *prev;
};

struct stack_entry
{
    bool is_busy;
    unsigned int count;
    struct node *last_node;
};

hstack_t stack_new();

int stack_valid_handler(const hstack_t stack);

void stack_free(const hstack_t stack);

unsigned int stack_size(const hstack_t stack);

void stack_push(const hstack_t stack, const void *data_in, const unsigned int size);

unsigned int stack_pop(const hstack_t stack, void *data_out, const unsigned int size);

#endif /* CSTACK_H */
