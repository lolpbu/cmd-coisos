#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "include/input.h"
#include "include/mat4.h"
#include "include/tela.h"
#include "include/peca.h"

#define period 1000.0/5.5

using namespace std;

chrono::system_clock::time_point t_a = chrono::system_clock::now();
chrono::system_clock::time_point t_b = chrono::system_clock::now();

int main(int argc, char** argv) {

    // Mat4 teste({
    //     {'.', '.', '.', '.'},
    //     {'.', '#', '#', '.'},
    //     {'.', '#', '#', '.'},
    //     {'.', '.', '.', '.'}
    // });

    Mat4 teste({
        {'#', '.', '.', '.'},
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'}
    });

    Mat4 formats[] = {
        
        // Mat4({
        //     {'.', '.', '.', '.'},
        //     {'.', '#', '#', '.'},
        //     {'.', '#', '#', '.'},
        //     {'#', '#', '#', '#'}
        // }),

        Mat4({
            {'.', '#', '.', '.'},
            {'.', '#', '.', '.'},
            {'.', '#', '.', '.'},
            {'.', '#', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'.', '#', '#', '.'},
            {'.', '#', '#', '.'},
            {'.', '.', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'#', '.', '.', '.'},
            {'#', '#', '#', '.'},
            {'.', '.', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'.', '.', '.', '#'},
            {'.', '#', '#', '#'},
            {'.', '.', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'.', '#', '.', '.'},
            {'#', '#', '#', '.'},
            {'.', '.', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'.', '#', '#', '.'},
            {'#', '#', '.', '.'},
            {'.', '.', '.', '.'}
        }),

        Mat4({
            {'.', '.', '.', '.'},
            {'.', '#', '#', '.'},
            {'.', '.', '#', '#'},
            {'.', '.', '.', '.'}
        }),
    };

    std::random_device dev;
    std::uniform_int_distribution<std::mt19937::result_type> rnd_range_0_6(0, 6);

    Tela t;
    Peca* p;
    KEY_STATE_T stt = NOSTT;
    bool exit = false;
    int pont = 0;
    int down_c = 0;

    while(!exit) {
        std::mt19937 RNG(dev());
        int format_i = rnd_range_0_6(RNG);
        p = new Peca(formats[format_i], &t);
        p->_debug_str = std::to_string(format_i);
        //p = new Peca(teste, &t);

        while(!p->sol) {
            if(Input::key_esc()) {
                exit = true;
                break;
            }
            
            //step clock
            t_a = chrono::system_clock::now();
            chrono::duration<double, milli> deltaT = t_a - t_b;
            if(deltaT.count() < period) { 
                chrono::duration<double, milli> deltaT_ms(period - deltaT.count());
                auto deltaT_ms_duration = chrono::duration_cast<chrono::milliseconds>(deltaT_ms);
                this_thread::sleep_for(chrono::milliseconds(deltaT_ms_duration.count()));
            }
            t_b = chrono::system_clock::now();
            chrono::duration<double, milli> work_time = t_b - t_a;
            // if(down_c++ >= 3)
            //     down_c = 0;


            //input handle
            stt = Input::get_key_state();

            //update
            if(Input::key_space())
                p->format.rotate90();
            p->move(stt);

            if(p->coll(DOWN)) {
                p->sol = true;
                if(p->y <= LIMIT_Y)
                    exit = true;
                t.clear_sol();
                t.clear_lines(&pont);
            } else {
                if(down_c++ >= 3) {
                    p->move(DOWN);
                    down_c = 0;
                }
            }

            //clear
            //cout << "\x1b[2J\x1b[H";
	        system("CLS");

            //draw
            t.print();

            //debug
            cout << pont << endl;
            cout << "hz: " << 1000.0/(work_time + deltaT).count() << endl;
            cout << endl;

            cout << stt  << " / " << Input::key_state_str(stt) << endl;
            cout << "x " << p->x << endl;
            cout << "y " << p->y << endl;
            cout << endl;

            cout << "coll R " << p->coll(RIGHT) << endl;
            cout << "coll L " << p->coll(LEFT) << endl;
            cout << "coll D " << p->coll(DOWN) << endl;
            cout << "coll U " << p->coll(UP) << endl;
            cout << endl;

            cout << p->_debug_str << endl;
            cout << endl;
        }
        //delete p;
    }

    delete p;

    return 0;
}
