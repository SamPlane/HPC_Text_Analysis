#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main() {

char phrase[100];
char line[1000];
int noOfLines = 0;
int occurrences = 0;
int match;
int charIndex;
char* currentLine[1000];

// Prompt user to input phrase to search for
printf("Enter the phrase to be searched for: \n");
scanf("%s", phrase);

int phraseLength = strlen(phrase);

// Confirm number of lines in file
FILE *getLinesTotal = fopen("Odyssey.txt", "r");

    if (getLinesTotal == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), getLinesTotal)) { // Read file line-by-line
        ++noOfLines;
    }

fclose(getLinesTotal); //Close the file


// Read lines from file into array
char ptr[noOfLines][255];
noOfLines = 0;

FILE *readLines = fopen("Odyssey.txt", "r");

    if (readLines == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), getLinesTotal)) {
        strcpy(ptr[noOfLines],line);
        ++noOfLines;

    }

fclose(readLines);

// Iterates through every element in the array
for (int eachLine = 0; eachLine < noOfLines; eachLine++) {
    // Only checks lines of an appropriate length
    if (strlen(ptr[eachLine]) >= phraseLength) {
	// Uses every valid character in the current line as a starting point for the potential phrase match
        for (int eachChar = 0; eachChar < strlen(ptr[eachLine])-phraseLength; eachChar++) {
	    match = 1;
	    // If a subsequent character after the starting point doesn't match the phrase
	    // note that a match has not occurred
            for (int eachPhraseChar = 0; eachPhraseChar < phraseLength; eachPhraseChar++) {
		charIndex = eachChar + eachPhraseChar;
		if (ptr[eachLine][charIndex] != phrase[eachPhraseChar]) {
                    match = 0;
		}
		    
	    }
	    //All matches are counted for output at the end of the program
	    if (match == 1) {
	        ++occurrences;
	    }
        }
    }
}

printf("There are %d occurrences of this phrase in the text \n", occurrences);

//free(ptr);


return 0;
}
