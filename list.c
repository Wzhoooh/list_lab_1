#include "list.h"
#include <stdlib.h>
#include <stdio.h>

struct List* createList()
{
    /// сдедать проверку на null
    struct List* newList = (struct List*) malloc(sizeof(struct List) * 1);
    if (newList == NULL)
        return NULL;

    newList->pFirst = NULL;
    newList->pLast = NULL;
    newList->size = 0;
    return newList;
};

struct Node* insertAfterIndex(struct List* list, int index, int value)
{
    struct Node* newNode = NULL;
    if (index >= list->size || index < 0)
        return NULL;

    if (index == list->size-1)
    {
        newNode = insertBack(list, value);
        return newNode;
    }

    struct Node* node = list->pFirst;
    for (int i = 0; i != index; i++)
        node = node->pNext;

    newNode = (struct Node*) malloc(sizeof(struct Node) * 1);
    if (newNode == NULL)
        return NULL;

    newNode->value = value;

    newNode->pPrev = node;
    newNode->pNext = node->pNext;
    node->pNext->pPrev = newNode;
    node->pNext = newNode;

    list->size++;
    return newNode;
}

struct Node* insertFront(struct List* list, int value)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node) * 1);
    if (newNode == NULL)
        return NULL;

    newNode->value = value;

    /// create first node
    if (list->size == 0)
    {
        newNode->pPrev = NULL;
        newNode->pNext = NULL;
        list->pFirst = newNode;
        list->pLast = newNode;
    }
    else
    {
        newNode->pNext = list->pFirst;
        newNode->pPrev = NULL;
        list->pFirst->pPrev = newNode;
        list->pFirst = newNode;
    }

    list->size++;
    return newNode;
}

struct Node* insertBack(struct List* list, int value)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node) * 1);
    if (newNode == NULL)
        return NULL;

    newNode->value = value;

    /// create first node
    if (list->size == 0)
    {
        newNode->pPrev = NULL;
        newNode->pNext = NULL;
        list->pFirst = newNode;
        list->pLast = newNode;
    }
    else
    {
        newNode->pNext = NULL;
        newNode->pPrev = list->pLast;
        list->pLast->pNext = newNode;
        list->pLast = newNode;
    }

    list->size++;
    return newNode;
}

struct Node* getElement(struct List* list, int index)
{
    if (index >= list->size || index < 0)
        return NULL;

    if (index >= list->size / 2)
    {
        /// движемся с конца в начало
        struct Node* node = list->pLast;
        for (int i = list->size-1; i > index ; i--)
            node = node->pPrev;

        return node;
    }
    else
    {
        /// движемся из начала в конец
        struct Node* node = list->pFirst;

        for (int i = 0; i < index; i++)
            node = node->pNext;

        return node;
    }
    return NULL;
}

struct Node* changeElement(struct List* list, int index, int newVal)
{
    if (index < 0 || index >= list->size)
        return NULL;

    struct Node* node = list->pFirst;
    for (int i = 0; i < index; i++)
        node = node->pNext;

    node->value = newVal;
    return node;
};

void eraseElement(struct List* list, int index)
{
    if (index < 0 || index >= list->size)
        return;

    if (index == 0)
    {
        eraseFront(list);
        return;
    }

    if (index == list->size-1)
    {
        eraseBack(list);
        return;
    }

    struct Node* node = list->pFirst;
    for (int i = 0; i < index; i++)
        node = node->pNext;

    node->pPrev->pNext = node->pNext;
    node->pNext->pPrev = node->pPrev;

    list->size--;
    free(node);
}

void eraseFront(struct List* list)
{
    if (list->size == 0)
        return;

    if (list->size == 1)
    {
        struct Node* node = list->pFirst;
        list->pFirst = NULL;
        list->pLast = NULL;

        list->size = 0;
        free(node);
        return;
    }

    struct Node* node = list->pFirst;
    list->pFirst = node->pNext;
    list->pFirst->pPrev = NULL;

    list->size--;
    free(node);
}

