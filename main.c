#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "time.h"

int main()
{
    struct List* l = createList();
    insertBack(l, 33);
    insertBack(l, 5);
    insertBack(l, 7);
    insertFront(l, 10);
    printf("size: %d\n", l->size);
    print(l);
printf("----i1--\n");
    struct Iterator* i = createBackIterator(l);
    printf("value: %d\n", i->node->value);
    printf("nu: %d\n---\n", i->numOfNode);
    relocateIterator(i, -2);
    printf("value: %d\n", i->node->value);
    printf("nu: %d\n------\n", i->numOfNode);
    //erase(i);
    print(l);
printf("----i2--\n");
    struct Iterator* i2 = createFrontIterator(l);
    relocateIterator(i2, 1);
    insertAfterIterator(i2, 100);
    insertAfterIterator(i2, 101);
    insertAfterIterator(i2, 103);
    insertAfterIndex(l, 4, 666);
    print(l);
printf("----i3--\n");
    struct Iterator* i3 = createBackIterator(l);
    insertAfterIterator(i3, 10);
    insertAfterIterator(i3, 11);
    insertAfterIterator(i3, 2);
    insertAfterIterator(i3, 2);
    print(l);
printf("----i4--\n");
    struct Iterator* i4 = createFrontIterator(l);
//        printf("num: %d     ", i4->numOfNode);
//        printf("value: %d\n", i4->node->value);
    relocateIterator(i4, -5);
    erase(i4);
    print(l);
    relocateIterator(i4, -6);
    erase(i4); print(l);
    erase(i4); print(l);
    erase(i4); print(l);
printf("----i5--\n");
    struct Iterator* i5 = createBackIterator(l);
    erase(i5); print(l);
    erase(i5); print(l);
    erase(i5); print(l);


}
