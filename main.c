#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include "list.h"

#define BACK_SPACE 8
#define ENTER 13
#define ESC 27
#define UP 72   // 224 72
#define DOWN 80 // 224 80
#define LEFT 75 // 224 75
#define RIGHT 77// 224 77

const int SIZE_OF_MENU = 9;

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

int getFirstSizeWithGetch(const char* message)
{
    unsigned char byteFirst  = -1;
    unsigned char byteSecond = -1;
    char nStr[100] = { 0 };
    int it = -1;
    for (;;)
    {
        system("cls");
        printf(message);
        printf(nStr);

        byteFirst = getch();
        if (byteFirst == 224 || byteFirst == 0)
            byteSecond = getch();

        if(byteFirst >= '0' && byteFirst <= '9')
        {
            it++;
            nStr[it] = byteFirst;
        }
        if (byteFirst == BACK_SPACE)
        {
            nStr[it] = 0;
            if (it != -1)
                it--;
        }
        if (byteFirst == ENTER)
        {
            int flag = 1;
            for (int i = 0; nStr[i]; i++)
                if (nStr[i] != '0')
                    flag = 0;

            if (flag == 0)
                break;
        }
    }
    return strToNum(nStr);
}

int getNumberWithGetch(const char* message)
{
    unsigned char byteFirst  = -1;
    unsigned char byteSecond = -1;
    char nStr[100] = { 0 };
    int it = -1;
    for (;;)
    {
        system("cls");
        printf(message);
        printf(nStr);

        byteFirst = getch();
        if (byteFirst == 224 || byteFirst == 0)
            byteSecond = getch();

        if(byteFirst >= '0' && byteFirst <= '9' || it == -1 && byteFirst == '-')
        {
            it++;
            nStr[it] = byteFirst;
        }
        if (byteFirst == BACK_SPACE)
        {
            nStr[it] = 0;
            if (it != -1)
                it--;
        }
        if (byteFirst == ENTER)
        {
            if (nStr[0] != 0)
                break;
        }
    }
    return strToNum(nStr);
}

char* getChainStrWithGetch(const char* message)
{
    unsigned char byteFirst  = -1;
    unsigned char byteSecond = -1;

    char* nStr = (char*)malloc(sizeof(char) * 500);
    for (int i = 0; i < 500; i++)
        nStr[i] = 0;

    int it = -1;

    for (;;)
    {
        system("cls");
        printf(message);
        printf(nStr);

        byteFirst = getch();
        if (byteFirst == 224 || byteFirst == 0)
            byteSecond = getch();

        if(byteFirst >= '0' && byteFirst <= '9' ||
           (it == -1 || nStr[it] == ' ') && byteFirst == '-' ||
           (it != -1 && nStr[it] != ' ') && byteFirst == ' ')
        {
            it++;
            nStr[it] = byteFirst;
        }
        if (byteFirst == BACK_SPACE)
        {
            nStr[it] = 0;
            if (it != -1)
                it--;
        }
        if (byteFirst == ENTER)
        {
            if (nStr[0] != 0)
                break;
        }
    }
    return nStr;
}


void initialiseList(struct List* list)
{
    int numberOfMembers = getFirstSizeWithGetch("Enter number of members:  ");
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

void printMenu(int state)
{
    printf("1) Добавить элемент после указанного");     if(state == 1) printf(" <-"); printf("\n");
    printf("2) Добавить первый элемент");               if(state == 2) printf(" <-"); printf("\n");
    printf("3) Изменить элемент");                      if(state == 3) printf(" <-"); printf("\n");
    printf("4) Удалить элемент");                       if(state == 4) printf(" <-"); printf("\n");
    printf("5) Добавить цепочку элементов");            if(state == 5) printf(" <-"); printf("\n");
    printf("6) Удалить цепочку элементов");             if(state == 6) printf(" <-"); printf("\n");
    printf("7) Записать цепочку в файл");               if(state == 7) printf(" <-"); printf("\n");
    printf("8) Считать цепочку из файла");              if(state == 8) printf(" <-"); printf("\n");
    printf("9) Перестроить список");                    if(state == 9) printf(" <-"); printf("\n");
}

void changeState(int* state, char byteFirst, char byteSecond)
{
    if (byteSecond == DOWN)
        if (*state == SIZE_OF_MENU)
            *state = 1;
        else
            (*state)++;

    if (byteSecond == UP)
    if (*state == 1)
        *state = SIZE_OF_MENU;
    else
        (*state)--;

    if (byteFirst >= '1' && byteFirst <= '9')
        (*state) = byteFirst - '0';
}

int main()
{
    setlocale(LC_ALL, "Russian");

    struct List* list = createList();
    if (list == NULL)
    {
        printf("Memory Error");
        return;
    }

    initialiseList(list);
    struct Iterator* iterator = createFrontIterator(list);

    unsigned char byteFirst  = -1;
    unsigned char byteSecond = -1;

    int state = 1;
    int enterPressed = 0;

    for (;;)
    {
        system("cls");
        printf("list: \n");
        print(list);
        for (int i = 0; i < getNumOfNode(iterator); i++)
            printf("     |");

        printf("  ");
        printf("*  |");

        for (int i = 0; i < iterator->list->size - getNumOfNode(iterator) - 1; i++)
            printf("     |");

        printf("\n");

        printMenu(state);

        byteFirst = getch();
        if (byteFirst == 224 || byteFirst == 0)
            byteSecond = getch();
        else
            byteSecond = 0;

        changeState(&state, byteFirst, byteSecond);
        if (byteFirst == 224 && byteSecond == LEFT)
        {
            relocateIterator(iterator, -1);
        }
        if (byteFirst == 224 && byteSecond == RIGHT)
        {
            relocateIterator(iterator, 1);
        }
        if (byteFirst == ESC)
        {
            return 0;
        }
        if (byteFirst == ENTER)
        {
            enterPressed = 1;
        }

        if (enterPressed == 1)
        {
            if (state == 1) // insert element after index
            {
                if (list->size != 0)
                {
                    int insertNumber = getNumberWithGetch("Enter value of member: ");
                    insertAfterIterator(iterator, insertNumber);
                }
            }

            if (state == 2) // insert first element
            {
                int insertNumber = getNumberWithGetch("Enter value of new first member: ");
                if (iterator->list->size == 0)
                {
                    iterator->node = insertFront(iterator->list, insertNumber);
                }
                else
                {
                    insertFront(list, insertNumber);
                }
            }

            if (state == 3) // change element
            {
                int insertNumber = getNumberWithGetch("Enter value of member: ");
                changeElementIterator(iterator, insertNumber);
            }

            if (state == 4) // delete element
            {
                erase(iterator);
            }
            if (state == 5) // add a chain of elements
            {
                insertChainAfterIterator(iterator, getChainStrWithGetch("Enter value of chain members: "));
            }

            if (state == 9) // rebuild
            {
                if (iterator->list->size != 0)
                    rebuildList(iterator);
            }


        enterPressed = 0;
        }

    }
}
