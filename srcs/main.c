#include "../includes/ft_ls.h"

int    main()
{
  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  start_color();
  raw();

  WINDOW * _main;
  _main = newwin(30, 80, 2, 150);

  refresh();


    mvwprintw(_main,5,2, "Hostname                   ->    %s;", "blablabla");

    wrefresh(_main);

    getch();
    endwin();

  return (0);
}
