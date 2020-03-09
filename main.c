#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "list.h"

#define BACK_SPACE 8
#define ENTER 13
#define ESC 27
#define UP 72   // 224 72
#define DOWN 80 // 224 80
#define LEFT 75 // 224 75
#define RIGHT 77// 224 77


void testFuncton()
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
    relocateIterator(i5, -2);
    rebuildList(i5);
    print(l);
    printf("num: %d     ", i5->numOfNode);
    printf("value: %d\n", i5->node->value);
}

int strToNum(const char* str)
{
    int result = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += str[i] - '0';
        }
    if (str[0] == '-')
        result *= -1;

    return result;
}

const char* numToStr(int num)
{
    char* str = (char*)malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++)
        str[i] = 0;

    int sign = 0;
    if (num < 0)
    {
        sign = 1;
        num *= -1;
    }

    while (num)
    {
        for (int i = 100-1; i > 0; i--)
            str[i] = str[i-1];

        str[0] = num % 10 + '0';
        num /= 10;
    }
    if (sign)
    {
        for (int i = 100-1; i > 0; i--)
            str[i] = str[i-1];

        str[0] = '-';
    }

    if(str[0] == 0)
        str[0] = '0';
    return str;
}

int getItEnd(const char* str)
{
    int it = 0;
    for (; str[it]; it++)
    ;

    return it;
}

int getNumberWithGetch(const char* message)
{
    unsigned char biteFirst  = -1;
    unsigned char biteSecond = -1;
    char nStr[100] = { 0 };
    int it = -1;
    for (;;)
    {
        system("cls");
        printf(message);
        printf(nStr);

        biteFirst = getch();
        if (biteFirst == 224 || biteFirst == 0)
            biteSecond = getch();

        if(biteFirst >= '0' && biteFirst <= '9' || it == -1 && biteFirst == '-')
        {
            it++;
            nStr[it] = biteFirst;
        }
        if (biteFirst == BACK_SPACE)
        {
            nStr[it] = 0;
            if (it != -1)
                it--;
        }
        if (biteFirst == ENTER)
        {
            if (nStr[0] != 0)
                break;
        }
    }
    return strToNum(nStr);
}

void initialiseList(struct List* list)
{
    int numberOfMembers = getNumberWithGetch("Enter number of members:  ");
    if (numberOfMembers < 0)
        numberOfMembers *= -1;

    const char* numberOfMembersStr = numToStr(numberOfMembers);
    for (int i = 0; i < numberOfMembers; i++)
    {
        const char* numOfMemStr = numToStr(i);
        char message[300] = {'E','n','t','e','r',' ','m','e','m','b','e','r','('}; // 13
        strcpy(message + getItEnd(message), numOfMemStr);
        strcpy(message + getItEnd(message), " of ");
        strcpy(message + getItEnd(message), numberOfMembersStr);
        strcpy(message + getItEnd(message), "): ");

        int newMember = getNumberWithGetch(message);
        insertBack(list, newMember);
    }
    system("cls");
}

int main()
{
    struct List* list = createList();
    if (list == NULL)
    {
        printf("Memory Error");
        return;
    }

    initialiseList(list);
    struct Iterator* iterator = createFrontIterator(list);

    unsigned char biteFirst  = -1;
    unsigned char biteSecond = -1;

    for (;;)
    {
//         action == f -> insert first element
//         action == i -> insert element after index
//         action == d -> delete element
//         action == r -> rebuild

        system("cls");
        printf("list: \n");
        print(list);

        biteFirst = getch();
        if (biteFirst == 224 || biteFirst == 0)
            biteSecond = getch();


        if (biteFirst == 'f') // insert first element
        {

        }
        if (biteFirst == 'i') // insert element after index
        {

        }
        if (biteFirst == 'd') // delete element
        {

        }
        if (biteFirst == 'r') // rebuild
        {

        }
        if (biteFirst == LEFT)
        {

        }
        if (biteFirst == RIGHT)
        {

        }
        if (biteFirst == ESC)
        {

        }


    }
}
