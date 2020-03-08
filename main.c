#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    struct List* l = createList();
    insertLast(l, 33);
    insertLast(l, 5);
    insertLast(l, 7);
    insertFirst(l, 10);
    printf("size: %d\n", l->size);
    print(l);

    struct Iterator* i = createBackIterator(l);
    printf("value: %d\n", i->node->value);
    printf("nu: %d\n---\n", i->numOfNode);
    relocateIterator(i, -2);
    printf("value: %d\n", i->node->value);
    printf("nu: %d\n------\n", i->numOfNode);
    erase(l, i);
    print(l);

    struct Iterator* i2 = createFrontIterator(l);
    relocateIterator(i2, 1);
    insertAfterIterator(l, i2, 100);
    insertAfterIterator(l, i2, 101);
    print(l);

    struct Iterator* i3 = createBackIterator(l);
    insertAfterIterator(l, i3, 10);
    insertAfterIterator(l, i3, 11);
    print(l);
}
