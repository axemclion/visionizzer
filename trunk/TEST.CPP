#include <graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

# include <mouse.h>
# include "d:\prog\c\draw\bmploade.cpp"
# include "d:\prog\c\header1.h"
# include "d:\prog\c\header2.h"


int __obj;

int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
	line(0, 0, getmaxx(), getmaxy());
	getch();
	closegraph();
   return 0;
}
