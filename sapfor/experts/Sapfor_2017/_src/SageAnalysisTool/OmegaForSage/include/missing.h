/* missing.h,v 1.1.1.2 1992/07/10 02:40:55 davew Exp */
#ifndef Already_Included_Missing
#define Already_Included_Missing


/* You may need to comment these out */

extern int      delwin();
extern int      touchwin();
extern int      waddch();
extern int      waddstr();
extern int      wclear();
extern int      wclrtoeol();
extern int      wdeleteln();
extern int      wgetch();
extern int      wgetstr();
extern int      winsch();
extern int      winsertln();
extern int      wmove();
extern int      wrefresh();
extern int      wstandend();
extern int      wstandout();
extern int      printw();
extern int      wprintw();
extern int      mvwprintw();
extern int      endwin();
extern int      stty();

extern char     *getwd();

extern int	wait3();

extern int	mkdir();

extern int	getrusage();

#endif
