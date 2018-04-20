

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STDERR 2
#define ERROR "Error in system call\n"
#define SIZEERROR 21

/**
 * check if the letters are the same but one is upper case and the other is lower case
 * @param letter1 is the first letter
 * @param letter2 is the second letter
 * @return flag that symbolies somthing for the rest of the function
 */
int checkSimilar(char *letter1, char *letter2) {
    int replaceToCap;
    int replaceToLow;
    replaceToLow = *letter2 + 32;
    if (*letter1 == replaceToLow) {
        return 2;
    }
    replaceToCap = *letter2 - 32;
    if (*letter1 == replaceToCap) {
        return 2;
    } else {
        return 0;
    }
}

/**
 * make sure that we close the files that we opened.
 * @param file1 is the file descriptor of file1.
 * @param file2 is the file descriptor of file2.
 */
void closeFiles(int file1, int file2){
    close(file1);
    close(file2);
}

/**
 * main function.
 * @param argc is the number of parameters to main
 * @param argv is the files.
 * @return value that says if the files are the same or similar or not the same
 */
int main(int argc, char *argv[]) {
    char letter1[1];
    char letter2[1];

    int file1, file2;
    ssize_t result1, result2;

    int flagSimilar = 1;
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments\n");
    } else {
        file1 = open(argv[1], O_RDWR);
        file2 = open(argv[2], O_RDWR);
        if (file1 == -1 || file2 == -1) {
            write(STDERR, ERROR, SIZEERROR);
            exit(-1);
        } else { // success in opening the two files
            do {
                result1 = read(file1, letter1, 1);
                result2 = read(file2, letter2, 1);

                if (result1 == -1 || result2 == -1) {
                    write(STDERR, ERROR, SIZEERROR);
                    exit(-1);
                }

                if (*letter1 == *letter2) {
                    continue;
                } else {
                    flagSimilar = checkSimilar(letter1, letter2);
                    if (flagSimilar == 2)
                        continue;
                    if (flagSimilar == 0) {
                        if ((*letter1 == ' ' ||*letter1 == '\n')&& *letter2 != ' ') {
                            while (*letter1 == ' '|| *letter1 == '\n') {
                                result1 = read(file1, letter1, 1);
                                if (result1 == -1) {
                                    write(STDERR, ERROR, SIZEERROR);
                                }
                            }
                            if (*letter1 == *letter2) {
                                flagSimilar = 2;
                                continue;
                            }
                            else {
                                printf("the files are NOT the same\n");
                                closeFiles(file1, file2);
                                return 1;
                            }
                        } else if ((*letter2 == ' ' || *letter2 == '\n')&& *letter1 != ' ') {
                            while (*letter2 == ' '|| *letter2 == '\n') {
                                result2 = read(file2, letter2, 1);
                                if (result2 == -1) {
                                    write(STDERR, ERROR, SIZEERROR);
                                }
                            }
                            if (*letter1 == *letter2) {
                                printf("the files are the same \n");
                                flagSimilar = 2;
                                continue;
                            }
                            else {
                                printf("the files are NOT the same \n");
                                closeFiles(file1, file2);
                                return 1;
                            }
                        }
                    }
                }
            } while (result1 != 0 && result2 != 0);

        }
        if (flagSimilar == 1) {
            printf("the files are the same! \n");
            closeFiles(file1, file2);
            return 3;
        }else if(flagSimilar == 2){
            printf("the files are the similar \n");
            closeFiles(file1, file2);
            return 2;
        }


    }
}