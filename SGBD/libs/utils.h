#ifndef SGBD_TEXT_H
#define SGBD_TEXT_H

void cleanBuffer();
void strCopyFragment(char *buffer, const char *input, int start, int size);
char toLower(char c);
void toLowerCase(char *str);
char getCharInOptions(const char *options, const char *errorMessage);

#endif //SGBD_TEXT_H
