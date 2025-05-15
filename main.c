#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **text;
int row = 0;
int symbol = 0;
int memory_allocated = 1;

char *readInput() {
    int size = 10;
    char *buffer = malloc(size);
    if (buffer == NULL) return NULL;

    int index = 0;
    int current;

    while ((current = getchar()) != '\n' && current != EOF) {
        if (index + 1 > size) {
            size *= 2;
            char *temp = realloc(buffer, size);
            if (temp == NULL) {free(buffer);buffer = NULL;return NULL;}
            buffer = temp;
        }
        *(buffer + index++) = (char) current;
    }
    *(buffer + index) = '\0';
    return buffer;
}

void newLine() {
    row++;
    symbol = 0;
    text = realloc(text, memory_allocated += sizeof(char *));
    printf("New line started\n\n");
}

void save() {
    FILE* file;
    int temp; while ((temp = getchar()) != '\n' && temp != EOF) {}
    file = fopen(readInput(), "w");
    if (file != NULL)
    {
        for (int i = 0; i <= row; i++) {
            fputs(*(text + i), file);
            fputc('\n', file);
        }
        fclose(file);
        printf("Text has been saved successfully\n");
    }
}

void load() {
    FILE* file;
    int row_counter = 0;
    int temp; while ((temp = getchar()) != '\n' && temp != EOF) {}
    file = fopen(readInput(), "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }

    free(text);
    text = NULL;
    int alloc = sizeof(char*);
    text = malloc(alloc);

    int size = 10;
    int count = 0;
    char* buf = malloc(size);
    char ch;
    while ((ch = (char)fgetc(file)) != EOF) {
        if (count >= size) buf = realloc(buf, size*=2);
        if (ch == '\n') {
            *(buf + count) = '\0';
            row = row_counter;
            symbol = count;
            *(text + row_counter++) = buf;
            buf = malloc(size = 10);
            count = 0;
            text = realloc(text, alloc+=sizeof(char*));
        } else {
            *(buf + count++) = ch;
        }
    }
    fclose(file);
    printf("Text has been loaded successfully\n");
}

void print() {for (int i = 0; i <= row; i++) printf("%s\n\n", *(text + i));}

void insert(const int *ROW, const int *SYMBOL) {
    if (ROW == NULL || SYMBOL == NULL) return;

    int temp; while ((temp = getchar()) != '\n' && temp != EOF) {}

    char *input = readInput();

    int length = 0; while (*(input + length) != '\0') length++;

    if (*ROW == row && *SYMBOL == symbol && symbol == 0) *(text + *ROW) = malloc(length);
    else *(text + *ROW) = realloc(*(text + *ROW), memory_allocated += length);

    if (*ROW == row && *SYMBOL == symbol) for (int i = 0; i < length; i++) *(*(text + *ROW) + *SYMBOL + i) = *(input + i);
    else{
        for (int i = strlen(*(text + *ROW)); i >= *SYMBOL; i--)
            *(*(text + *ROW) + length + i) = *(*(text + *ROW) + i);
        for (int i = 0; i < length; i++)
            *(*(text + *ROW) + *SYMBOL + i) = *(input + i);
    }

    symbol += length;
    free(input);
    input = NULL;
    printf("\n");
}

void search() {
    int temp; while ((temp = getchar()) != '\n' && temp != EOF) {}
    char* prompt = readInput();
    int length = 0; while (*(prompt + length) != '\0') length++;
    for (int i = 0; i <= row; i++) {
        char* whole = *(text + i);
        char* found;

        while ((found = strstr(whole, prompt)) != NULL) {
            while (whole < found) putchar(*whole++);
            printf("[>%.*s<]", length, found);
            whole = found + length;
        }
        printf("%s\n", whole);
    }
}


int main(void) {
    system("clear");
    text = malloc(memory_allocated);
    while (235) {
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
                printf("Enter the file name for saving: ");
                save();
                break;
            case '4':
                printf("Enter the file name for loading: ");
                load();
                break;
            case '5':
                print();
                break;
            case '6':
                printf("Choose row and index [%%d %%d]: ");
                int r = row;
                int s = symbol;
                if (scanf(" %d %d", &r, &s) == 2) {
                    printf("Enter text to insert: ");
                    insert(&r, &s);
                } else printf("Invalid input, try again\n");
                break;
            case '7':
                printf("Enter text to search: ");
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
