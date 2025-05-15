#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

char** text;
int row = 0;
int symbol = 0;
int memory_allocated = 1;

char* readInput() {
    int size = 10;
    char* buffer = malloc(size);
    if (buffer == NULL) return NULL;

    int index = 0;
    int current;

    while ((current = getchar()) != '\n' && current != EOF) {
        //Resize buffer
        if (index + 1 > size) {
            size*=2;
            char* temp = realloc(buffer, size);
            if (temp == NULL) {
                free(buffer);
                buffer = NULL;
                return NULL;
            }
            buffer = temp;
        }
        *(buffer + index++) = (char)current;
    }
    *(buffer + index) = '\0';
    return buffer;
}

void newLine() {
    row++; symbol = 0; text = realloc(text, memory_allocated += sizeof(char*)); *(text + row) = "\0"; printf("New line started\n\n");
}

void save() {

}

void load() {

}

void print() {
    for (int i = 0; i <= row; i++) {
        printf("%s\n\n", *(text + i));
    }
}

void insert(const int* ROW, const int* SYMBOL) {
    if (ROW == NULL || SYMBOL == NULL) {
        printf("Choose row and index: ");
        //TODO: parse input position
        printf("Enter text to insert: ");
        return;
    }
    int temp; while ((temp = getchar()) != '\n' && temp != EOF){} //Flush input buffer
    char* input = readInput();
    int length = 0; while (input[length] != '\0') length++; //Count input length
    if (*ROW == row && *SYMBOL == symbol && symbol == 0) *(text + *ROW) = malloc(length);
    else *(text + *ROW) = realloc(*(text + *ROW), memory_allocated+=length);
    // char** swap = realloc(text, memory_allocated+=length);
    // if (swap != NULL) text = swap; else return;
    for (int i = 0; i < length; i++) *(*(text + *ROW) + *SYMBOL + i) = *(input + i); //*(text + memory_allocated - 1 - length+i) = ;
    symbol+=length;
    free(input);
    input = NULL;
    printf("\n");
}

void search() {

}


int main(void) {
    system("clear");
    text = malloc(memory_allocated);
    while (true) {
        printf("> Choose the command ([h] - help):\n");
        char command;
        scanf(" %c", &command);
        system("clear");
        switch (command) {
            case '0':
                free(text);
                text = NULL;
                printf("-----PROGRAM END-----");
                return 143;
            case '1':
                printf("Enter text to append: ");
                insert(&row, &symbol);
                break;
            case '2':
                newLine();
                break;
            case '3':
                save();
                break;
            case '4':
                load();
                break;
            case '5':
                print();
                break;
            case '6':
                insert(NULL, NULL);
                break;
            case '7':
                search();
                break;
            default:
                printf("Valid command numbers:\n");
                printf("[0] - exit\n");
                printf("[1] - append\n");
                printf("[2] - new line\n");
                printf("[3] - save\n");
                printf("[4] - load\n");
                printf("[5] - print\n");
                printf("[6] - insert\n");
                printf("[7] - search\n");
                break;
        }
    }
}