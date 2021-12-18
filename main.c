#include <stdio.h>
#include <string.h>

#define TXT 1024
#define WORD 30
#define TILDA 126
#define A 65
#define Z 90
#define a 97
#define z 122


int size(char txt[], int i, int j)
{
    int sum = 0, h;
    for(h=i; h<j; h++)
    {
        if(txt[h] >= A && txt[h] <= Z)
        {
            sum += txt[h]-A+1;
        }
        else if(txt[h] >= a && txt[h] <= z)
        {
            sum += txt[h]-a+1;
        }
    }
    return sum;
}

char reverseChar(char ch) // return the reverse char. (if a return z, if B return Y, ...) return null if the char is not legal.
{
    if(ch >= A && ch <= Z)
    {
        return (Z - (ch - A));
    }
    if(ch >= a && ch <= z)
    {
        return (z - (ch - a));
    }
    return 0;
}


int countChar(char ch, char txt[], char word[], int start, int stop) //check if we have the specific char too many times in a sequence
{
    int count1=0, count2=0, i;

    for(i=0; i<strlen(word); i++)
    {
        if(word[i] == ch)
        {
            count1++;
        }
    }

    for(i=start; i<=stop; i++)
    {
        if(txt[i] == ch)
        {
            count2++;
        }
    }

    if(count1 >= count2)
    {
        return 1;
    }
    return 0;
}


void gematria(char txt[] ,int wordSize)
{
    int i=0, j=0, tempSize=0, h=0;
    int first = 1;
    char checkFirst;

    for(i=0; i<strlen(txt); i++) //go over the txt and check for correct sequences.
    {
        checkFirst = reverseChar(txt[i]); // side affect of the function is that it will check if the char is legal or not.
        if(checkFirst == 0) //if the first char is elegal then skip it.
        {
            continue;
        }

        j = i+1;
        while(j <= strlen(txt))
        {
            tempSize = size(txt, i,j);
            if (tempSize > wordSize)
            {
                break;
            }
            if (tempSize == wordSize)
            {
                if(first == 0)
                {
                    printf("~");
                }
                for(h=i; h<j; h++)
                {
                    printf("%c", txt[h]);
                }
                first = 0;
                break;
            }
            j++;
        }
    }
}

void atbash(char txt[], char word[])
{
    int i=0, end=0, first = 1; 
    char reverse[WORD] = {0}; //the reverse word
    char copy[WORD] = {0}; //copy of the real word
    
    while (word[i] != 0) //count how many real chars we need to adress and change the word chars to the wanted version.
    {
        i++;
        end++;
        copy[i] = word[i];
    }
    for (i = 0; i < end; i++) //put values in the reverse word
    {
        reverse[i] = word[end-i-1];
        copy[i] = reverseChar(copy[i]);
        reverse[i] = reverseChar(reverse[i]);
    }

    int j=0, h=0, count=0; 
    char ch;
    char rch;

    
    for(i=0; i<strlen(txt); i++) //go over the txt and look for the start of the sequence (any of the two).
    {
        ch = copy[0];
        rch = reverse[0];
        if(txt[i] == ch) //check sequance of the ordered word
        {
            count = 0;
            j=i;
            while (j < strlen(txt) && count < strlen(copy))
            {
                ch = copy[count];
                if(txt[j] == 10 || txt[j] == 32 || txt[j] == 9 || txt[j] == 11)
                {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
                    j++;
                    continue;
                }
                if(txt[j] != ch) //wrong sequance then break the while loop.
                {
                    break;
                }
                j++;
                count++;
            }
            if(count == strlen(copy)) //if true then print
            {
                if(first == 0)
                {
                    printf("~");
                }
                for(h=i; h<j; h++) //print answer
                {
                    printf("%c", txt[h]);
                }
                first = 0;
            }
        }

        if(txt[i] == rch) //check sequance of the reverse word
        {
            count = 0;
            j=i;
            while (j < strlen(txt) && count < strlen(reverse))
            {
                rch = reverse[count];
                if(txt[j] == 10 || txt[j] == 32 || txt[j] == 9 || txt[j] == 11)
                {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
                    j++;
                    continue;
                }
                if(txt[j] != rch) //wrong sequance then break the while loop.
                {
                    break;
                }
                j++;
                count++;
            }
            if(count == strlen(reverse)) //if true then print
            {
                if(first == 0)
                {
                    printf("~");
                }
                for(h=i; h<j; h++) //print answer
                {
                    printf("%c", txt[h]);
                }
                first = 0;
            }
        }
    }  
}

void anagram(char txt[], char word[])
{
    int i=0, j=0, h=0, count=0;
    int first = 1;
    for(i=0; i<strlen(txt); i++)
    {
        if(txt[i] == 10 || txt[i] == 32 || txt[i] == 9 || txt[i] == 11)
        {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
            continue;
        }

        if(strchr(word, txt[i]) != NULL)
        {
            j=i;
            while(count < strlen(word) && j < strlen(txt))
            {
                if(txt[j] == 10 || txt[j] == 32 || txt[j] == 9 || txt[j] == 11)
                {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
                    j++;
                    continue;
                }

                if(strchr(word, txt[j]) == NULL || countChar(txt[j], txt, word, i, j) == 0)
                {
                    break;
                }
                count++;
                j++;
            }
            if(count == strlen(word)) //if true then print
            {
                if(first == 0)
                {
                    printf("~");
                }
                for(h=i; h<j; h++)
                {
                    printf("%c", txt[h]);
                }
                first = 0;
            }
            count=0;
        }
    }
}




int main()
{
    char word[WORD] = {0};
    char txt[TXT] = {0};
    scanf("%s", word); // accept word.
    int wordSize = size(word, 0, strlen(word));
    int i = 0;
    char ch;
    while(i < 1024) //accept text.
    {
        scanf("%c", &ch);
        if(ch == TILDA) // if the char is tilda then stop.
        {
            break;
        }
        else
        {
            txt[i] = ch;
            i++;
        }
    }

    printf("Gematria Sequences: ");
    gematria(txt, wordSize);
    printf("\nAtbash Sequences: ");
    atbash(txt, word);
    printf("\nAnagram Sequences: ");
    anagram(txt, word);
    return 0;
}
