#include <iostream>
#include <windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

// window width : 120chars
// window height: 30chars

int main() {
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO cbInfo;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &cbInfo);
    int original_console_att = cbInfo.wAttributes;

    // SetConsoleTextAttribute(hConsole, 13); 

    char sinplot[15][120] = {' '};
    int n = 0;
    for(int i=0; i<120; i++) {
        sinplot[(int)floor((8 + 7*sin((n/M_PI) /2)))][i] = '@';
        n = (n<360)?n+1:0;
    }
    for(int i=0; i<15; i++) {
        for(int j=0; j<120; j++) {
            SetConsoleTextAttribute(hConsole, j);
            std::cout << sinplot[i][j];
        }
        std::cout << std::endl;
    }

    for(int i=0;i<255;i++) {
        std::cout << "ELES ESTAO VINDO";
        SetConsoleTextAttribute(hConsole, 1+i%15);
    }

    SetConsoleTextAttribute(hConsole, original_console_att);
    return 0;
}