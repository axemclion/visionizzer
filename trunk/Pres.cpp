#include <dos.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "d:\prog\c\bmploade.cpp"

# define PORT  0x378

void load()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}

}

int recv()
{
	int ret = 1;
	while (ret != 0)
	{
		char far *scroll = (char far*)0x417;
		if (!(*scroll & 16))
			break;
		ret = inport(PORT+1);
		ret = ret & 16;
	}
	while (ret== 0)
	{
		char far *scroll = (char far*)0x417;
		if (!(*scroll & 16))
			break;
		ret = inport(PORT+1);
		ret = ret & 16;
	}
	while(kbhit())
		getch();
	return ret + 52;
}//end of wireless

int main()
{
	clrscr();
	printf("Press a key for presentation .....");
	char far *soll = (char far*)0x417;
	char a = 0;
	_setcursortype(_NOCURSOR);
	while (!kbhit())
	{
	gotoxy(2,1);
	a = inport(PORT+1);
	a = a & 16;
	if (*soll & 16)
		printf("\nWireless Activated ..... ");
	else
		printf("\nWireless not active..... ");
	if (!a)
		printf("   [ 께께께께께� ]   ");
	else
		printf("   [ ----------- ]   ");
	}//end of waiting
	getch();
	while (kbhit())
		getch();
	int wireless = 0;
	int flag = 0;
	char *fname = (char *)calloc(1,100);
	FILE *fp;
	load();
	int key = 0;
	fp = fopen("pres.ini","rt");
	while (!feof(fp))
	{
		char far *scroll = (char far*)0x417;
//checking for scroll lock
		if (*scroll & 16)
			wireless = 1;
		else
			wireless = 0;
//actual procedure
		key = 0;
		fgets(fname,100,fp);
		fname[strlen(fname) -1] = NULL;
		loadbmp(fname,1,1);
		if (flag == 0)
			if (wireless == 1)
				key = recv();
			else
				{
				key = getch();
				if (key == 0)
					getch();
				}
		else if (flag == 1)
			delay(2000);
		if (key == 27)
			break;
		if (key == 13)
			flag = 1;
	while(kbhit())
		getch();
	}//end of file
	fclose(fp);
	closegraph();
	return 0;
}
