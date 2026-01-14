/***
* Kristen North // First and Last Name
* krnorth // UCSC CruzID
* 2026 Winter CSE101 PA1 // Replace ID with assignment number 
* Words.c // FileName
* Test client for List ADT 
***/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX_LINE_LENGTH 1024
#define INITIAL_ARRAY_SIZE 16

//dont use variable length array shouldnt use stack memory
    //use heap array calloc(n, sizeof(char*));

        //indirectly sort array of strings
      //build a listadt of ints
      // build it so it indirectly sorts the array

      //empty list
      //outer loop that 
      //insert 0 at ind 0
      //insert 1, move front so 0 is current
      //1 should be b4 or after 0 (a vs c) insert before
      //2 (2 before 1) no move next
      //2 before 0? yes insert before
      //repeat for all elements

int main(int argc, char *argv[]) {
    if (argc != 3) {//not enough args
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");//open input
    if (fp == NULL) {//mem check
        fprintf(stderr, "Error opening input file: %s\n", argv[1]);
        exit(1);
    }

    FILE *of = fopen(argv[2], "w");//open output
    if (of == NULL) {//mem check
        fprintf(stderr, "Error opening output file: %s\n", argv[2]);
        fclose(fp);
        exit(1);
    }

    //words heap
    char **words = calloc(INITIAL_ARRAY_SIZE, sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        fclose(fp);
        fclose(of);
        exit(1);
    }

    //set sizes
    char line[MAX_LINE_LENGTH];
    int count = 0;
    int size = INITIAL_ARRAY_SIZE;

    // Read all words from file FIRST (don't close fp inside the loop)
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {//read ll words from file

        char *word = strtok(line, " \t\n\r,.;:!?\"'()[]{}");//get each word
        
        while (word != NULL) {//check for dups
            int isDup = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(words[i], word) == 0) {//dup found
                    isDup = 1;
                    break;
                }
            }

            if (!isDup) {//no dup found
                if (count == size) {//resize array by 2

                    size *= 2;
                    char **temp = realloc(words, size * sizeof(char*));

                    if (temp == NULL) {//mem check

                        fprintf(stderr, "Error: memory reallocation failed\n");

                        for (int i = 0; i < count; i++) free(words[i]);//free all words

                        free(words);//free word arr
                        fclose(fp);//close all files
                        fclose(of);
                        exit(1);
                    }
                    words = temp;//update arr
                }

                // Allocate and copy the word
                words[count] = malloc((strlen(word) + 1) * sizeof(char));

                if (words[count] == NULL) {//mem check

                    fprintf(stderr, "Error: memory allocation for word failed\n");

                    for (int i = 0; i < count; i++) free(words[i]);
                    free(words);
                    fclose(fp);
                    fclose(of);
                    exit(1);
                }

                strcpy(words[count], word);//copy word into word arr
                count++;//inc size
            }

            word = strtok(NULL, " \t\n\r,.;:!?\"'()[]{}");//ignore special chars
        }
    }
    
    fclose(fp);//close input

    // Now sort the words using List ADT
    List l = newList();
    
    if (count > 0) {
        append(l, 0);//first el
        
        for (int i = 1; i < count; i++) {//rest elements
            int inserted = 0;
            moveFront(l);
            
            //find pos for word
            while (position(l) >= 0) {
                int currentIndex = get(l);
                
                if (strcmp(words[i], words[currentIndex]) < 0) {//current word comes before index insert before index
                    insertBefore(l, i);
                    inserted = 1;
                    break;
                }
                moveNext(l);//update curs
            }
            
            if (!inserted) {//append later alph words at end
                append(l, i);
            }
        }
    }

    //print ind to output file
    printList(of, l);
    fprintf(of, "\n");

    //print words to out file
    moveFront(l);
    while (position(l) >= 0) {
        int wordIndex = get(l);
        fprintf(of, "%s\n", words[wordIndex]);
        moveNext(l);
    }

    //free everything and close output
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    freeList(&l);
    fclose(of);

    return 0;
}