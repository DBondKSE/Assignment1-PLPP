#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

char* text;
int row = 0;
int symbol = 0;
int memory_allocated = 0;

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
                return NULL;
            }
            buffer = temp;
        }
        buffer[index++] = current;
    }
    buffer[index] = '\0';

    return buffer;
}

void newLine() {

}

void save() {

}

void load() {

}

void print() {
    printf("%s\n\n",text);
}

void insert(const int* ROW, const int* SYMBOL) {
    if (ROW == NULL && SYMBOL == NULL) {
        printf("Choose row and index: ");
        //TODO: parse input position
        printf("Enter text to insert: ");
    }

    int temp; while ((temp = getchar()) != '\n' && temp != EOF){} //Flush input buffer
    char* input = readInput();
    int length = 0; while (input[length] != '\0') length++; //Count input length
    text = realloc(text, memory_allocated+=length);
    for (int i = 0; i < length; i++) text[memory_allocated-length+i] = input[i];
    symbol+=length;
    free(input);
    printf("\n");
}

void search() {

}


int main(void) {
    system("clear");
    text = malloc(memory_allocated);
    while (true) {
        printf("> Choose the command:\n");
        int command;
        //TODO: bug with letter input instead of number
        scanf("%d", &command);
        system("clear");
        switch (command) {
            case 0:
                free(text);
                return 143;
            case 1:
                printf("Enter text to append: ");
                insert(&row, &symbol);
                break;
            case 2:
                newLine();
                break;
            case 3:
                save();
                break;
            case 4:
                load();
                break;
            case 5:
                print();
                break;
            case 6:
                insert(NULL, NULL);
                break;
            case 7:
                search();
                break;
            default:
                printf("Please, enter valid command number\n");
                break;
        }
    }
}