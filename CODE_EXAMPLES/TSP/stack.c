#include "stack.h"

#include <stdlib.h>

//taken from assignment
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

//taken from assignment
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//taken from assignment
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_empty(Stack *s) {
    return (s->top == 0);
}

//replaced capacity-1 with capacity
bool stack_full(Stack *s) {
    return (s->top == s->capacity);
}

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *x = s->items[s->top]; //confused on this
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top; //error handling with capacity?
    for (uint32_t i = 0; i < dst->top; i++) {
        dst->items[i] = src->items[i];
    }
}

//taken from assignment
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
