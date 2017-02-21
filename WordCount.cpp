/*
 * Bailey Thompson
 * Word Count (1.0.4)
 * 20 February 2017
 * Create a .txt file and insert some text. The program will then count the amount of words and write it to a .anl file.
 * Insert words as command-line arguments to get the occurrences of those words in the .anl file also.
 */

#include <iostream>
#include <fstream>
#include <math.h>

const int MAX_CHARACTERS = 50000;

void setFormatToAnl(char* fileName, int index) {
    fileName[index + 1] = 'a';
    fileName[index + 2] = 'n';
    fileName[index + 3] = 'l';
    fileName[index + 4] = '\0';
}

void setFormatToTxt(char* fileName, int index) {
    fileName[index] = '.';
    fileName[index + 1] = 't';
    fileName[index + 2] = 'x';
    fileName[index + 3] = 't';
    fileName[index + 4] = '\0';
}

bool invalidFileFormat(char* fileFormat, int u) {
    return fileFormat[u] == '.' && (fileFormat[u + 1] != 't' || fileFormat[u + 2] != 'x' || fileFormat[u + 3] != 't');
}

int main(int argc, char* argv[]) {
    char buffer[MAX_CHARACTERS];
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        buffer[i] = ' ';
    }
    if (argc < 2) {
        std::cerr << "Error: not enough arguments" << std::endl;
        return -1;
    }
    char* fileFormat = argv[1];
    int u = 0;
    while (fileFormat[u] != '\0' && fileFormat[u] != '.') {
        u++;
    }
    if (invalidFileFormat(fileFormat, u)) {
        std::cerr << "Error: invalid file format" << std::endl;
        return -1;
    }
    std::ifstream fin;
    int counter = 0;
    char* newFile = argv[1];
    while (newFile[counter] != '\0' && newFile[counter] != '.') {
        counter++;
    }
    char fileName[counter + 4];
    int index = 0;
    if (newFile[counter] == '\0') {
        while (newFile[index] != '\0') {
            fileName[index] = newFile[index];
            index += 1;
        }
        setFormatToTxt(fileName, index);
    } else if (newFile[counter] == '.') {
        while (newFile[index] != '\0') {
            fileName[index] = newFile[index];
            index += 1;
        }
        index -= 4;
        fileName[index + 4] = '\0';
    }
    fin.open(fileName);
    if (fin.fail()) {
        std::cerr << "Error: bad file name" << std::endl;
        return -1;
    }
    int subword[argc - 1];
    for (int i = 0; i < argc - 1; i++) {
        subword[i] = 0;
    }
    int wordCount = 0, letterCount = 0, longestWord = 0, shortestWord = 0, currentWord = 0;
    while (fin.getline(buffer, MAX_CHARACTERS)) {
        for (int i = 0; i < MAX_CHARACTERS; i++) {
            int w = 2;
            while (argc > w) {
                char* temp = argv[w];
                int h = 0, l = 0;
                while (temp[h] != '\0' && tolower(temp[h]) == tolower(buffer[i + h]) && buffer[i + h] != ' ') {
                    h += 1;
                }
                while (temp[l] != '\0') {
                    l += 1;
                }
                if (h == l) {
                    subword[w - 2] += 1;
                }
                w += 1;
            }
            buffer[i] = (char) tolower(buffer[i]);
            if (int(buffer[i]) < 97 || int(buffer[i]) > 122) {
                buffer[i] = ' ';
            }
            if (buffer[i] != ' ') {
                currentWord++;
                letterCount++;
            } else if (i > 0 && buffer[i] == ' ' && buffer[i - 1] != ' ') {
                wordCount++;
                if (shortestWord == 0) {
                    shortestWord = currentWord;
                }
                if (currentWord > longestWord) {
                    longestWord = currentWord;
                } else if (currentWord < shortestWord) {
                    shortestWord = currentWord;
                }
                currentWord = 0;
            }
        }
        for (int i = 0; i < MAX_CHARACTERS; i++) {
            buffer[i] = ' ';
        }
    }
    fin.close();

    setFormatToAnl(fileName, index);

    std::ofstream outputFile;
    outputFile.open(fileName);

    double average = (double) letterCount / (double) wordCount;
    average *= 100;
    average = round(average);
    average /= 100;

    outputFile << "Number of words: " << wordCount << std::endl;
    outputFile << "Longest word: " << longestWord << std::endl;
    outputFile << "Shortest word: " << shortestWord << std::endl;
    outputFile << "Average word length: " << average << std::endl;
    for (int i = 2; i < argc; i++) {
        outputFile << "Number of occurrences of " << argv[i] << ": " << subword[i - 2] << std::endl;
    }

    outputFile.close();
    return 0;
}
