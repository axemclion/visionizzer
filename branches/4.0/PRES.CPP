#include <dos.h>
#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>
#include <string.h>
#include "d:\prog\c\draw\bmploade.cpp"

int main()
{
	int flag = 0;
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
	char *fname = (char *)calloc(1,100);
	FILE *fp;
	int key = 0;
	fp = fopen("pres.ini","rt");
		while (!feof(fp))
	{
		key = 0;
		fgets(fname,100,fp);
		fname[strlen(fname) -1] = NULL;
		loadbmp(fname,1,1);
		if (flag == 0)
			key = getch();
		else if (flag == 1)
			delay(2000);
		if (key == 27)
			break;
		if (key == 13)
			flag = 1;
	}//end of file
	fclose(fp);
	closegraph();
	return 0;
}
