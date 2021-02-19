/**************************************************************************************
* Author: Lam Thu Phung
* Course: EGR 226 - 905
* Date: 02/05/2021
* Project: LAB 2
* File: LAB 2 - Part 2
* Description: BookDatabase
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;

void main()
{
    char run = '1';
    int k = 0;  //This variable was used to check whether user want to continue another searching or not
    char title[255];
    char author_name[50];
    char ISBN[10];
    char filename[50] = "BookList.csv";
    book my_book;
    book my_book_array[360];
    int size = 360;
    int option = -1;

    while (k == 0)
    {
        parse_file(filename, my_book_array);
        while(run == '1')
            {
                //in this loop, the program prompt user to enter the option for searching book
                while (option < 0 || option > 2)
                {
                    printf("What would you like to search by? [0] Title, [1] Author, or [2] ISBN \n");
                    scanf("%d", &option);
                    //this code used to check the entered input if matching the option or not which is (0,1,2)
                    while((getchar())!= '\n');
                    if (option == 0)
                    {   //if the user pick this option then the program will prompt the user to enter the title that they want to search
                        printf("\n\tEnter your search title: \n");
                        scanf("%s", &*title);
                        //then the program will store the entered input under title and call the function search_title.
                        search_title(my_book_array, size, title);
                    }
                    else if (option == 1)
                    {   //if the user pick this option then the program will prompt the user to enter the author name that they want to search
                        printf("\n\tEnter author name: \n");
                        scanf("%s", &*author_name);
                        //then the program will store the entered input under author_name and call the function search_author.
                        search_author(my_book_array, size, author_name);
                    }
                    else if (option == 2)
                    {
                        //if the user pick this option then the program will prompt the user to enter the ISBN that they want to search
                        printf("\n\tEnter the ISBN: \n\t");
                        scanf("%s", &*ISBN);
                        //then the program will store the entered input under isbn and call the function search_ISBN.
                        search_ISBN(my_book_array, size, ISBN);
                    }
                    else
                        //if the option entered is not available then it will print out invalid entry
                        printf("\t<Please enter a value between 0 and 2>\n ");
                }

                //the do-while loop below was used to ask the user if the want to search another book or not
                //it also has an error check the input entered.
                do
                {
                    printf("\nWould you like to do another searching?\n\tEnter 1 for Yes/ 0 for No\n");
                    scanf(" %c", &run);
                    while((getchar())!= '\n');
                    if (run == '1')
                        option = -1;
                    else if ((run != '1') && (run != '0'))
                        printf("INVALID INPUT\n\n");
                    else if (run == '0')
                        k = 1;
                }
                while((run != '0') && (run != '1'));
            }
        }

    printf("Good Bye!");
    return 0;
}

int parse_file(char filename[], book my_book_array[])
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
    else
    {
    char buffer[512];
    int i = 0, n = 0;
        //the while loop used to check the error if the data of each scanned element is N/A
    while (fgets(buffer, 512, file))
    {
        //Using strtok() function to parse a line by a comma delimiter
        char *ptr = strtok(buffer,",");
        if (strcmp(ptr, "N/A"))
            strcpy(my_book_array[i].title, ptr);
            ptr = strtok(NULL,",\n");

        if (strcmp(ptr, "N/A"))
            strcpy(my_book_array[i].author_name, ptr);
            ptr = strtok(NULL,",\n");

        if (strcmp(ptr, "N/A"))
            strcpy(my_book_array[i].ISBN, ptr);
            ptr = strtok(NULL,",\n");

        if (strcmp(ptr, "N/A"))
            my_book_array[i].pages = atoi(ptr); //atoi() function is used to convert character to digit
            ptr = strtok(NULL,",\n");

        if (strcmp(ptr, "N/A"))
            my_book_array[i].year_published = atoi(ptr);
            ptr = strtok(NULL,",\n");
            i++;
    }
    n++;
    fclose(file);
    }
    return 1;
}



//function called used to print the book with 5 data points
void print_book(book my_book_array[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("\t|Title: %s\n", my_book_array[i].title);
        printf("\t|Author Name: %s\n", my_book_array[i].author_name);
        printf("\t|ISBN: %s\n", my_book_array[i].ISBN);
        printf("\t|Pages: %d\n", my_book_array[i].pages);
        printf("\t|Published Year: %d\n\n", my_book_array[i].year_published);
    }
}

//This function allows user to search the book by title
void search_title(book my_book_array[], int size, char user_search_title[])
{
    for(int i = 0; i < size; ++i)
    {
        //this code use to compare the input value vs the date of the title element
        char *p1 = strstr(my_book_array[i].title, user_search_title);

        //if the compare matching, then the book will be printed out
        if (p1 != NULL)
        {
            printf("\t|Title: %s\n",my_book_array[i].title);
            printf("\t|Author Name: %s\n", my_book_array[i].author_name);
            printf("\t|ISBN: %s\n", my_book_array[i].ISBN);
            printf("\t|Pages: %d\n", my_book_array[i].pages);
            printf("\t|Published Year: %d\n\n", my_book_array[i].year_published);

        }
    }
}

//This function allows user to search the book by author name
void search_author(book my_book_array[], int size, char user_search_author[])
{
    for(int i = 0; i < size; ++i)
    {
        //this code use to compare the input value vs the date of the author name element
        char *p1 = strstr(my_book_array[i].author_name, user_search_author);

        //if the compare matching, then the book will be printed out
        if (p1 != NULL)
        {
            printf("\t|Title: %s\n", my_book_array[i].title);
            printf("\t|Author Name: %s\n", my_book_array[i].author_name);
            printf("\t|ISBN: %s\n", my_book_array[i].ISBN);
            printf("\t|Pages: %d\n", my_book_array[i].pages);
            printf("\t|Published Year: %d\n\n", my_book_array[i].year_published);
        }
    }
}

//This function allows user to search the book by ISBN
void search_ISBN (book my_book_array[], int size, char user_search_ISBN[])
{
    for(int i = 0; i < size; ++i)
    {
        //this code use to compare the input value vs the date of the ISBN element
        char *p1 = strstr(my_book_array[i].ISBN, user_search_ISBN);
        //if the compare matching, then the book will be printed out
        if (p1 != NULL)
        {
            printf("\t|Title: %s\n", my_book_array[i].title);
            printf("\t|Author Name: %s\n", my_book_array[i].author_name);
            printf("\t|ISBN: %s\n", my_book_array[i].ISBN);
            printf("\t|Pages: %d\n", my_book_array[i].pages);
            printf("\t|Published Year: %d\n\n", my_book_array[i].year_published);
        }
    }
}
