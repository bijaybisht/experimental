#pragma once
#include <iostream>
#include <ncurses.h>

class Window 
{
private:
    static Window &instance() {
        static Window w;
        return w;
    }

    std::string message;

    Window(): message("scheduler simulation > q to quit") {
        initscr();
        cbreak();

        if (!has_colors()) exit(-1);

        start_color();

        init_color(1,750,0,0);
        init_color(2,0,1000,0);
        init_color(3,0,0,1000);
        init_color(4,500,500,0);
        init_color(5,0,500,500);
        init_color(6,500,0,500);

        init_pair(1, COLOR_WHITE, 1);
        init_pair(2, COLOR_WHITE, 2);
        init_pair(3, COLOR_WHITE, 3);
        init_pair(4, COLOR_WHITE, 4);
        init_pair(5, COLOR_WHITE, 5);
        init_pair(6, COLOR_WHITE, 1);
        init_pair(7, COLOR_WHITE, 2);
        init_pair(8, COLOR_WHITE, 3);
        init_pair(9, COLOR_WHITE, 4);
        init_pair(10, COLOR_WHITE, 5);

        wattron(draw,A_REVERSE);

        //setlocale(LC_ALL, "");
        draw   = newwin(16,200,0,0);
        jobs   = newwin(1,200,17,0);
        text   = newwin(8,200,19,0);
        prompt = newwin(1,200,28,0);

        wprintw(prompt, message.c_str());
        wrefresh(prompt);
    }

    ~Window() {
        wgetch(prompt);
        endwin();
    }

public:
    static void initdraw() {
        Window &w = instance();
        wclear(w.draw);
    }

    static void coloron(unsigned int scheme) {
        Window &w = instance();
        wattron(w.draw, COLOR_PAIR(scheme));
    }

    static void coloroff(unsigned int scheme) {
        Window &w = instance();
        wattroff(w.draw, COLOR_PAIR(scheme));
        //wrefresh(w.draw);
    }

    static void plot(unsigned int row, unsigned int bars) {
        Window &w = instance();
        unsigned int col = bars;
        while (col--) mvwaddch(w.draw, 15 - col, row, '+');
        if(!bars) mvwaddch(w.draw, 15, row, 'o');
        wrefresh(w.draw);
    }

    static void jout(const std::string &s) {
        Window &w = instance();
        wprintw(w.jobs, s.c_str());
        wrefresh(w.jobs);
    }

    static void out(const std::string &s) {
        Window &w = instance();
        wprintw(w.text, s.c_str());
        wrefresh(w.text);
    }

    static void clear() {
        Window &w = instance();
        wclear(w.text);
    }

    static void wait() {
        static int quit = false;
        Window &w = instance();
        wmove(w.prompt,0,w.message.length());
        wrefresh(w.prompt);
        if (!quit) {
            char c = wgetch(w.prompt);
            quit = (c == 'q');
        }

        wclear(w.text);
        wmove(w.text,0,0);
        wrefresh(w.text);

        wclear(w.jobs);
        wmove(w.jobs,0,0);
        wrefresh(w.jobs);
    }

    WINDOW *draw;
    WINDOW *jobs;
    WINDOW *text;
    WINDOW *prompt;
};
