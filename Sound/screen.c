#include "screen.h"
#include <stdio.h>

/*	function definition of clearScreen()
	This function uses VT100 escape sequences \ESC[2J to make the whole
	terminal screen empty
	argument: no
	return: no
*/

void clearScreen(void){
	printf("%c[2J",ESC);
	fflush(stdout);
}

/*	function definition of gotoxy()
	This function uses VT100 escape sequence \ESC[row;colH to set cursor
	to a specific location on the terminal screen
	argument:	row number, 1 is top row
				col number, 1 is left column
	return: no
*/

void gotoxy(int row, int col){
	printf("%c[%d;%dH", ESC, row, col);
	fflush(stdout);
}

/*	function definition of setColor()
	This function uses VT100 escape sequence \ESC[1;colorm to set color
	argument: color
	return: no
*/

void setColor(int color){
	if(color >= BLACK && color <= WHITE){
		printf("%c[1;%dm",ESC,color);
		fflush(stdout);
	}
}

/*	function definition of dispBar()
	This function would display decibel value in bar type. The decibel value
	is divided by 3 and every 3dB is one row, so we rendered 3dB for one row.
	We set color for dB value, when dB value is bigger than 51, the color of
	the bar is yellow. When dB value is bigger than 69, the color of the bar is red
	argument:	dB, decibel value
				color
	return: no
*/
void dispBar(int col, double dB){
	int i;
	for(i=0; i< dB/3; i++){		// we render 3dB for one row
		gotoxy(30-i, col+1);
#ifndef UNICODE		//if unicode is not enabled
		printf("%c", '*');
#else				// if unicode is enabled
		if(i >17 && i<23)		//if 51 < dB < 69 , the bar is yellow
			setColor(YELLOW);
		else if( i >= 23)		// if dB >= 69, the bar is red
			setColor(RED);
		else
			setColor(WHITE);	// if dB <= 50, the bar is white
		printf("%s",BAR);
#endif			// end of conditional compilation
	}
}
