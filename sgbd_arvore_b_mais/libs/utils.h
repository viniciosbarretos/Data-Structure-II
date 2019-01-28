#ifndef SGBD_TEXT_H
#define SGBD_TEXT_H

void cleanBuffer();
void clearScreen();
void strCopyFragment(char *buffer, const char *input, int start, int size);
char toLower(char c);
void toLowerCase(char *str);
int getIntegerBetween(int min, int max);
char getCharInOptions(const char *options, const char *errorMessage);
void waitForChar(const char *message);
int max(int a, int b);
int min(int a, int b);

#endif //SGBD_TEXT_H
