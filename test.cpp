#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;



int main()
{	int ch;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    printw("Type any character to see it in bold\n");
	ch = getch();			/* If raw() hadn't been called
					 * we have to press enter before it
					 * gets to the program 		*/
	if(ch == KEY_BACKSPACE)		/* Without keypad enabled this will */
		printw("fui borrado");/*  not get to us either	*/
					/* Without noecho() some ugly escape
					 * charachters might have been printed
					 * on screen			*/
    if(ch==KEY_F(2))
        printw("F2 key pressed");

    if(ch==KEY_F(3))
        printw("F3 key pressed");

    if(ch==KEY_F(4)){
        printw("F4 key pressed"); 
        printw("\n");
    }
    if(ch==KEY_F(5)){
        printw("F5 key pressed"); 
        printw("\n");
    }
    if(ch==KEY_F(6)){
        printw("F6 key pressed"); 
        printw("\n");
    }
    
	else
	{	printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();			/* Print it on to the real screen */
    	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
