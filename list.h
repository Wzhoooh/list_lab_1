#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>

struct List;
struct Node;
struct Iterator;

struct List
{
    struct Node* pFirst;
    struct Node* pLast;
    int size;
};

struct Node
{
    int value;
    struct Node* pNext;
    struct Node* pPrev;
};

struct Iterator
{
    int numOfNode;
    struct Node* node;
};

struct List* createList();

struct Node* insertAfterIndex(struct List* list, int index, int value);
struct Node* insertFirst(struct List* list, int value);
struct Node* insertLast(struct List* list, int value);

void deleteElement(struct List* list, int index); /// delete
void deleteFirst(struct List* list);
void deleteLast(struct List* list);

struct Node* getElement(struct List* list, int index);
struct Node* changeElement(struct List* list, int index, int newNal);

int getSize(struct List* list);
void clear(struct List* list);
void print(struct List* list);

struct Iterator* createFrontIterator(struct List* list);
struct Iterator* createBackIterator(struct List* list);
struct Iterator* relocateIterator(struct Iterator* it, int relocateOn);
void erase(struct List* list, struct Iterator* it);
void changeElementIterator(struct Iterator* it, int newNal);
struct Iterator* insertAfterIterator(struct List* list, struct Iterator* it, int value);

#endif // LIST_H_INCLUDED
