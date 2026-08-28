#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

char phrase[100];
char line[1000];
int noOfLines = 0;
int occurrences = 0;
int match;
int charIndex;
int phraseLength;
char* currentLine[1000];
int myId;
int numProcs;
int occurrencesTotal = 0;
int lowerBound, upperBound;

MPI_Init(&argc, &argv);

// Obtains values of process number and total number of processes
MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
MPI_Comm_rank(MPI_COMM_WORLD, &myId);

// Prompt user to input phrase to search for
if (myId == 0 ) {
    printf("Enter the phrase to be searched for: \n");
    scanf("%s", phrase);
    phraseLength = strlen(phrase);
}

MPI_Barrier(MPI_COMM_WORLD);

// Broadcasts the phrase to be searched for to all the processes
MPI_Bcast(&phraseLength, 1, MPI_INT, 0, MPI_COMM_WORLD);
MPI_Bcast(&phrase, phraseLength, MPI_CHAR, 0, MPI_COMM_WORLD); 

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

// Calculates the bounds that each process will iterate over in the array
lowerBound = (noOfLines/numProcs) * myId;
upperBound = (noOfLines/numProcs) * (myId+1);


// Iterates through every element in the array
for (int eachLine = lowerBound; eachLine < upperBound; eachLine++) {
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

int occurrencesArray[numProcs];

// Collects total occurrences of the specified phrase from all processes into one process
if(myId == 0) {
    MPI_Gather(&occurrences, 1, MPI_INT, occurrencesArray, 1, MPI_INT, 0, MPI_COMM_WORLD);
} else {
    MPI_Gather(&occurrences, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
}


// Sums the total values collected by processes and outputs the sum total
if(myId == 0) {
    for (int eachTotal = 0; eachTotal < sizeof(occurrencesArray)/ sizeof(occurrencesArray[0]); eachTotal++) {
        occurrencesTotal = occurrencesTotal + occurrencesArray[eachTotal];
    }
    printf("There are %d occurrences of this phrase in the text \n", occurrencesTotal);
}

MPI_Finalize();

return 0;

}
