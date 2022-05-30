/* Mihăilă Octavian-Iulian - 315CB */
/* Dobre Emilia-Iliana - 315CB */
/* StackFunctions.c -- elementele stivei sunt memorate intr-o lista generica */

#include "stack.h"

stack push(stack *s, void *info) {
    stack new_elem = (stack)calloc(1, sizeof(stack_element));
    new_elem->prev = *s;

    new_elem->data = info;

    return new_elem;
}

stack pop(stack *s) {
    stack elem = *s;
    *s = (*s)->prev;

    return elem;
}