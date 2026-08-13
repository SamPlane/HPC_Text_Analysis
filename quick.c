#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {


// Create a string
char phrase[100];

// Ask the user to input some text
printf("Enter the phrase to be searched for: \n");

// Get and save the text
scanf("%s", phrase);

int phraseLength = strlen(phrase);

FILE *getLinesTotal = fopen("Odyssey.txt", "r"); // Open file in read mode

if (getLinesTotal == NULL) {
    printf("Error: Could not open file.\n");
    return 1;
}

char line[1000];

int noOfLines = 0;

while (fgets(line, sizeof(line), getLinesTotal)) { // Read file line-by-line
    ++noOfLines;
}

fclose(getLinesTotal); //Close the file

/*
char* ptr;
ptr = (char*) malloc(noOfLines * sizeof(line));
*/

char ptr[noOfLines][1000];

printf("Reading");

FILE *readLines = fopen("Odyssey.txt", "r");

if (readLines == NULL) {
    printf("Error: Could not open file.\n");
    return 1;
}

noOfLines = 0;

while (fgets(line, sizeof(line), getLinesTotal)) { // Read file line-by-line
    ++noOfLines;
    //ptr[noOfLines] = line;
    strcpy(ptr[noOfLines],line); 
}

fclose(readLines);

printf("Read into ptr \n");
int occurrences = 0;
int match;
int charIndex;
char* currentLine[1000];

for (int eachLine = 0; eachLine < noOfLines; eachLine++) {
    if (strlen(ptr[eachLine]) >= phraseLength) {
        for (int eachChar = 0; eachChar < strlen(ptr[eachLine]-phraseLength); eachChar++) {
	    match = 1;
            for (int eachPhraseChar = 0; eachPhraseChar < phraseLength; eachPhraseChar++) {
		charIndex = eachChar + eachPhraseChar;
		//&currentLine = ptr[eachLine];
		if (ptr[eachLine][charIndex] != phrase[eachPhraseChar]) {
                    match = 0;
		}
		    
	    }
	    ++occurrences;
        }
    }
}

printf("There are %d occurrences of this phrase in the text", occurrences);

free(ptr);

return 0;
}
