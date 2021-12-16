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

char reverseChar(char ch) // return the reverse char. (if a return z, if B return Y, ...)
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


int countChar(char ch, char txt[], char word[], int start, int stop)
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


void checkAtbash(char txt[], char words[], int *first)
{
    int i=0, j=0, h=0, count=0; 
    char ch = reverseChar(words[count]);
    
    for(i=0; i<strlen(txt); i++)
    {
        if(txt[i] == ch)
        {
            j=i;
            while (j < strlen(txt) && count < strlen(words))
            {
                ch = reverseChar(words[count]);
                if(txt[j] == 10 || txt[j] == 32 || txt[j] == 9 || txt[j] == 11)
                {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
                    j++;
                    continue;
                }
                if(txt[j] != ch)
                {
                    break;
                }
                j++;
                count++;
            }
            if(count == strlen(words)) //if true then print
            {
                if(*first == 0)
                {
                    printf("~");
                }
                for(h=i; h<j; h++)
                {
                    printf("%c", txt[h]);
                }
                *first = 0;
            }
        }
        count = 0;
        ch = reverseChar(words[count]);
    }
}



void gematria(char txt[] ,int wordSize)
{
    int i=0, j=0, tempSize=0, h=0;
    int first = 1;
    char checkFirst;

    for(i=0; i<strlen(txt); i++)
    {
        checkFirst = reverseChar(txt[i]); // side affect of the function is that it will check id the char is legal or not.
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
    int i=0, end=0; 
    int first = 1;
    checkAtbash(txt, word, &first);

    while (word[i] != 0)
    {
        i++;
        end++;
    }

    char reverse[WORD] = {0};
    for (i = 0; i < end; i++)
    {
        reverse[i] = word[end-i-1];
    }
    checkAtbash(txt, reverse, &first);    
}

void anagram(char txt[], char word[])
{
    int i=0, j=0, h=0, count=0;
    int first = 1;
    for(i=0; i<strlen(txt); i++)
    {
        if(txt[i] == 32)
        {//all the options for white space: enter(10), space(32), tab(9) and vertical tab(11)
            continue;
        }

        if(strchr(word, txt[i]) != NULL)
        {
            j=i;
            while(count < strlen(word) && j < strlen(txt))
            {
                if(txt[j] == 32)
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
