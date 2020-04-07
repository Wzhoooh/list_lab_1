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
    struct Node* node;
    struct List* list;
};

struct List* createList();

struct Node* insertAfterIndex(struct List* list, int index, int value);
struct Node* insertFront(struct List* list, int value);
struct Node* insertBack(struct List* list, int value);

void eraseElement(struct List* list, int index); /// delete
void eraseFront(struct List* list);
void eraseBack(struct List* list);

struct Node* getElement(struct List* list, int index);
struct Node* changeElement(struct List* list, int index, int newNal);

int getSize(struct List* list);
void clear(struct List* list);
void print(struct List* list);

struct Iterator* createFrontIterator(struct List* list);
struct Iterator* createBackIterator(struct List* list);
struct Iterator* relocateIterator(struct Iterator* it, int relocateOn);
struct Iterator* erase(struct Iterator* it);
void changeElementIterator(struct Iterator* it, int newNal);
struct Iterator* insertAfterIterator(struct Iterator* it, int value);

void rebuildList(struct Iterator* it);

int getNumOfNode(struct Iterator* it);

#endif // LIST_H_INCLUDED
