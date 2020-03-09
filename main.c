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


void _main()
{
    struct List* list = createList();
    insertFront(list, 55);
    insertFront(list, 1);
    insertFront(list, 4);
    struct Iterator* iterator = createFrontIterator(list);
    relocateIterator(iterator, 1);
    relocateIterator(iterator, 1);
    print(list);
    printf("num: %d     ", iterator->numOfNode);
    printf("value: %d\n", iterator->node->value);
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
//printf("num: %d", iterator->numOfNode);
//printf("  val: %d", iterator->node->value);
//printf("size: %d\n", iterator->list->size);
//Sleep(1000);

    unsigned char biteFirst  = -1;
    unsigned char biteSecond = -1;

    for (;;)
    {
//         action == f -> insert first element
//         action == i -> insert element after index
//         action == d -> delete element
//         action == c -> change element
//         action == r -> rebuild

        system("cls");
printf("num: %d", iterator->numOfNode);
printf("size: %d\n", iterator->list->size);
        printf("list: \n");
        print(list);
        for (int i = 0; i < iterator->numOfNode; i++)
            printf("      ");

        printf("  ");
        printf("*");

        biteFirst = getch();
        if (biteFirst == 224 || biteFirst == 0)
            biteSecond = getch();


        if (biteFirst == 'f') // insert first element
        {
            int insertNumber = getNumberWithGetch("Enter value of first member: ");
            if (iterator->list->size == 0)
            {
                iterator->node = insertFront(list, insertNumber);
                iterator->numOfNode = 0;
            }
            else
                insertFront(list, insertNumber);
        }
        if (biteFirst == 'i') // insert element after index
        {
            if (iterator->numOfNode != -1)
            {
                int insertNumber = getNumberWithGetch("Enter value of member: ");
                insertAfterIterator(iterator, insertNumber);
            }
        }
        if (biteFirst == 'd') // delete element
        {
            erase(iterator);
        }
        if (biteFirst == 'c') // change element
        {
            int insertNumber = getNumberWithGetch("Enter value of member: ");
            changeElementIterator(iterator, insertNumber);
        }
        if (biteFirst == 'r') // rebuild
        {
            if (iterator->list->size != 0)
                rebuildList(iterator);
        }
        if (biteSecond == LEFT)
        {
            relocateIterator(iterator, -1);
        }
        if (biteSecond == RIGHT)
        {
            relocateIterator(iterator, 1);
        }
        if (biteFirst == ESC)
        {
            return 0;
        }
    }
}
/// ��������� ������������ ������� ��� ��������� ��������� - �������, �������� � ��
/// ��� ������ �������� ��������� ������ ������
/// ��� rebuild ��� �� ���������� ������������ �������� ���������
/// ��� ������� ������� ��������� ������
