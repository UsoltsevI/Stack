#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <windows.h>

const HANDLE COLOR_C = GetStdHandle(STD_OUTPUT_HANDLE);

#define BLACK    0
#define BLUE     1
#define GREEN    2
#define LLBLUE   3
#define RED      4
#define PURPURE  5
#define YELLOW   6
#define LYELLOW  7
#define GREY     8
#define LBLUE    9
#define LGREEN   10
#define LLGREEN  11
#define ORANGE   12
#define LPURPURE 13
#define LLYELLOW 14
#define WHITE    15

#define COL(a, b) SetConsoleTextAttribute(COLOR_C, a + 16 * b);
#define C(a) SetConsoleTextAttribute(COLOR_C, a);

#endif // COLOR_H_INCLUDED
