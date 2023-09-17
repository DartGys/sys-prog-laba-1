#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Word {
    char word[31];
    int vowelCount;
};

int compareWords(const void *a, const void *b) {
    struct Word *wordA = (struct Word *)a;
    struct Word *wordB = (struct Word *)b;
    return wordA->vowelCount - wordB->vowelCount;
}

int main() {
    char filename[100];
    printf("Write file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("An error occurred opening the file.\nThe file may not exist or you do not have permission to read it.\n"
               "Check if the file name is correct and try again.\n"
               "Example file name: name.txt\n");
        return 1;
    }

    struct Word words[10000];
    int wordCount = 0;

    char wordBuffer[31];
    int wordBufferIndex = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (!isalpha(c)) {
            if (wordBufferIndex > 0) {
                wordBuffer[wordBufferIndex] = '\0';

                int isDuplicate = 0;
                for (int i = 0; i < wordCount; i++) {
                    if (strcmp(words[i].word, wordBuffer) == 0) {
                        isDuplicate = 1;
                        break;
                    }
                }
                if (!isDuplicate) {
                    strcpy(words[wordCount].word, wordBuffer);
                    words[wordCount].vowelCount = 0;
                    for (int i = 0; wordBuffer[i] != '\0'; i++) {
                        if (isalpha(wordBuffer[i]) && strchr("aeiouAEIOU", wordBuffer[i])) {
                            words[wordCount].vowelCount++;
                        }
                    }
                    wordCount++;
                }
                wordBufferIndex = 0;
            }
        } else {
            if (wordBufferIndex < 30) {
                wordBuffer[wordBufferIndex++] = c;
            }
        }
    }

    qsort(words, wordCount, sizeof(struct Word), compareWords);

    printf("Words without repetitions, sorted by increasing number of vowel letters:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s (%d vowel letters)\n", words[i].word, words[i].vowelCount);
    }

    fclose(file);
    return 0;
}
