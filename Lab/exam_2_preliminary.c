#include "stdio.h"
#include "lab2.h"
#include "string.h"

/* TASK SOLUTIONS */

void to_lower(char * sentence)
{
    int gap = ('a' - 'A');
    
    while (*sentence != '!')
    {
        if (*sentence < 'a' && *sentence >= 'A')
        {
            *sentence += gap;
        }
        sentence += 1;
        
    }
    return;
}

void print_sentence(char * sentence)
{
    while (*sentence != '!')
    {
        printf("%c", *sentence);
        sentence += 1;
    }
    printf("\n");
}

void substrings(char * sentence, char * substr, int * arr)
{
    int same = 0;
    int i;
    int index = 0;
    int index_first;
    int sub_length = 0;
    
    while (*substr != '!') /* Calculates the length of substr */
    {
        sub_length += 1;
        substr += 1;
    }
    substr = (substr - sub_length);
    
    
    while (*sentence != '!')
    {
        if (*sentence == *substr)
        {
            index_first = index;
            same = 1;
            for (i=1 ; i<sub_length ; ++i)
            {
                if (*(sentence+i) != *(substr+i))
                {
                    same = 0;
                    break;
                }
            }
        }
        else
        {
            same = 0;
        }
        
        if (same == 1)
        {
            *arr = index_first;
            arr += 1;
            sentence += sub_length;
            index += sub_length;
            continue;
        }
        
        sentence += 1;
        index += 1;
    }
    
    
}

void removeX(char * sentence, int * arr, int count)
{
    int index = 0;
    int times = 0;
    int s_index = 0;
    int arr_length = (sizeof(arr) / sizeof(*arr)) + 1;
    int sentence_length = 0;
    
    while (*sentence != '!')
    {
        sentence_length += 1;
        sentence += 1;
    }
    sentence -= sentence_length;
    

    while (times < arr_length)
    {
        if (index == *arr )
        {
            for (s_index=(index - times*count) ; s_index<(sentence_length) ; ++s_index)
            {
                *(sentence + s_index) = *(sentence + s_index + count);
            }
            sentence_length -= count;
            index += count;
            times += 1;
            arr += 1;
        }
        else index += 1;
    }
        
    
}

void addSome(char * sentence, int * arr, char * substr)
{
    int i;
    int j;
    int time = 1;
    int arr_length = (sizeof(arr) / sizeof(*arr)) + 1;
    int sentence_length = 0;
    int sub_length = 0;
    char to_copy_sentence[256] = "a";
    int zum = 0;
    
    while (*substr != '!') /* Calculates the length of substr */
    {
        sub_length += 1;
        substr += 1;
    }
    substr = (substr - sub_length);
    
    while (*sentence != '!') /* length of sentence */
    {
        sentence_length += 1;
        sentence += 1;
    }
    sentence -= sentence_length;
    
    
    for (i=0 ; *(sentence + i) != '!' ; ++i)
    {
        if ( *(sentence+i) == '!' )
        {
            for (j=0 ; j < arr_length*sub_length ; ++j)
            {
                *(sentence + i + 1 + j ) = '.';
            }
        }
    }
    
    i=0;
    j=0;
    while (i < sentence_length + arr_length*sub_length + 1)
    {
        if (i == *(arr))
        {
            while (zum < sub_length)
            {
                to_copy_sentence[*(arr) + zum] = *(substr + zum);
                zum += 1;
            }
            zum = 0;
            arr += 1;
            i += sub_length;
            *(arr) += time*sub_length;
            time += 1;
        }
        else
        {
            to_copy_sentence[i] = *(sentence + j);
            i += 1;
            j += 1;
        }
    }

    for (i=0 ;  to_copy_sentence[i] != '\0' ; ++i)
    {
        *(sentence + i) = to_copy_sentence[i];
    }
}
