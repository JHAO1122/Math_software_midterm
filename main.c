# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ncurses.h>
# include <unistd.h>
# include "conway.h"

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Usage: %s rows cols [filename]\n", argv[0]);
        return 1;
    }
    boundary = 1;
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    init_world(&w, atoi(argv[1]), atoi(argv[2]));
    if(argc < 4) randomize_world(&w);
    else load_world(argv[3], &w, 0, 0);
    while(1)
    {
        clear();
        print_world(&w);
        refresh();
        usleep(100000);
        world next_w;
        next_world(&w, &next_w);
        usleep(100000);
        if(getch() == 'q') break;
        else if(getch() == 's') save_worldimage(&w, "world.bmp");
    }
    endwin();
    free_world(&w);
    return 0;
}