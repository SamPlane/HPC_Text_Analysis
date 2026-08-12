#include <stdio.h>

int main() {
FILE *file = fopen("Odyssey.txt", "r"); // Open file in read mode
if (file == NULL) {
printf("Error: Could not open file.\n");
return 1;
}

char ch;
while ((ch = fgetc(file)) != EOF) { // Read until End of File (EOF)
putchar(ch); // Print each character
}

fclose(file); // Close the file
return 0;
}
