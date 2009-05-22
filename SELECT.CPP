# define DELAY 200

#include <string.h>
#include <math.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>
#include "d:\prog\c\draw\bmploade.cpp"

int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	int result = 0;
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}
	loadbmp("select");
	mouse_present();
	mouse_status mouse;
st:
	show_mouse();
	xclick();
	mouse = click();
	hide_mouse();
	setcolor(8);
	char name[100];
	setfillstyle(9,10);
	if (inarea(mouse.x,mouse.y,165,142,250,229))
		{
		result = 1;
		strcpy(name,"Presentation");
		bar(165,142,250,229);
		}
	else if(inarea(mouse.x,mouse.y,378,143,463,229))
		{
		result = 2;
		strcpy(name,"VisioniZZer");
		bar(378,143,463,229);
		}
	else if(inarea(mouse.x,mouse.y,165,255,250,341))
		{
		result = 3;
		strcpy(name,"Port Tester");
		bar(165,255,250,341);
		}
	else if(inarea(mouse.x,mouse.y,378,255,463,341))
		{
		result = 4;
		strcpy(name,"Mousepointer");
		bar(378,255,463,341);
		}
	else if(inarea(mouse.x,mouse.y,165,362,250,448))
		{
		result = 5;
		strcpy(name,"Knots & Krosses");
		bar(165,362,250,448);
		}
	else if(inarea(mouse.x,mouse.y,378,362,463,447))
		{
		result = 6;
		strcpy(name,"Exit");
		bar(378,362,463,447);
		}
	else goto st;
	setcolor(11);
	for (int i = 0;i < 640;i+=2)
		{
		circle(mouse.x,mouse.y,i);
		delay(2);
		}

	settextstyle(0,0,5);
	setcolor(12);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	int x = getmaxx()/2-textwidth(name)/2;
	char t[2];
	t[1] = NULL;
	for (i=0;i < strlen(name);i++)
		{
		t[0] = name[i];
		outtextxy(x,getmaxy()/2,t);
		x=x+textwidth(t);
		delay(DELAY);
		}
	delay(200);
	setcolor(0);
	for (i = 0;i < getmaxy();i++)
		{
		line(0,i,getmaxx(),i);
		delay(3);
		}
	closegraph();
	if (mouse.button == RIGHT_CLICK)
		return 7;
	return result;
}
