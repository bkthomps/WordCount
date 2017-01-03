/**
 * Bailey Thompson
 * Word Count (1.0.2)
 * 22 November 2016
 * Info: Create a .txt file and insert some text. The program will then count the amount of words and write it to a .anl
 * Info: file. Insert words as command-line arguments to get the occurences of those words in the .anl file also.
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    //used for statistics tracking
    int wordCount = 0, letterCount = 0, longestWord = 0, shortestWord = 0, currentWord = 0;
    //character buffer
    char buffer[50000];
    for (int i = 0; i < 50000; i++) {
        buffer[i] = ' ';
    }
    //error checking for insufficient arguments
    if (argc < 2) {
        std::cerr << "Error: not enough arguments" << std::endl;
        return -1;
    }
    char* fileFormat = argv[1];
    int u = 0;
    //checking file format
    while (fileFormat[u] != '\0' && fileFormat[u] != '.') {
        u ++;
    }
    if (fileFormat[u] == '.') {
        if (fileFormat[u + 1] != 't' && fileFormat[u] != 'x' && fileFormat[u] != 't') {
            std::cerr << "Error: invalid file format" << std::endl;
            return -1;
        }
    }
    //setting file name
    std::ifstream fin;
    int counter = 0;
    char* newFile = argv[1];
    while (newFile[counter] != '\0' && newFile[counter] != '.') {
        counter += 1;
    }
    char fileName[counter + 4];
    int counter2 = 0;
    if (newFile[counter] == '\0') {
        while (newFile[counter2] != '\0') {
            fileName[counter2] = newFile[counter2];
            counter2 += 1;
        }
        fileName[counter2] = '.';
        fileName[counter2 + 1] = 't';
        fileName[counter2 + 2] = 'x';
        fileName[counter2 + 3] = 't';
        fileName[counter2 + 4] = '\0';
    } else if (newFile[counter] == '.') {
        while (newFile[counter2] != '\0') {
            fileName[counter2] = newFile[counter2];
            counter2 += 1;
        }
        counter2 -= 4;
        fileName[counter2 + 4] = '\0';
    }
    fin.open(fileName);
    //error checking for lack of file
    if (fin.fail()) {
        std::cerr << "Error: bad file name" << std::endl;
        return -1;
    }
    //used for subwords
    int subword[argc - 1];
    for (int i = 0; i < argc - 1; i++) {
        subword[i] = 0;
    }
    //getting file
    while (fin.getline(buffer, 50000)) {
        for (int i = 0; i < 50000; i++) {
            //checking for subword matches
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
            //converting to character array
            buffer[i] = tolower(buffer[i]);
            if (int(buffer[i]) < 97 || int(buffer[i]) > 122) {
                buffer[i] = ' ';
            }
            //doing the logic
            if (buffer[i] != ' ') {
                currentWord += 1;
                letterCount += 1;
            } else if (i > 0 && buffer[i] == ' ' && buffer[i - 1] != ' ') {
                wordCount += 1;
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
        for (int i = 0; i < 50000; i++) {
            buffer[i] = ' ';
        }
    }
    fin.close();
    //changing file type to anl
    fileName[counter2 + 1] = 'a';
    fileName[counter2 + 2] = 'n';
    fileName[counter2 + 3] = 'l';
    fileName[counter2 + 4] = '\0';
    //opening file
    std::ofstream outputFile;
    outputFile.open(fileName);
    //doing average
    double average = double(letterCount) / double(wordCount);
    average *= 100;
    average = round(average);
    average /= 100;
    //writing to file
    outputFile << "Number of words: " << wordCount << std::endl;
    outputFile << "Longest word: " << longestWord << std::endl;
    outputFile << "Shortest word: " << shortestWord << std::endl;
    outputFile << "Average word length: " << average << std::endl;
    for (int i = 2; i < argc; i++) {
        outputFile << "Number of occurences of " << argv[i] << ": " << subword[i - 2] << std::endl;
    }

    outputFile.close();
    return 0;
}
