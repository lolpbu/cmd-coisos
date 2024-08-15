#ifndef _INPUT_H
#define _INPUT_H

#include <windows.h>
#include <string>
#include <conio.h>

typedef enum {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    NOSTT = -1
} KEY_STATE_T;

//inline void clear() { system("CLS"); }
//inline void clear() { std::cout << "\x1b[2J\x1b[H"; }

namespace Input {
    inline bool key_left()  { return GetKeyState(VK_LEFT)  & 0x8000; };
    inline bool key_right() { return GetKeyState(VK_RIGHT) & 0x8000; };
    inline bool key_down()  { return GetKeyState(VK_DOWN)  & 0x8000; };
    inline bool key_up()    { return GetKeyState(VK_UP)    & 0x8000; };

    inline bool key_esc()     { return GetKeyState(VK_ESCAPE) & 0x8000; };
    inline bool key_space()   { return GetKeyState(VK_SPACE)  & 0x8000; };

    inline KEY_STATE_T get_key_state() {
        if(key_left())
            return LEFT;
        else if(key_right())
            return RIGHT;
        else if(key_down())
            return DOWN;
        else if(key_up())
            return UP;
        return NOSTT;
    }

    inline std::string key_state_str(KEY_STATE_T stt) {
        switch(stt) {
            case LEFT : return "esq";
            case RIGHT: return "dir";
            case DOWN : return "baixo";
            case UP   : return "cima";
            default   : return ". . .";
        }
    }
};

#endif