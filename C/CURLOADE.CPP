#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>

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
	mouse_present();
	FILE *fp;
	fp = fopen("c:\\windows\\cursors\\busy_1.cur","rt");
	if (fp == NULL)
		return 0;
	char buffer;int count;
	buffer=fgetc(fp);
	if (buffer != 0)	return 1;
	buffer=fgetc(fp);
	if (buffer != 0)	return 1;
	buffer=fgetc(fp);
	if (buffer != 2)	return 1;
	buffer=fgetc(fp);
	if (buffer != 0)	return 1;
	count = fgetc(fp);
	printf("File opened ......");
	fclose(fp);
	getch();
   closegraph();
   return 0;
}
