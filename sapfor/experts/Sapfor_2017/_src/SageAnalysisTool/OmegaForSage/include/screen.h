/* screen.h,v 1.1.1.2 1992/07/10 02:41:20 davew Exp */


#ifndef Already_Included_Screen
#define Already_Included_Screen


/* Define 6 screen primitives:
   screen_init()		what to call to initialize the graphics system.
   screen_print			like 'printf' to write to the virtual screen
   screen_move(line,col)	to move to an (line,col) position on the virtual screen
   screen_where(line,col)	get the current (line,col) position
   screen_highlight()		print with reverse video
   screen_lowlight()		end reverse-video printing
   screen_getchar(ch,line,col)	get the char at position (line,col) 
  					[may move cursor]
   screen_clear()		how to clear the screen
   screen_clrline(line)		move to the start of line 'line' and clear it
   screen_clreol()		clear to end of this line from current pos
   screen_clrrest()		clear to end of screen from this line
   screen_update()		after _print, how to update the actual screen
   screen_fini()		what to call when done with graphics.
  
   two variables:
   COLS : number of columns on screen
   LINES: number of lines on screen
  
   0 <= line < LINES
   0 <= col < COLS
   */

#ifdef __TURBOC__
/* no good way to use Turbo C to detect number of lines/cols on screen */
#define LINES 25
#define COLS 80

#include <conio.h>
/* #define screen_init()		textattr((BLUE<<4)+LIGHTGRAY) */
#define screen_init()		textattr((BLACK<<4)+LIGHTGRAY), 1
/* added ,1 to make it return TRUE.  3.21.91 davew@panache.cs.umd.edu */
#define screen_print		cprintf
#define screen_move(line,col)	gotoxy(col+1,line+1)
#define screen_where(line,col)	line=wherey()-1;col=wherex()-1
/* #define screen_highlight()	textattr((LIGHTGRAY<<4)+BLUE) */
/* #define screen_lowlight()	textattr((BLUE<<4)+LIGHTGRAY) */
#define screen_highlight()	textattr((LIGHTGRAY<<4)+BLACK)
#define screen_lowlight()	textattr((BLACK<<4)+LIGHTGRAY)
#define screen_getchar(ch,line,col)	\
				{ char c[2];\
				  gettext(col+1,line+1,col+1,line+1,c);\
				  ch = c[2]; }
#define screen_clear()		clrscr()
#define screen_clrline(line)	gotoxy(1,line+1);clreol()
#define screen_clreol()		clreol()
#define screen_clrrest()	{ uint l;\
				  for(l=wherey();l<=LINES-2;++l){\
				    gotoxy(1,l);\
				    clreol();\
				  }\
				}
#define screen_update()
#define screen_fini()
#else
#include <curses.h>
#include "missing.h"
#undef bool
/* #define screen_init()		initscr();refresh() */

/* Three new functions for use with scrolling */
#define screen_putchar		mvaddch
#define screen_waddch		mvwaddch
#define screen_insertln		insertln
#define screen_deleteln		deleteln
#define screen_print		printw
#define screen_wprint		mvwprintw
#define screen_move(line,col)	move(line,col)
#define screen_where(line,col)	getyx(stdscr,line,col)
#define screen_highlight()	standout()
#define screen_lowlight()	standend()
#define screen_dhighlight()	wstandout(depend)
#define screen_dlowlight()	wstandend(depend)
#define screen_touch()		touchwin(stdscr)
#define screen_dtouch()		touchwin(depend)
#define screen_dclose()		delwin(depend)

/* get the character directly from the curses data structure so that the */
/* attribute bit is not stripped off                                     */
#define screen_getchar(ch,line,col)	ch=stdscr->_y[line][col]

#define screen_clear()		{ clear();\
				  if (depend_shown)\
				    wclear(depend);\
                                }
#define screen_clrline(line)	{move(line,0);clrtoeol();}
#define screen_clreol()		clrtoeol()
#define screen_clrrest()	{ uint l,c;\
				  getyx(stdscr,l,c);\
				  for(l=l;l<LINES-2;++l){\
				    move(l,0);\
				    clrtoeol();\
				  }\
				}
#define screen_update()		{ refresh();\
				  if (depend_shown){\
				    wrefresh(depend);\
				  }\
                                }
#define screen_touch_and_update() { touchwin(stdscr); refresh();\
				  if (depend_shown){\
				    touchwin(depend); wrefresh(depend);\
				  }\
                                }

extern int screen_init();
extern void screen_fini();
  /* changed to functions for better results from curses
     3/20/91 davew@panache.cs.umd.edu */

#endif

WINDOW *depend;
int depend_shown;

#endif
