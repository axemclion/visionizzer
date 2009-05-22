# define DELAY 200

# include <process.h>
#include <string.h>
#include <math.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>
#include "d:\prog\c\draw\bmploade.cpp"

void init()
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
	loadbmp("select");
	mouse_present();
}//end of init functions


int main(void)
{
	int result = 0;
	init();
	mouse_status mouse;
while (result == 0)
{
	show_mouse();
	xclick();
	mouse = click();
	hide_mouse();
	setcolor(8);
	char name[100];
	setfillstyle(9,10);
	if (inarea(mouse.x,mouse.y,165,142,250,229))
		result = 1;
	else if(inarea(mouse.x,mouse.y,378,143,463,229))
		result = 2;
	else if(inarea(mouse.x,mouse.y,165,255,250,341))
		result = 3;
	else if(inarea(mouse.x,mouse.y,378,255,463,341))
		result = 4;
	else if(inarea(mouse.x,mouse.y,165,362,250,448))
		result = 5;
	else if(inarea(mouse.x,mouse.y,378,362,463,447))
		result = 6;
	else if (inarea(mouse.x,mouse.y,260,200,365,270))
		result = 7;
	else if (inarea(mouse.x,mouse.y,260,300,365,370))
		break;

	if (result != 0)
	{
		for (int i = 0;i < 640;i+=2)
			circle(mouse.x,mouse.y,i);
		closegraph();

		switch(result)
		{
			case 1:
				result = spawnl(P_WAIT,"puzzle.exe",NULL);
				break;
			case 3:
				result = spawnl(P_WAIT,"trans.exe",NULL);
				break;
			case 5:
				result = spawnl(P_WAIT,"computer.exe",NULL);
				result = spawnl(P_WAIT,"you.exe",NULL);
				break;
			case 2:
				result = spawnl(P_WAIT,"cobgen.exe",NULL);
				break;
			case 4:
				result = spawnl(P_WAIT,"mouse.exe",NULL);
				break;
			case 6:
				result = spawnl(P_WAIT,"port.exe",NULL);
				break;
			case 7:
				result = spawnl(P_WAIT,"pres.exe",NULL);
				break;
		}//end of switch case
		if (result != 0)
			{
			printf("Component Unavailable\nPleae press any key to continue....");
			getch();
			}
		init();

	}//end of manipulating result
	result = 0;

}//end of the main loop
	closegraph();
	return result;
}//end of main