void eraseBack(struct List* list)
{
    if (list->size == 0 || list->size == 1)
    {
        eraseFront(list);
        return;
    }

    struct Node* node = list->pLast;
    list->pLast = node->pPrev;
    list->pLast->pNext = NULL;

    list->size--;
    free(node);
}

int getSize(struct List* list)
{
    return list->size;
}

void clear(struct List* list)
{
    struct Node* node = list->pFirst;
    for (int i = 0; i < list->size; i++)
    {
        struct Node* nextNode = node;
        free(node);
        node = nextNode;
    }

    list->size = 0;
    list->pFirst = NULL;
    list->pLast = NULL;
}

void print(struct List* list)
{
    if (list->size == 0)
    {
        printf("\n");
        return;
    }

    struct Node* node = list->pFirst;
    for (int i = 0; i < list->size; i++)
    {
        printf("%5d|", node->value);
        node = node->pNext;
    }
    printf("\n");
}

struct Iterator* createFrontIterator(struct List* list)
{
    if (list == NULL)
        return 0;

    if (list->size == 0)
        return NULL;

    struct Iterator* it = (struct Iterator*)malloc(sizeof(struct Iterator));
    if (it == NULL)
        return NULL;

    it->node = list->pFirst;
    it->list = list;
    return it;
};

struct Iterator* createBackIterator(struct List* list)
{
    if (list == NULL)
        return 0;

    if (list->size == 0)
        return NULL;

    struct Iterator* it = (struct Iterator*)malloc(sizeof(struct Iterator));
    if (it == NULL)
        return NULL;

    it->node = list->pLast;
    it->list = list;
    return it;
};

struct Iterator* relocateIterator(struct Iterator* it, int relocateOn)
{
    if (it == NULL)
        return NULL;

    if (relocateOn == 0)
        return it;

    if (relocateOn > 0)
    {
        for (int i = 0; i < relocateOn; i++)
        {
            if (it->node->pNext == NULL)
            {
                it->node = it->list->pFirst;
            }
            else
            {
                it->node = it->node->pNext;
            }
        }
    }
    else
    {
        for (int i = relocateOn; i < 0; i++)
        {
            if (it->node->pPrev == NULL)
            {
                it->node = it->list->pLast;
            }
            else
            {
                it->node = it->node->pPrev;
            }
        }
    }
    return it;
};

struct Iterator* erase(struct Iterator* it)
{
    if(it->list->pFirst == NULL)
        return NULL;

    if (it->node->pNext == NULL)
    {
        eraseBack(it->list);
        it->node = it->list->pLast;
        return it;
    }
    if (it->node->pPrev == NULL)
    {
        eraseFront(it->list);
        it->node = it->list->pFirst;
        return it;
    }

    it->node->pPrev->pNext = it->node->pNext;
    it->node->pNext->pPrev = it->node->pPrev;
    struct Node* deleteNode = it->node;
    it->node = it->node->pPrev;
    free(deleteNode);
    it->list->size--;
}

void changeElementIterator(struct Iterator* it, int newNal)
{
    it->node->value = newNal;
}

struct Iterator* insertAfterIterator(struct Iterator* it, int value)
{
    if (it->node->pNext == NULL)
    {
        insertBack(it->list, value);
        it->node = it->list->pLast;
        return it;
    }


    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->value = value;

    n->pPrev = it->node;
    n->pNext = it->node->pNext;
    it->node->pNext->pPrev = n;
    it->node->pNext = n;
    it->node = n;
    it->list->size++;
    return it;
};

void rebuildList(struct Iterator* it)
{
    it->list->pLast->pNext = it->list->pFirst;
    it->list->pFirst->pPrev = it->list->pLast;

    it->list->pFirst = it->node;
    it->list->pLast = it->node->pPrev;

    it->node->pPrev->pNext = NULL;
    it->node->pPrev = NULL;
}

int getNumOfNode(struct Iterator* it)
{
    int index = 0;
    for (struct Node* n = it->list->pFirst; n != it->node; n = n->pNext)
        index++;

    return index;
}
